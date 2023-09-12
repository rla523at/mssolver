#include "Radii_Calculator.h"

double Radii_Calculator_1D::calculate(const double* projected_volumes, const ms::math::Vector_View characteristic_velocity_vec) const
{
  return characteristic_velocity_vec[0];
}

double Radii_Calculator_2D::calculate(const double* projected_volumes, const ms::math::Vector_View characteristic_velocity_vec) const
{
  const auto vol_x = projected_volumes[0];
  const auto vol_y = projected_volumes[1];
  const auto vel_x = characteristic_velocity_vec[0];
  const auto vel_y = characteristic_velocity_vec[1];

  return vol_y * vel_x + vol_x * vel_y;
}