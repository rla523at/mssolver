#include "Discrete_Solution_FVM.h"

#include "Governing_Equation.h"
#include "Governing_Equation_Container.h"
#include "Initial_Condition.h"
#include "Initial_Condition_Container.h"

Discrete_Solution_FVM::Discrete_Solution_FVM(const ms::config::Data& problem_data, const ms::grid::Grid& grid)
    : _governing_equation(Governing_Equation_Container::get(problem_data))
{
  // make initial condition
  const auto& initial_condition = *Initial_Condition_Container::get(problem_data);

  const auto dimension     = grid.dimension();
  this->_num_cells         = grid.num_cells();
  const auto num_equations = this->_governing_equation->num_equations();

  this->_solution_values.resize(this->_num_cells * num_equations);
  auto solution_ptr = this->_solution_values.data();

  std::vector<double> coordinates(dimension);
  for (int i = 0; i < this->_num_cells; ++i)
  {
    grid.cell_center(coordinates.data(), i);
    initial_condition.calculate_solution(solution_ptr, coordinates.data());
    solution_ptr += num_equations;
  }
}

ms::math::Vector_Wrapper Discrete_Solution_FVM::solution_vector(void)
{
  return _solution_values;
}

void Discrete_Solution_FVM::cal_characteristic_velocity(ms::math::Vector_Wrapper characteristic_velocity_vec, const int cell_number) const
{
  const auto sol = this->solution_vector(cell_number);
  this->_governing_equation->cal_characteristic_velocity_vector(characteristic_velocity_vec, sol);
}

ms::math::Vector_Const_Wrapper Discrete_Solution_FVM::solution_vector(const int cell_number) const
{
  const auto num_sols     = this->_governing_equation->num_equations();
  const auto jump         = cell_number * num_sols;
  const auto solution_ptr = this->_solution_values.data() + jump;

  const auto solution = ms::math::Vector_Const_Wrapper(solution_ptr, num_sols);
  return solution;
}

void Discrete_Solution_FVM::extended_solution_vector(ms::math::Vector_Wrapper extended_solution, const int cell_number) const
{
  this->_governing_equation->extend_solution(extended_solution, this->solution_vector(cell_number));
}

int Discrete_Solution_FVM::num_cells(void) const
{
  return this->_num_cells;
}

int Discrete_Solution_FVM::num_DOF(void) const
{
  return static_cast<int>(this->_solution_values.size());
}

int Discrete_Solution_FVM::num_extended_solution(void) const
{
  return this->_governing_equation->num_extended_solutions();
  }
