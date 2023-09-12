#pragma once
#include "msmath/Vector.h"

// forward declaration
class Discrete_Solution_FVM;
/*










*/

class Solution_At_Location
{
  virtual void solution(const Discrete_Solution_FVM& solution, ms::math::Vector_Wrap sol, const int cell_number) const = 0;
};
