#include "Discrete_Solution_FVM.h"

#include "Governing_Equation.h"
#include "Governing_Equation_Container.h"
#include "Initial_Condition.h"
#include "Initial_Condition_Container.h"

Discrete_Solution_FVM::Discrete_Solution_FVM(const ms::config::Data& problem_data, const ms::grid::Grid& grid)
    : _governing_equation(Governing_Equation_Container::get_sptr(problem_data))
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

ms::math::Vector_Wrap Discrete_Solution_FVM::solution_vector_view(void)
{
  return _solution_values;
}

void Discrete_Solution_FVM::cal_characteristic_velocity(ms::math::Vector_Wrap characteristic_velocity_vec, const int cell_number) const
{
  const auto sol = this->solution_vector_view(cell_number);
  this->_governing_equation->cal_characteristic_velocity_vector(characteristic_velocity_vec, sol);
}

ms::math::Vector_View Discrete_Solution_FVM::solution_vector_view(const int cell_number) const
{
  const auto solution_values_part = this->solution_values_part(cell_number);
  const auto solution_vector_view = ms::math::Vector_View(solution_values_part);
  return solution_vector_view;
}

void Discrete_Solution_FVM::center_extended_solution(ms::math::Vector_Wrap extended_solution, const int cell_number) const
{
  // extended_solution : conservative solution + primitive solution
  this->_governing_equation->to_extend_solution(extended_solution, this->solution_vector_view(cell_number));
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

std::span<const double> Discrete_Solution_FVM::solution_values_part(const int cell_number) const
{
  const auto num_sols = this->_governing_equation->num_equations();

  const auto start_index = cell_number * num_sols;
  const auto num_values  = num_sols;

  const auto solution_values_view = std::span<const double>(this->_solution_values);
  return solution_values_view.subspan(start_index, num_values);
}
