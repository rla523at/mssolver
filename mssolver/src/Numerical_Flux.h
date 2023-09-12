#pragma once
#include "msmath/Vector.h"

class Numerical_Flux
{
public:
  virtual void calculate(ms::math::Vector_Wrap numerical_flux_vec, const ms::math::Vector_View oc_solution_vec, const ms::math::Vector_View nc_solution_vec, const ms::math::Vector_View normal_vec) = 0;
};
