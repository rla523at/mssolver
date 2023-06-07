#include "Numerical_Flux_Impl.h"

#include "Governing_Equation_Impl.h"
#include "msmath/BLAS.h"
#include <iostream>

Godunov_Flux_Linear_Advection::Godunov_Flux_Linear_Advection(const std::shared_ptr<Linear_Advection>& governing_equation)
    : _linear_advection(governing_equation) {};

void Godunov_Flux_Linear_Advection::calculate(double* numerical_flux_ptr, const ms::math::Vector_Const_Wrapper oc_solution, const ms::math::Vector_Const_Wrapper nc_solution, const ms::math::Vector_Const_Wrapper normal_vector) const
{
  const auto advection_velocity_v = this->_linear_advection->advection_velocity_vector();

  const auto value = advection_velocity_v.inner_product(normal_vector);

  if (0 < value)
  {
    numerical_flux_ptr[0] = value * oc_solution[0];
  }
  else
  {
    numerical_flux_ptr[0] = value * nc_solution[0];
  }
}
//
// Euclidean_Vector LLF::calculate(const Euclidean_Vector& oc_solution, const Euclidean_Vector& nc_solution, const Euclidean_Vector& normal_vector) const
//{
//  this->governing_equation_->calculate_physical_flux(this->oc_physical_flux_, oc_solution);
//  this->governing_equation_->calculate_physical_flux(this->nc_physical_flux_, nc_solution);
//  const auto inner_face_maximum_lambda = this->governing_equation_->calculate_inner_face_maximum_lambda(oc_solution, nc_solution, normal_vector);
//
//  this->central_normal_flux_.initalize();
//  ms::mpm(this->oc_physical_flux_, this->nc_physical_flux_, this->central_flux_.data());
//  ms::mv(this->central_flux_, normal_vector, this->central_normal_flux_.data());
//  this->central_normal_flux_ *= 0.5;
//
//  ms::vmv(oc_solution, nc_solution, this->correction_flux_.data());
//  this->correction_flux_ *= (0.5 * inner_face_maximum_lambda);
//
//  return this->central_normal_flux_ + this->correction_flux_;
//}
//
// void LLF::calculate(double* numerical_flux_ptr, const Euclidean_Vector& oc_solution, const Euclidean_Vector& nc_solution, const Euclidean_Vector& normal_vector) const
//{
//  this->governing_equation_->calculate_physical_flux(this->oc_physical_flux_, oc_solution);
//  this->governing_equation_->calculate_physical_flux(this->nc_physical_flux_, nc_solution);
//  const auto inner_face_maximum_lambda = this->governing_equation_->calculate_inner_face_maximum_lambda(oc_solution, nc_solution, normal_vector);
//
//  this->central_normal_flux_.initalize();
//  ms::mpm(this->oc_physical_flux_, this->nc_physical_flux_, this->central_flux_.data());
//  ms::mv(this->central_flux_, normal_vector, this->central_normal_flux_.data());
//  this->central_normal_flux_ *= 0.5;
//
//  const auto n = static_cast<int>(this->correction_flux_.size());
//  ms::BLAS::x_minus_y(n, oc_solution.data(), nc_solution.data(), this->correction_flux_.data());
//  // ms::vmv(oc_solution, nc_solution, this->correction_flux_.data()); //bug!!!!
//  this->correction_flux_ *= (0.5 * inner_face_maximum_lambda);
//
//  ms::BLAS::x_plus_y(n, this->central_normal_flux_.data(), this->correction_flux_.data(), numerical_flux_ptr);
//  // ms::vpv(this->central_normal_flux_, this->correction_flux_, numerical_flux_ptr);
//}
//
