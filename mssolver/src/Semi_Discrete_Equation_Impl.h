#pragma once
#include "Discrete_Solution_FVM.h"
#include "Semi_Discrete_Equation.h"
#include "msmath/Vector.h"

// forward declaration
class Time_Step_Calculator;
class Boundary_Flux;
class Numerical_Flux;

// class declaration
class Semi_Discrete_Equation_FVM : public Semi_Discrete_Equation
{
public:
  Semi_Discrete_Equation_FVM(const ms::config::Data& problem_data, const ms::config::Data& time_step_data, const ms::grid::Grid& grid);

public:
  // std::vector<double>      calculate_error_norms(const ms::grid::Grid& grid, const double end_time) const override;
  //  void                     reconstruct(void) override;
  void                     update_residual(void) override;
  ms::math::Vector_Wrap solution_vector_view(void) override;

public:
  double                         calculate_allowable_time_step(void) const override;
  ms::math::Vector_View const_residual_vector(void) const override;
  void                           post_solution(const double time) const override;
  // ms::math::Vector<>             copy_solution_vector(void) const override;
  // ms::math::Vector_View const_RHS_vector(void) const override;
  // ms::math::Vector<>             copy_RHS_vector(void) const override;

private:
  ms::math::Vector_Wrap residual_vector(const int cell_index);

private:
  int                                   _dimension;
  Discrete_Solution_FVM                 _solution;
  std::vector<double>                   _residual;
  std::unique_ptr<Time_Step_Calculator> _time_step_calculator_ptr;
  std::shared_ptr<Numerical_Flux>       _numerical_flux_ptr;
  int                                   _num_equations;

  // data for cells
  int                 _num_cells;
  std::vector<double> _cell_number_to_reciprocal_volume;

  // data for boundaries
  int                                         _num_boundaries;
  std::vector<int>                            _bdry_index_to_oc_number;
  std::vector<std::unique_ptr<Boundary_Flux>> _bdry_index_to_flux_ptr;
  std::vector<std::vector<double>>            _bdry_index_to_normal;
  std::vector<double>                         _bdry_index_to_volume;

  // data for innerfaces
  int                              _num_inter_cell_faces;
  std::vector<std::pair<int, int>> _infc_number_to_oc_nc_number_pair;
  std::vector<std::vector<double>> _infc_index_to_normal;
  std::vector<double>              _infc_number_to_volume;
};