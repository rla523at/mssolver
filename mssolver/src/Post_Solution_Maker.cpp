#include "Post_Solution_Maker.h"

#include "Discrete_Solution_FVM.h"

std::vector<double> Post_Solution_Maker_Center::make_post_solution_values(const Discrete_Solution_FVM& solution)
{
  // cell center solution values format
  // num variables X num_post_cells
  // ((v1)1, ..., (v1)nc , ... , (vn)1,...,(vn)nc) (variable location = CELLCENTERD)

  const auto            num_extended_soltuion = solution.num_extended_solution();
  const auto            num_cells             = solution.num_cells();
  std::vector<double>   extended_solution_values(num_extended_soltuion * num_cells);
  ms::math::Vector_Wrap extended_solution_values_wrap = extended_solution_values;

  for (int i = 0; i < num_cells; ++i)
  {
    const auto start_position                = i;
    const auto inc                           = num_cells;
    const auto num_values                    = num_extended_soltuion;
    const auto cell_center_extended_solution = extended_solution_values_wrap.sub_wrap(start_position, inc, num_values);

    solution.center_extended_solution(cell_center_extended_solution, i);
  }
}

std::vector<double> Post_Solution_Maker_Node::make_post_solution_values(const Discrete_Solution_FVM& solution)
{
  const auto& grid = solution.grid();

  std::vector<double> solution_values(grid.num_nodes());

  for (int i = 0; i < grid.num_nodes(); ++i)
  {
    solution_values[i] = solution.value(i);
  }

  return solution_values;
}