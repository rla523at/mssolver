#pragma once
#include "Numerical_Flux.h"

#include "msmath/Matrix.h"
#include <memory>

class Governing_Equation;
class Linear_Advection;

class Godunov_Flux_Linear_Advection : public Numerical_Flux
{
public:
  Godunov_Flux_Linear_Advection(const std::shared_ptr<Linear_Advection>& governing_equation)
      : _linear_advection(governing_equation){};

public:
  void calculate(ms::math::Vector_Wrap numerical_flux_vec, const ms::math::Vector_View oc_solution_vec, const ms::math::Vector_View nc_solution_vec, const ms::math::Vector_View normal_vec) override;

private:
  std::shared_ptr<Linear_Advection> _linear_advection;
};

class Unstable_Flux : public Numerical_Flux
{
public:
  Unstable_Flux(const std::shared_ptr<Governing_Equation>& governing_equation);

public:
  void calculate(ms::math::Vector_Wrap numerical_flux_vec, const ms::math::Vector_View oc_solution_vec, const ms::math::Vector_View nc_solution_vec, const ms::math::Vector_View normal_vec) override;

private:
  std::shared_ptr<Governing_Equation> _governing_equation_ptr;

  ms::math::Matrix    _owner_cell_physical_flux    = ms::math::Matrix::null_matrix();
  ms::math::Matrix    _neighbor_cell_physical_flux = ms::math::Matrix::null_matrix();
  ms::math::Matrix    _sum_flux                    = ms::math::Matrix::null_matrix();
};

// class LLF : public Numerical_Flux_Function
//{
// public:
//   LLF(const std::shared_ptr<Governing_Equation>& governing_equation)
//       : governing_equation_(governing_equation),
//         oc_physical_flux_(governing_equation->num_equations(), governing_equation->space_dimension()),
//         nc_physical_flux_(governing_equation->num_equations(), governing_equation->space_dimension()),
//         central_flux_(governing_equation->num_equations(), governing_equation->space_dimension()),
//         central_normal_flux_(governing_equation->num_equations()),
//         correction_flux_(governing_equation->num_equations()){};
//
// public:
//   Euclidean_Vector calculate(const Euclidean_Vector& oc_solution, const Euclidean_Vector& nc_solution, const Euclidean_Vector& normal_vector) const override;
//   void             calculate(double* numerical_flux_ptr, const Euclidean_Vector& oc_solution, const Euclidean_Vector& nc_solution, const Euclidean_Vector& normal_vector) const override;
//
// private:
//   std::shared_ptr<Governing_Equation> governing_equation_;
//
//   // for construction optimization
//   mutable Matrix           oc_physical_flux_;
//   mutable Matrix           nc_physical_flux_;
//   mutable Matrix           central_flux_;
//   mutable Euclidean_Vector central_normal_flux_;
//   mutable Euclidean_Vector correction_flux_;
// };