#include "Discrete_Solution_FVM.h"

#include "Governing_Equation.h"
#include "Governing_Equation_Container.h"
#include "Initial_Condition.h"
#include "Initial_Condition_Container.h"


Discrete_Solution_FVM::Discrete_Solution_FVM(const ms::config::Data& problem_data, const ms::grid::Grid& grid)
    : _governing_equation(Governing_Equation_Container::get(problem_data))
{
  // make initial condition
  const auto& initial_condition = Initial_Condition_Container::get(problem_data);

  const auto dimension = grid.dimension();
  const auto num_cells = grid.num_cells();
  const auto num_sols  = this->_governing_equation.num_equations();

  this->_solution_values.resize(num_cells * num_sols);
  auto solution_ptr = this->_solution_values.data();

  std::vector<double> coordinates(dimension);
  for (int i = 0; i < num_cells; ++i)
  {
    grid.cell_center(coordinates.data(), i);
    initial_condition.calculate_solution(solution_ptr, coordinates.data());
    solution_ptr += num_sols;
  }
}

void Discrete_Solution_FVM::cal_characteristic_velocity(double* characteristic_velocity, const int cell_number) const
{
  const auto sol = this->const_solution_vector(cell_number);
  this->_governing_equation.cal_characteristic_speed(characteristic_velocity,sol);
}


ms::math::Vector_Const_Wrapper Discrete_Solution_FVM::const_solution_vector(const int cell_number) const
{
  const auto num_sols     = this->_governing_equation.num_equations();
  const auto jump         = cell_number * num_sols;
  const auto solution_ptr = this->_solution_values.data() + jump;

  const auto solution = ms::math::Vector_Const_Wrapper(solution_ptr, num_sols);
  return solution;
}
