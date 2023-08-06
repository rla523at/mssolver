#include "Numerical_Flux_Impl.h"

#include "Governing_Equation_Impl.h"
#include "msmath/BLAS.h"

void Godunov_Flux_Linear_Advection::calculate(ms::math::Vector_Wrapper numerical_flux_vec, const ms::math::Vector_Const_Wrapper oc_solution_vec, const ms::math::Vector_Const_Wrapper nc_solution_vec, const ms::math::Vector_Const_Wrapper normal_vec)
{
  const auto advection_velocity_vec = this->_linear_advection->advection_velocity_vector();

  const auto value = advection_velocity_vec.inner_product(normal_vec);

  if (0 < value)
  {
    numerical_flux_vec[0] = value * oc_solution_vec[0];
  }
  else
  {
    numerical_flux_vec[0] = value * nc_solution_vec[0];
  }
}

Unstable_Flux::Unstable_Flux(const std::shared_ptr<Governing_Equation>& governing_equation)
    : _governing_equation_ptr(governing_equation)
{
  const auto dim      = this->_governing_equation_ptr->dimension();
  const auto num_eqs  = this->_governing_equation_ptr->num_equations();

  this->_owner_cell_physical_flux.resize(dim, num_eqs);
  this->_neighbor_cell_physical_flux.resize(dim, num_eqs);
  this->_sum_flux.resize(dim, num_eqs);
};

void Unstable_Flux::calculate(ms::math::Vector_Wrapper numerical_flux_vec, const ms::math::Vector_Const_Wrapper oc_solution_vec, const ms::math::Vector_Const_Wrapper nc_solution_vec, const ms::math::Vector_Const_Wrapper normal_vec)
{
  auto oc_flux_mat        = this->_owner_cell_physical_flux.wrapper();
  auto nc_flux_mat        = this->_neighbor_cell_physical_flux.wrapper();
  auto sum_flux_mat       = this->_sum_flux.wrapper();
  
  // 0.5(oc_flux + nc_flux) * normal
  this->_governing_equation_ptr->cal_flux(oc_flux_mat, oc_solution_vec);
  this->_governing_equation_ptr->cal_flux(nc_flux_mat, nc_solution_vec);
  ms::math::blas::mpm(sum_flux_mat, oc_flux_mat, nc_flux_mat);
  ms::math::blas::cmv(numerical_flux_vec, 0.5, sum_flux_mat, normal_vec);
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
