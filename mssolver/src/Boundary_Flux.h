#pragma once
#include "msmath/Vector.h"

class Boundary_Flux
{
public:
  virtual void calculate(double* bdry_flux_ptr, const ms::math::Vector_Const_Wrapper oc_solution_v, const ms::math::Vector_Const_Wrapper normal_v) const = 0;
};