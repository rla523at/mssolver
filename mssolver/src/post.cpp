#include "Post.h"

#include "msexception/Exception.h"
#include "msstring/string.h"
#include "mstecplot/Writer.h"

void Post::initialize(const ms::config::Data& post_data)
{
  const auto& format      = post_data.get_data<std::string>("Format");
  const auto& folder_path = post_data.get_data<std::string>("folder_path");
  const auto& title       = post_data.get_data<std::string>("title");
  THIS::_partition_order  = post_data.get_data<int>("partition_order");
  const auto& sol_loc     = post_data.get_data<std::string>("SOLUTION_LOCATION");

  ms::tecplot::Configuration config;

  if (ms::string::compare_icase(format, "ASCII"))
  {
    config.file_fomrat = ms::tecplot::File_Format::ASCII;
  }
  else if (ms::string::compare_icase(format, "BINARY"))
  {
    config.file_fomrat = ms::tecplot::File_Format::Binary;
  }
  else
  {
    EXCEPTION(format + " is not supproted post file format");
  }

  config.folder_path = folder_path;
  config.title       = title;

  ms::tecplot::Writer::set_configuration(std::move(config));

  if (ms::string::compare_icase(sol_loc, "CENTER"))
  {
    THIS::_is_solution_location_center = true;
  }
  else if (ms::string::compare_icase(sol_loc, "NODE"))
  {
    THIS::_is_solution_location_center = false;
  }
  else
  {
    EXCEPTION(sol_loc + " is not supproted solution location");
  }

  THIS::_is_initialized = true;
}

void Post::write_grid(const ms::grid::Grid& grid)
{
  REQUIRE(THIS::_is_initialized, "initialize should be call first");

  const auto dim = grid.dimension();

  ms::geo::Partition_Data partition_data;
  if (THIS::_is_solution_location_center)
  {
    partition_data = grid.make_partition_data(THIS::_partition_order);
  }
  else
  {
    partition_data = grid.make_discrete_partition_data(THIS::_partition_order);
  }

  auto& nodes          = partition_data.nodes;
  auto& connectivities = partition_data.connectivities;

  for (auto& connectivity : connectivities)
  {
    for (auto& number : connectivity)
    {
      number += 1; // Tecplot node number starts from 1
    }
  }

  const auto num_nodes       = nodes.num_nodes();
  const auto num_elements    = connectivities.size();
  const auto coordinates_ptr = nodes.coordinates_ptr();

  ms::tecplot::Grid_Data grid_data(dim, num_nodes, num_elements, coordinates_ptr, connectivities);
  ms::tecplot::Writer::write_grid_file(std::move(grid_data));
}
