#include "Solution_Type_Transformer_Impl.h"

#include "Governing_Equation.h"

void To_Conservative_Solution::transform_solution_type(ms::math::Vector_Wrap conservative_solution, const ms::math::Vector_View equation_solution) const
{
  this->_governing_equation_sptr->to_conservative_solution(conservative_solution, equation_solution);
}

void To_Extended_Solution::transform_solution_type(ms::math::Vector_Wrap extended_solution, const ms::math::Vector_View equation_solution) const
{
  this->_governing_equation_sptr->to_extended_solution(extended_solution, equation_solution);
}

void To_Primitive_Solution::transform_solution_type(ms::math::Vector_Wrap primitive_solution, const ms::math::Vector_View equation_solution) const
{
  this->_governing_equation_sptr->to_primitive_solution(primitive_solution, equation_solution);
}
