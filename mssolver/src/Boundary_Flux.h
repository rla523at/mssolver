#pragma once
#include "msmath/Vector.h"

class Boundary_Flux
{
public:
  virtual ~Boundary_Flux(void) = default;

public:
  virtual void calculate(ms::math::Vector_Wrap boundary_flux_vec, const ms::math::Vector_View oc_solution_vec, const ms::math::Vector_View normal_vec) const = 0;
};