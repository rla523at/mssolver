#pragma once
#include "msconfig/Data.h"
#include "msgrid/Grid.h"
#include "msmath/Vector.h"

// forward declaration
class Governing_Equation;
/*










*/

// Discrete_Solution_FVM class definition
// solution : conservative solutio
class Discrete_Solution_FVM
{
public:
  Discrete_Solution_FVM(const ms::config::Data& problem_data, const ms::grid::Grid& grid);

public:
  ms::math::Vector_Wrap solution_vector_view(void);

public:
  void                  cal_characteristic_velocity(ms::math::Vector_Wrap characteristic_velocity_vec, const int cell_number) const;
  ms::math::Vector_View solution_vector_view(const int cell_number) const;
  void                  center_extended_solution(ms::math::Vector_Wrap extended_solution, const int cell_number) const;
  void                  node_extended_solution(ms::math::Vector_Wrap node_extended_solution, const int cell_number) const;
  int                   num_cells(void) const;
  int                   num_DOF(void) const;
  int                   num_extended_solution(void) const;

private:
  std::span<const double> solution_values_part(const int cell_number) const;

private:
  int                                 _num_cells;
  std::shared_ptr<Governing_Equation> _governing_equation;
  std::vector<double>                 _solution_values; // num_cells X num_equations
};