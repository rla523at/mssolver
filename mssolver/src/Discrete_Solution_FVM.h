#pragma once
#include "msconfig/Data.h"
#include "msgrid/Grid.h"
#include "msmath/Vector.h"

// forward declaration
class Governing_Equation;
/*




*/

// class definition
class Discrete_Solution_FVM
{
public:
  Discrete_Solution_FVM(const ms::config::Data& problem_data, const ms::grid::Grid& grid);

public:
  ms::math::Vector_Wrapper solution_vector(void);

public:
  void                           cal_characteristic_velocity(double* characteristic_velocity, const int cell_number) const;
  ms::math::Vector_Const_Wrapper const_solution_vector(const int cell_number) const;
  int                            num_DOF(void) const;

private:
  std::shared_ptr<Governing_Equation> _governing_equation;
  std::vector<double>                 _solution_values;
};