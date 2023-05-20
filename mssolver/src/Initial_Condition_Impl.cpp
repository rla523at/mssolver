#include "Initial_Condition_Impl.h"

#include "msexception/Exception.h"
#include <numbers>

void Constant1::calculate_solution(double* solution, const double* coordinates) const
{
  solution[0] = 1.0;
}

Sine_Wave::Sine_Wave(const double* wave_lengths, const int dimension)
{
  REQUIRE(0 < dimension, "dimension should be natural number");

  this->_dimension = dimension;
  this->_wave_numbers.resize(this->_dimension);

  for (int i = 0; i < this->_dimension; ++i)
  {
    this->_wave_numbers[i] = 2 * std::numbers::pi / wave_lengths[i];
  }
}

void Sine_Wave::calculate_solution(double* solution, const double* coordinates) const
{
  auto val = 1.0;

  for (int i = 0; i < this->_dimension; ++i)
  {
    val *= std::sin(this->_wave_numbers[i] * coordinates[i]);
  }

  solution[0] = val;
}
//
//Euclidean_Vector Square_Wave::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  for (ushort i = 0; i < this->space_dimension_; ++i)
//  {
//    if (space_vector[i] < 0.25 || 0.75 < space_vector[i])
//    {
//      return {0};
//    }
//  }
//  return {1};
//}
//
//Circle_Wave::Circle_Wave(const ushort space_dimension)
//    : space_dimension_(space_dimension)
//{
//  this->center_v_ = std::vector<double>(this->space_dimension_, 0.5);
//};
//
//Euclidean_Vector Circle_Wave::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto shock_radius = 0.25;
//
//  const auto distance_from_center = (space_vector - this->center_v_).L2_norm();
//
//  if (distance_from_center <= shock_radius)
//  {
//    return {1};
//  }
//  else
//  {
//    return {0};
//  }
//}
//
//Gaussian_Wave::Gaussian_Wave(const ushort space_dimension)
//    : space_dimension_(space_dimension)
//{
//  this->center_v_ = std::vector<double>(this->space_dimension_, 0.5);
//};
//
//Euclidean_Vector Gaussian_Wave::calculate_solution(const Euclidean_Vector& point_v) const
//{
//  constexpr auto beta              = 20.0;
//  const auto     center_to_point_v = point_v - this->center_v_;
//
//  return {std::exp(-beta * center_to_point_v.inner_product(center_to_point_v))};
//}
//
//Euclidean_Vector Euler_Shocktube_2D::primitive_to_conservative(const Euclidean_Vector& primitive_variable) const
//{
//  constexpr auto gamma = 1.4;
//  constexpr auto c     = 1 / (gamma - 1);
//
//  const auto rho = primitive_variable[0];
//  const auto u   = primitive_variable[1];
//  const auto v   = primitive_variable[2];
//  const auto p   = primitive_variable[3];
//
//  const auto rhou = rho * u;
//  const auto rhov = rho * v;
//  const auto rhoE = p * c + 0.5 * (rhou * u + rhov * v);
//
//  return {rho, rhou, rhov, rhoE};
//}
//
//Euclidean_Vector Euler_Shocktube_3D::primitive_to_conservative(const Euclidean_Vector& primitive_variable) const
//{
//  constexpr auto gamma = 1.4;
//  constexpr auto c     = 1 / (gamma - 1);
//
//  const auto rho = primitive_variable[0];
//  const auto u   = primitive_variable[1];
//  const auto v   = primitive_variable[2];
//  const auto w   = primitive_variable[3];
//  const auto p   = primitive_variable[4];
//
//  const auto rhou = rho * u;
//  const auto rhov = rho * v;
//  const auto rhow = rho * w;
//  const auto rhoE = p * c + 0.5 * (rhou * u + rhov * v + rhow * w);
//
//  return {rho, rhou, rhov, rhow, rhoE};
//}
//
//Euclidean_Vector SOD_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.5;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 1.0;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//  else
//  {
//    constexpr auto rho = 0.125;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 0.1;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//}
//
//Euclidean_Vector SOD_3D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.5;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 1.0;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//  else
//  {
//    constexpr auto rho = 0.125;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 0.1;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//}
//
//Euclidean_Vector Modified_SOD_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.3;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.75;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 1.0;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//  else
//  {
//    constexpr auto rho = 0.125;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 0.1;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//}
//
//Euclidean_Vector Modified_SOD_3D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.3;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.75;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 1.0;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//  else
//  {
//    constexpr auto rho = 0.125;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 0.1;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//}
//
//Euclidean_Vector Supersonic_Expansion_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.5;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho  = 1.0;
//    constexpr auto u    = -2.0;
//    constexpr auto v    = 0.0;
//    constexpr auto rhoE = 3.0;
//
//    constexpr auto rhou = rho * u;
//    constexpr auto rhov = rho * v;
//
//    return {rho, rhou, rhov, rhoE};
//  }
//  else
//  {
//    constexpr auto rho  = 1.0;
//    constexpr auto u    = 2.0;
//    constexpr auto v    = 0.0;
//    constexpr auto rhoE = 3.0;
//
//    constexpr auto rhou = rho * u;
//    constexpr auto rhov = rho * v;
//
//    return {rho, rhou, rhov, rhoE};
//  }
//}
//
//Euclidean_Vector Supersonic_Expansion_3D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.5;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho  = 1.0;
//    constexpr auto u    = -2.0;
//    constexpr auto v    = 0.0;
//    constexpr auto w    = 0.0;
//    constexpr auto rhoE = 3.0;
//
//    constexpr auto rhou = rho * u;
//    constexpr auto rhov = rho * v;
//    constexpr auto rhow = rho * w;
//
//    return {rho, rhou, rhov, rhow, rhoE};
//  }
//  else
//  {
//    constexpr auto rho  = 1.0;
//    constexpr auto u    = 2.0;
//    constexpr auto v    = 0.0;
//    constexpr auto w    = 0.0;
//    constexpr auto rhoE = 3.0;
//
//    constexpr auto rhou = rho * u;
//    constexpr auto rhov = rho * v;
//    constexpr auto rhow = rho * w;
//
//    return {rho, rhou, rhov, rhow, rhoE};
//  }
//}
//
//Euclidean_Vector Left_Half_Blast_Wave_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.5;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 1000.0;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//  else
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 0.01;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//}
//
//Euclidean_Vector Left_Half_Blast_Wave_3D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.5;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 1000.0;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//  else
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 0.01;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//}
//
//Euclidean_Vector Double_Strong_Shock_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.4;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 5.99924;
//    constexpr auto u   = 19.5975;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 460.894;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//  else
//  {
//    constexpr auto rho = 5.99242;
//    constexpr auto u   = -6.19633;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 46.0950;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//}
//
//Euclidean_Vector Double_Strong_Shock_3D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.4;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 5.99924;
//    constexpr auto u   = 19.5975;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 460.894;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//  else
//  {
//    constexpr auto rho = 5.99242;
//    constexpr auto u   = -6.19633;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 46.0950;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//}
//
//Euclidean_Vector Slowly_Moving_Contact_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.8;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = -19.59745;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 1000.0;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//  else
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = -19.59745;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 0.01;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//}
//
//Euclidean_Vector Slowly_Moving_Contact_3D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.8;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = -19.59745;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 1000.0;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//  else
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = -19.59745;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 0.01;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//}
//
//Euclidean_Vector Harten_Lax_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.5;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 0.445;
//    constexpr auto u   = 0.698;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 3.528;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//  else
//  {
//    constexpr auto rho = 0.5;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 0.571;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//}
//
//Euclidean_Vector Harten_Lax_3D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.5;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 0.445;
//    constexpr auto u   = 0.698;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 3.528;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//  else
//  {
//    constexpr auto rho = 0.5;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 0.571;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//}
//
//Euclidean_Vector Shu_Osher_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.125;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 3.857143;
//    constexpr auto u   = 2.629369;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 10.333333;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//  else
//  {
//    const auto     rho = 1 + 0.2 * std::sin(16 * std::numbers::pi * x_coordinate);
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 1.0;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//}
//
//Euclidean_Vector Shu_Osher_3D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location = 0.125;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate <= discontinuity_location)
//  {
//    constexpr auto rho = 3.857143;
//    constexpr auto u   = 2.629369;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 10.333333;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//  else
//  {
//    const auto     rho = 1 + 0.2 * std::sin(16 * std::numbers::pi * x_coordinate);
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 1.0;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//}
//
//Euclidean_Vector Blast_Wave_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location1 = 0.1;
//  constexpr auto discontinuity_location2 = 0.9;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate < discontinuity_location1)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 1000.0;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//  else if ((discontinuity_location1 <= x_coordinate) && (x_coordinate < discontinuity_location2))
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 0.01;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//  else
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 100.0;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//}
//
//Euclidean_Vector Blast_Wave_3D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location1 = 0.1;
//  constexpr auto discontinuity_location2 = 0.9;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate < discontinuity_location1)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 1000.0;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//  else if ((discontinuity_location1 <= x_coordinate) && (x_coordinate < discontinuity_location2))
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 0.01;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//  else
//  {
//    constexpr auto rho = 1;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 100.0;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//}
//
//Euclidean_Vector Leblanc_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_location1 = 3;
//
//  const auto x_coordinate = space_vector.at(0);
//
//  if (x_coordinate < discontinuity_location1)
//  {
//    constexpr auto rho  = 1.0;
//    constexpr auto rhou = 0.0;
//    constexpr auto rhov = 0.0;
//    constexpr auto rhoE = 0.1;
//
//    return {rho, rhou, rhov, rhoE};
//  }
//  else
//  {
//    constexpr auto rho  = 1.0e-3;
//    constexpr auto rhou = 0.0;
//    constexpr auto rhov = 0.0;
//    constexpr auto rhoE = 1.0e-9;
//
//    return {rho, rhou, rhov, rhoE};
//  }
//}
//
//Euclidean_Vector Explosion_2D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_radius = 0.4;
//
//  const auto distance_from_origin = space_vector.L2_norm();
//
//  if (distance_from_origin <= discontinuity_radius)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 1.0;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//  else
//  {
//    constexpr auto rho = 0.125;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto p   = 0.1;
//
//    return this->primitive_to_conservative({rho, u, v, p});
//  }
//}
//
//Euclidean_Vector Explosion_3D::calculate_solution(const Euclidean_Vector& space_vector) const
//{
//  constexpr auto discontinuity_radius = 0.4;
//
//  const auto distance_from_origin = space_vector.L2_norm();
//
//  if (distance_from_origin <= discontinuity_radius)
//  {
//    constexpr auto rho = 1.0;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 1.0;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//  else
//  {
//    constexpr auto rho = 0.125;
//    constexpr auto u   = 0.0;
//    constexpr auto v   = 0.0;
//    constexpr auto w   = 0.0;
//    constexpr auto p   = 0.1;
//
//    return this->primitive_to_conservative({rho, u, v, w, p});
//  }
//}
//
//std::unique_ptr<Initial_Condition> Initial_Condition_Factory::make_unique(const Configuration& configuration)
//{
//  const auto& name            = configuration.get_initial_condition();
//  const auto  space_dimension = configuration.space_dimension();
//
//  if (ms::compare_icase(name, "constant1"))
//  {
//    return std::make_unique<Constant1>();
//  }
//  else if (ms::compare_icase(name, "sine_wave"))
//  {
//    const auto wave_lengths_ptr = configuration.wave_lengths_ptr();
//
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Sine_Wave_2D>(wave_lengths_ptr);
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Sine_Wave_3D>(wave_lengths_ptr);
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "square"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Square_Wave_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Square_Wave_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "circle"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Circle_Wave_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Circle_Wave_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "gaussian"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Gaussian_Wave_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Gaussian_Wave_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "SOD"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<SOD_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<SOD_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "Modified_SOD"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Modified_SOD_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Modified_SOD_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "Supersonic_Expansion"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Supersonic_Expansion_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Supersonic_Expansion_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "Left_Half_Blast_Wave"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Left_Half_Blast_Wave_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Left_Half_Blast_Wave_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "Double_Strong_Shock"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Double_Strong_Shock_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Double_Strong_Shock_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "Slowly_Moving_Contact"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Slowly_Moving_Contact_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Slowly_Moving_Contact_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "Harten_Lax"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Harten_Lax_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Harten_Lax_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "Shu_Osher"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Shu_Osher_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Shu_Osher_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "Blast_Wave"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Blast_Wave_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Blast_Wave_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "Leblanc"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Leblanc_2D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else if (ms::compare_icase(name, "Explosion"))
//  {
//    if (space_dimension == 2)
//    {
//      return std::make_unique<Explosion_2D>();
//    }
//    else if (space_dimension == 3)
//    {
//      return std::make_unique<Explosion_3D>();
//    }
//    else
//    {
//      EXCEPTION("not supproted space dimension");
//      return nullptr;
//    }
//  }
//  else
//  {
//    EXCEPTION("initial condition in configuration file is not supported");
//    return nullptr;
//  }
//}
