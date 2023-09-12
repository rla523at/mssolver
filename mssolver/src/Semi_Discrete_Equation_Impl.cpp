#include "Semi_Discrete_Equation_Impl.h"

#include "Boundary_Flux.h"
#include "Boundary_Flux_Factory.h"
#include "Governing_Equation.h"
#include "Governing_Equation_Container.h"
#include "Numerical_Flux.h"
#include "Numerical_Flux_Container.h"
#include "Post.h"
#include "Time_Step_Calculator.h"
#include "Time_Step_Calculator_Factory.h"
#include "msmath/BLAS.h"

Semi_Discrete_Equation_FVM::Semi_Discrete_Equation_FVM(const ms::config::Data& problem_data, const ms::config::Data& discretization_data, const ms::grid::Grid& grid)
    : _solution(problem_data, grid)
{
  const auto& gov_eq   = *Governing_Equation_Container::get(problem_data);
  this->_num_equations = gov_eq.num_equations();

  this->_residual.resize(this->_solution.num_DOF());

  const auto& time_step_data            = discretization_data.get_data<ms::config::Data>("time_step");
  const auto& space_discretization_data = discretization_data.get_data<ms::config::Data>("Space");
  const auto& numerical_flux_name       = space_discretization_data.get_data<std::string>("numerical_flux");

  this->_time_step_calculator_ptr = Time_Step_Calculator_Factory::make(time_step_data, grid);
  this->_numerical_flux_ptr       = Numerical_Flux_Container::get(problem_data, numerical_flux_name);

  this->_dimension = grid.dimension();

  // make cell data
  this->_num_cells = grid.num_cells();
  this->_cell_number_to_reciprocal_volume.resize(this->_num_cells);

  for (int i = 0; i < this->_num_cells; ++i)
  {
    auto& reciprocal_volume = this->_cell_number_to_reciprocal_volume[i];

    reciprocal_volume = 1.0 / grid.cell_volume(i);
  }

  // make boundary data
  this->_num_boundaries = grid.num_boundaries();
  this->_bdry_index_to_oc_number.resize(this->_num_boundaries);
  this->_bdry_index_to_flux_ptr.resize(this->_num_boundaries);
  this->_bdry_index_to_normal.resize(this->_num_boundaries);
  this->_bdry_index_to_volume.resize(this->_num_boundaries);

  for (int i = 0; i < this->_num_boundaries; ++i)
  {
    auto& oc_number = this->_bdry_index_to_oc_number[i];
    auto& flux      = this->_bdry_index_to_flux_ptr[i];
    auto& normal    = this->_bdry_index_to_normal[i];
    auto& volume    = this->_bdry_index_to_volume[i];

    auto elem_type = grid.boundary_type(i);
    normal.resize(this->_dimension);

    oc_number = grid.boundary_owner_cell_number(i);
    volume    = grid.boundary_volume(i);
    flux      = Boundary_Flux_Factory::make_unique(elem_type, this->_numerical_flux_ptr);
    grid.boundary_outward_unit_normal_at_center(normal.data(), i, oc_number);
  }

  // make inter cell face data
  this->_num_inter_cell_faces = grid.num_inter_cell_faces();
  this->_infc_number_to_oc_nc_number_pair.resize(this->_num_inter_cell_faces);
  this->_infc_number_to_volume.resize(this->_num_inter_cell_faces);
  this->_infc_index_to_normal.resize(this->_num_inter_cell_faces);

  for (int i = 0; i < this->_num_inter_cell_faces; ++i)
  {
    auto& oc_nc_number_pair = this->_infc_number_to_oc_nc_number_pair[i];
    auto& normal            = this->_infc_index_to_normal[i];
    auto& volume            = this->_infc_number_to_volume[i];

    normal.resize(this->_dimension);

    oc_nc_number_pair = grid.inter_cell_face_owner_neighbor_cell_number_pair(i);
    volume            = grid.inter_cell_face_volume(i);

    const auto oc_number = oc_nc_number_pair.first;
    grid.inter_cell_face_outward_unit_normal_at_center(normal.data(), i, oc_number);
  }
}

ms::math::Vector_Wrap Semi_Discrete_Equation_FVM::solution_vector_view(void)
{
  return this->_solution.solution_vector_view();
}

void Semi_Discrete_Equation_FVM::update_residual(void)
{
  // initialize residual
  std::fill(this->_residual.begin(), this->_residual.end(), 0.0);

  // calculate residual at boundary
  auto flux = ms::math::Vector<0>(this->_num_equations);
  for (int i = 0; i < this->_num_boundaries; ++i)
  {
    const auto  volume          = this->_bdry_index_to_volume[i];
    const auto& normal_vec      = this->_bdry_index_to_normal[i];
    const auto  oc_number       = this->_bdry_index_to_oc_number[i];
    const auto  oc_solution_vec = this->_solution.solution_vector_view(oc_number);
    auto        oc_residual_vec = this->residual_vector(oc_number);

    auto& boundary_flux_function = this->_bdry_index_to_flux_ptr[i];

    boundary_flux_function->calculate(flux.wrapper(), oc_solution_vec, normal_vec);

    ms::math::blas::x_plus_assign_cy(oc_residual_vec.data(), -volume, flux.data(), this->_num_equations);
  }

  // calculate residual at innerface
  for (int i = 0; i < this->_num_inter_cell_faces; ++i)
  {
    const auto  volume                = this->_infc_number_to_volume[i];
    const auto& normal                = this->_infc_index_to_normal[i];
    const auto [oc_number, nc_number] = this->_infc_number_to_oc_nc_number_pair[i];

    const auto oc_solution_v = this->_solution.solution_vector_view(oc_number);
    const auto nc_solution_v = this->_solution.solution_vector_view(nc_number);

    this->_numerical_flux_ptr->calculate(flux.data(), oc_solution_v, nc_solution_v, normal);

    auto oc_residual_v = this->residual_vector(oc_number);
    auto nc_residual_v = this->residual_vector(nc_number);

    ms::math::blas::x_plus_assign_cy(oc_residual_v.data(), -volume, flux_v.data(), n);
    ms::math::blas::x_plus_assign_cy(nc_residual_v.data(), volume, flux_v.data(), n);
  }

  // scailing
  for (int i = 0; i < this->_num_cells; ++i)
  {
    const auto reciprocal_volume = this->_cell_number_to_reciprocal_volume[i];

    auto residual_v = this->residual_vector(i);
    residual_v *= reciprocal_volume;
  }
}

double Semi_Discrete_Equation_FVM::calculate_allowable_time_step(void) const
{
  auto time_step = std::numeric_limits<double>::max();

  ms::math::Vector<0> characteristic_velocity_vec(this->_dimension);
  for (int i = 0; i < this->_num_cells; ++i)
  {
    this->_solution.cal_characteristic_velocity(characteristic_velocity_vec.wrapper(), i);
    const auto allowable_time_step = this->_time_step_calculator_ptr->calculate(characteristic_velocity_vec, i);

    if (allowable_time_step < time_step) time_step = allowable_time_step;
  }

  return time_step;
}

ms::math::Vector_View Semi_Discrete_Equation_FVM::const_residual_vector(void) const
{
  return this->_residual;
}

void Semi_Discrete_Equation_FVM::post_solution(const double time) const
{
  Post::write_solution(this->_solution, time);
}

ms::math::Vector_Wrap Semi_Discrete_Equation_FVM::residual_vector(const int cell_index)
{
  auto start_ptr   = _residual.data() + cell_index * this->_num_equations;
  auto vec_wrapper = ms::math::Vector_Wrap(start_ptr, this->_num_equations);
  return vec_wrapper;
}
