#include "Solution_At_Location_Impl.h"

#include "Discrete_Solution_FVM.h"

void Solution_At_Center::solution(const Discrete_Solution_FVM& solution, ms::math::Vector_Wrap sol, const int cell_number) const
{
  solution.center_extended_solution(sol, cell_number);
}

void Solution_At_Node::solution(const Discrete_Solution_FVM& solution, ms::math::Vector_Wrap sol, const int cell_number) const
{
  solution.node_extended_solution(sol, cell_number);
}
