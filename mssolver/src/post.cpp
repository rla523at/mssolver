#include "Post.h"

#include "Discrete_Solution_FVM.h"
#include "Governing_Equation.h"
#include "Governing_Equation_Container.h"
#include "msexception/Exception.h"
#include "msstring/string.h"
#include "mstecplot/Writer.h"

void Post::initialize(const ms::config::Data& problem_data, const ms::config::Data& post_data)
{
  // initialize from problem data
  const auto gov_eq_ptr             = Governing_Equation_Container::get(problem_data);
  const auto num_extended_solutions = gov_eq_ptr->num_extended_solutions();
  THIS::_variable_strs.resize(num_extended_solutions);

  gov_eq_ptr->solution_names(THIS::_variable_strs.data());

  // initalize from post data
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
    THIS::_var_locations.resize(num_extended_solutions, ms::tecplot::Variable_Location::CELL_CENTER);
  }
  else if (ms::string::compare_icase(sol_loc, "NODE"))
  {
    THIS::_is_solution_location_center = false;
    THIS::_var_locations.resize(num_extended_solutions, ms::tecplot::Variable_Location::NODE);
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

void Post::write_solution(const Discrete_Solution_FVM& solution, const double time)
{
  // make extended soltuions
  const auto          num_cells             = solution.num_cells();
  const auto          num_extended_soltuion = solution.num_extended_solution();
  std::vector<double> values(num_extended_soltuion * num_cells);

  const auto values_ptr = values.data();
  for (int i = 0; i < num_cells; ++i)
  {
    ms::math::Vector_Wrapper extended_solution_vector(values_ptr + i, num_extended_soltuion, num_cells);
    solution.extended_solution_vector(extended_solution_vector, i);
  }

  ms::tecplot::Solution_Data solution_data(values_ptr, time, THIS::_variable_strs, THIS::_var_locations.data());
  ms::tecplot::Writer::write_solution_file(std::move(solution_data));
}
