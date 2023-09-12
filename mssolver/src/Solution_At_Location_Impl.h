#pragma once
#include "Solution_At_Location.h"

class Solution_At_Center : public Solution_At_Location
{
public:
  void solution(const Discrete_Solution_FVM& solution, ms::math::Vector_Wrap sol, const int cell_number) const override;
};

class Solution_At_Node : public Solution_At_Location
{
public:
  void solution(const Discrete_Solution_FVM& solution, ms::math::Vector_Wrap sol, const int cell_number) const override;
};