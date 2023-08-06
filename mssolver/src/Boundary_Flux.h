#pragma once
#include "msmath/Vector.h"

class Boundary_Flux
{
public:
  virtual ~Boundary_Flux(void) = default;

public:
  virtual void calculate(ms::math::Vector_Wrapper boundary_flux_vec, const ms::math::Vector_Const_Wrapper oc_solution_vec, const ms::math::Vector_Const_Wrapper normal_vec) const = 0;
};