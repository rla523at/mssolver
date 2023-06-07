#pragma once
#include "msgrid/Grid.h"
#include "msmath/Vector.h"

class Semi_Discrete_Equation
{
public:
  // virtual std::vector<double>      calculate_error_norms(const ms::grid::Grid& grid, const double end_time) const = 0;
  // virtual void                     reconstruct(void)                                                              = 0;
  virtual void                     update_residual(void) = 0;
  virtual ms::math::Vector_Wrapper solution_vector(void) = 0;

public:
  virtual double                         calculate_time_step(void) const   = 0;
  virtual ms::math::Vector_Const_Wrapper const_residual_vector(void) const = 0;
  // virtual ms::math::Vector<>             copy_solution_vector(void) const        = 0;
  // virtual ms::math::Vector<>             copy_RHS_vector(void) const             = 0;
};

// #include "Boundaries.h"
// #include "Boundary_Flux_Function_Factory.h"
// #include "Cells.h"
// #include "Error.h"
// #include "Governing_Equation_Impl.h"
// #include "Initial_Condition_Impl.h"
// #include "Inner_Faces.h"
// #include "Post_Processor.h"
// #include "Reconstruction_Factory.h"
//
// class Semi_Discrete_Equation
//{
// public: // Command
//   virtual Euclidean_Vector_Wrapper discrete_solution_vector_wrapper(void) abstract;
//   virtual void                     reconstruct(void) abstract;
//   virtual void                     calculate_RHS(void) abstract;
//
// public: // Query
//   virtual double                            calculate_time_step(void) const abstract;
//   virtual Euclidean_Vector                  discrete_solution_vector(void) const abstract;
//   virtual Constant_Euclidean_Vector_Wrapper discrete_solution_constant_vector_wrapper(void) const abstract;
//   virtual Constant_Euclidean_Vector_Wrapper RHS_constant_vector_wrapper(void) const abstract;
//   virtual Euclidean_Vector                  RHS_vector(void) const abstract;
//
//   virtual std::vector<double> calculate_error_norms(const Grid& grid, const double end_time) const abstract;
// };
//
// class Semi_Discrete_Equation_DG : public Semi_Discrete_Equation
//{
// public:
//   Semi_Discrete_Equation_DG(const Configuration& configuration, const Grid& grid);
//
// public: // Command
//   Euclidean_Vector_Wrapper discrete_solution_vector_wrapper(void) override;
//   void                     reconstruct(void) override;
//   void                     calculate_RHS(void) override;
//
// public: // Query
//   double                            calculate_time_step(void) const override;
//   Euclidean_Vector                  discrete_solution_vector(void) const override;
//   Constant_Euclidean_Vector_Wrapper discrete_solution_constant_vector_wrapper(void) const override;
//   Constant_Euclidean_Vector_Wrapper RHS_constant_vector_wrapper(void) const override;
//   Euclidean_Vector                  RHS_vector(void) const override;
//
//   std::vector<double> calculate_error_norms(const Grid& grid, const double end_time) const override;
//
// private:
//   // Concrete class이지만 기본 생성자가 없음으로 unique ptr을 활용
//   std::unique_ptr<Discrete_Solution_DG> discrete_solution_;
//   std::unique_ptr<Cells_DG>             cells_;
//   std::unique_ptr<Boundaries_DG>        boundaries_;
//   std::unique_ptr<Inner_Faces_DG>       inner_faces_;
//   std::unique_ptr<Residual>             RHS_;
//
//   // Abstract class
//   std::unique_ptr<Reconstruction_DG> reconstruction_;
//   std::unique_ptr<Error>             error_;
// };
//
// class Semi_Discrete_Equation_Factory
//{
// public:
//   static std::unique_ptr<Semi_Discrete_Equation> make_unique(const Configuration& configuration, const Grid& grid);
// };