#pragma once
#include "msmath/Vector.h"

class Numerical_Flux
{
public:
  virtual void calculate(ms::math::Vector_Wrapper numerical_flux_vec, const ms::math::Vector_Const_Wrapper oc_solution_vec, const ms::math::Vector_Const_Wrapper nc_solution_vec, const ms::math::Vector_Const_Wrapper normal_vec) = 0;
};
