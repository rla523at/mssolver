#include "Post.h"

#include "Discrete_Solution_FVM.h"
#include "Governing_Equation.h"
#include "Governing_Equation_Container.h"
#include "Solution_At_Location.h"
#include "Solution_At_Location_Container.h"
#include "Solution_Type_Transformer.h"
#include "Solution_Type_Transformer_Container.h"
#include "msexception/Exception.h"
#include "msstring/string.h"
#include "mstecplot/Writer.h"

void Post::initialize(const ms::config::Data& problem_data, const ms::config::Data& post_data)
{
  // initialize post solution
  const auto& solution_data = post_data.get_data<ms::config::Data>("SOLUTION");
  const auto& type          = solution_data.get_data<std::string>("TYPE");
  const auto& display_type  = solution_data.get_data<std::string>("DISPLAY_TYPE");
  const auto& location      = solution_data.get_data<std::string>("LOCATION");

  const auto TYPE         = ms::string::upper_case(type);
  const auto DISPLAY_TYPE = ms::string::upper_case(display_type);
  const auto LOCATION     = ms::string::upper_case(location);

  const auto gov_eq_sptr = Governing_Equation_Container::get(problem_data);

  auto num_variables = 0;
  if (TYPE == "CONSERVATIVE")
  {
    num_variables = gov_eq_sptr->num_conservative_solutions();
    THIS::_variable_strs.resize(num_variables);
    gov_eq_sptr->conservative_solution_names(THIS::_variable_strs.data());
  }
  else if (TYPE == "PRIMITIVE")
  {
    num_variables = gov_eq_sptr->num_primitive_solutions();
    THIS::_variable_strs.resize(num_variables);
    gov_eq_sptr->primitive_solution_names(THIS::_variable_strs.data());
  }
  else if (TYPE == "EXTENDED")
  {
    num_variables = gov_eq_sptr->num_extended_solutions();
    THIS::_variable_strs.resize(num_variables);
    gov_eq_sptr->extended_solution_names(THIS::_variable_strs.data());
  }
  else
  {
    EXCEPTION(std::string(type) + " is not supported solution type");
  }

  if (DISPLAY_TYPE == "CONTINUOUS")
  {
    REQUIRE(ms::string::compare_icase(location, "CENTER"), "Continuous display type is only supported at center");
    THIS::_is_continuous_display_type = true;
    THIS::_var_locations.resize(num_variables, ms::tecplot::Variable_Location::CELL_CENTER);
  }
  else if (DISPLAY_TYPE == "DISCRETE")
  {
    THIS::_is_continuous_display_type = false;

    if (LOCATION == "CENTER")
    {
      THIS::_var_locations.resize(num_variables, ms::tecplot::Variable_Location::CELL_CENTER);
    }
    else if (LOCATION == "NODE")
    {
      THIS::_var_locations.resize(num_variables, ms::tecplot::Variable_Location::NODE);
    }
    else
    {
      EXCEPTION(location + " is not supproted variable location");
    }
  }
  else
  {
    EXCEPTION(display_type + " is not supproted variable display type");
  }

  THIS::_solution_at_location_sptr      = Solution_At_Location_Container::get_sptr(location);
  THIS::_solution_type_transformer_sptr = Solution_Type_Transformer_Container::get_sptr(type, gov_eq_sptr);
  THIS::_partition_order                = post_data.get_data<int>("PARTITION_ORDER");

  // set tecplot configuration
  const auto& format      = post_data.get_data<std::string>("Format");
  const auto& folder_path = post_data.get_data<std::string>("folder_path");
  const auto& title       = post_data.get_data<std::string>("title");

  ms::tecplot::Configuration config;

  const auto FORMAT = ms::string::upper_case(format);

  if (FORMAT == "ASCII")
  {
    config.file_format = ms::tecplot::File_Format::ASCII;
  }
  else if (FORMAT == "BINARY")
  {
    config.file_format = ms::tecplot::File_Format::Binary;
  }
  else
  {
    EXCEPTION(format + " is not supproted post file format");
  }

  config.folder_path = folder_path;
  config.title       = title;

  ms::tecplot::Writer::set_configuration(std::move(config));

  THIS::_is_initialized = true;
}

void Post::write_grid(const ms::grid::Grid& grid)
{
  REQUIRE(THIS::_is_initialized, "initialize should be call first");

  const auto dim = grid.dimension();

  ms::geo::Partition_Data partition_data;
  if (THIS::_is_continuous_display_type)
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

void Post::write_solution(const Discrete_Solution_FVM& solution, const double time)
{
  const auto solution_values = THIS::_post_solution_maker_uptr->make_post_solution_values(solution);

  // ms::tecplot::Solution_Data solution_data(values_ptr, time, THIS::_variable_strs, THIS::_var_locations.data());
  // ms::tecplot::Writer::write_solution_file(std::move(solution_data));
}
