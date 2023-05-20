#pragma once
#include "Discrete_Solution_FVM.h"
#include "Semi_Discrete_Equation.h"
#include "msmath/Vector.h"

// forward declaration
class Time_Step_Calculator;
class Boundary_Flux_Function;
class Numerical_Flux_Function;

// class declaration
class Semi_Discrete_Equation_FVM : public Semi_Discrete_Equation
{
public:
  Semi_Discrete_Equation_FVM(const ms::config::Data& problem_data, const ms::config::Data& time_step_data, const ms::grid::Grid& grid);

public:
  // std::vector<double>      calculate_error_norms(const ms::grid::Grid& grid, const double end_time) const override;
  //  void                     reconstruct(void) override;
  void update_residual(void) override;
  // ms::math::Vector_Wrapper solution_vector(void) override;

public:
  double calculate_time_step(void) const override;
  // ms::math::Vector<>             copy_solution_vector(void) const override;
  // ms::math::Vector_Const_Wrapper const_RHS_vector(void) const override;
  // ms::math::Vector<>             copy_RHS_vector(void) const override;

private:
  ms::math::Vector_Wrapper residual_vector(const int cell_index);

private:
  // data for cells
  int                 _num_cells;
  std::vector<double> _cell_index_to_reciprocal_volume;

  // data for boundaries
  int                                 _num_boundaries;
  std::vector<int>                    _bdry_index_to_oc_index;
  std::vector<Boundary_Flux_Function> _bdry_index_to_flux_function;
  std::vector<std::vector<double>>    _bdry_index_to_normal;
  std::vector<double>                 _bdry_index_to_volume;

  // data for innerfaces
  int                              _num_inner_faces;
  std::vector<std::pair<int, int>> _infc_index_to_oc_nc_index;
  Numerical_Flux_Function          _numerical_flux_function;
  std::vector<std::vector<double>> _infc_index_to_normal;
  std::vector<double>              _infc_index_to_volume;

  Discrete_Solution_FVM                 _solution;
  std::unique_ptr<Time_Step_Calculator> _time_step_calculator_uptr;
  std::vector<double>                   _residual;
};