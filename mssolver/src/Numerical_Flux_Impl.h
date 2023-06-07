#pragma once
#include "Numerical_Flux.h"

#include "msmath/Matrix.h"
#include <memory>

class Linear_Advection;

// Numerical Flux Function을 만들 때, Governing Equation이 무엇인지 필요하지 않다고 생각했지만 사실은 아니였다...!
// Numerical Flux Function을 만들 때, Governing Equation이 무엇인지에 대한 정보가 필요할 수도 있다.
// Numerical Flux Function은 어디에서 만들어지는가 ?

class Godunov_Flux_Linear_Advection : public Numerical_Flux
{
public:
  Godunov_Flux_Linear_Advection(const std::shared_ptr<Linear_Advection>& governing_equation);

public:
  void calculate(double* numerical_flux_ptr, const ms::math::Vector_Const_Wrapper oc_solution, const ms::math::Vector_Const_Wrapper nc_solution, const ms::math::Vector_Const_Wrapper normal_vector) const override;

private:
  std::shared_ptr<Linear_Advection> _linear_advection;
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