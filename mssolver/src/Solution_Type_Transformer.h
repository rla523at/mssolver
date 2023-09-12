#pragma once
#include "msmath/Vector.h"

class Solution_Type_Transformer
{
  virtual void transform_solution_type(ms::math::Vector_Wrap conservative_solution, const ms::math::Vector_View equation_solution) const = 0;
};