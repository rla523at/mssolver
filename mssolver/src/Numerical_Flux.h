#pragma once
#include "msmath/Vector.h"

class Numerical_Flux
{
public:
  virtual void calculate(double* numerical_flux_ptr, const ms::math::Vector_Const_Wrapper oc_solution, const ms::math::Vector_Const_Wrapper nc_solution, const ms::math::Vector_Const_Wrapper normal_vector) const = 0;
};
