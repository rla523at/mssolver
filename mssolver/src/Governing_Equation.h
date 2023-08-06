#pragma once
#include "msmath/Matrix.h"
#include "msmath/Vector.h"
#include <string>

class Governing_Equation
{
public:
  virtual void cal_characteristic_velocity_vector(ms::math::Vector_Wrapper characteristic_velocity_vec, const ms::math::Vector_Const_Wrapper solution) const = 0;
  virtual void cal_flux(ms::math::Matrix_Wrapper flux, const ms::math::Vector_Const_Wrapper solution) const                                                  = 0;
  virtual int  dimension(void) const                                                                                                                         = 0;
  virtual void extend_solution(ms::math::Vector_Wrapper extended_solution, const ms::math::Vector_Const_Wrapper equation_solution) const                     = 0;
  virtual void solution_names(std::string* names) const                                                                                                      = 0;
  virtual int  num_equations(void) const                                                                                                                     = 0;
  virtual int  num_extended_solutions(void) const                                                                                                            = 0;

protected:
  virtual ~Governing_Equation(void) = default;
};

// enum class Governing_Equation_Type
//{
//   Linear_Advection,
//   Burgers,
//   Euler,
//   Not_Supported
// };
//
// class Governing_Equation
//{
// public: // Query
//   const std::vector<std::string>& get_solution_names(void) const { return solution_names_; };
//   int                             num_equations(void) const { return this->num_equations_; };
//   int                             num_solutions(void) const { return this->num_solutions_; };
//   int                             space_dimension(void) const { return this->space_dimension_; };
//   Governing_Equation_Type         type(void) const { return this->type_; };
//
//   virtual std::vector<std::vector<double>> calculate_cell_index_to_coordinate_projected_maximum_lambdas_table(const std::vector<Euclidean_Vector>& P0_solutions) const abstract;
//   virtual double                           calculate_inner_face_maximum_lambda(const Euclidean_Vector& oc_solution, const Euclidean_Vector& nc_solution, const Euclidean_Vector& nomal_vector) const abstract;
//   virtual Matrix                           calculate_physical_flux(const Euclidean_Vector& solution) const abstract;
//   virtual void                             calculate_physical_flux(Matrix& physical_flux, const Euclidean_Vector& solution) const abstract;
//   virtual void                             extend_to_solution(Euclidean_Vector& governing_equation_solution) const abstract;
//   virtual void                             extend_to_solution(const double* GE_solution_values, double* solution_values) const abstract;
//   virtual short                            pressure_index(void) const abstract;
//
// protected:
//   int                      num_equations_   = 0;
//   int                      num_solutions_   = 0;
//   int                      space_dimension_ = 0;
//   std::vector<std::string> solution_names_;
//   Governing_Equation_Type  type_ = Governing_Equation_Type::Not_Supported;
// };