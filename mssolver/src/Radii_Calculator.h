#pragma once
#include "msmath/Vector.h"

class Radii_Calculator
{
public:
  virtual double calculate(const double* projected_volumes, const ms::math::Vector_View characteristic_velocity_vec) const = 0;
};

class Radii_Calculator_1D : public Radii_Calculator
{
public:
  double calculate(const double* projected_volumes, const ms::math::Vector_View characteristic_velocity_vec) const;
};

class Radii_Calculator_2D : public Radii_Calculator
{
public:
  double calculate(const double* projected_volumes, const ms::math::Vector_View characteristic_velocity_vec) const;
};