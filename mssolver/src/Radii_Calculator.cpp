#include "Radii_Calculator.h"

double Radii_Calculator_1D::calculate(const double* projected_volumes, const double* characteristic_velocity) const
{
  return characteristic_velocity[0];
}

double Radii_Calculator_2D::calculate(const double* projected_volumes, const double* characteristic_velocity) const
{
  const auto vol_x = projected_volumes[0];
  const auto vol_y = projected_volumes[1];
  const auto vel_x = characteristic_velocity[0];
  const auto vel_y = characteristic_velocity[1];

  return vol_y * vel_x + vol_x * vel_y;
}