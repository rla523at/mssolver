#include "Semi_Discrete_Equation_Impl.h"

#include "Time_Step_Calculator.h"
#include "Time_Step_Calculator_Factory.h"
#include "msmath/BLAS.h"

Semi_Discrete_Equation_FVM::Semi_Discrete_Equation_FVM(const ms::config::Data& problem_data, const ms::config::Data& time_step_data, const ms::grid::Grid& grid)
    : _solution(problem_data, grid)
{
  this->_time_step_calculator_uptr = Time_Step_Calculator_Factory::make_unique(time_step_data, grid);
  this->_num_cells                 = grid.num_cells();
}

void Semi_Discrete_Equation_FVM::update_residual(void)
{
  auto       flux   = std::vector<double>();
  const auto flux_v = ms::math::Vector_Const_Wrapper(flux);
  const auto n      = flux_v.dimension();

  // initialize residual
  std::fill(this->_residual.begin(), this->_residual.end(), 0.0);

  // calculate residual at boundary
  for (int i = 0; i < this->_num_boundaries; ++i)
  {
    const auto  volume        = this->_bdry_index_to_volume[i];
    const auto& normal        = this->_bdry_index_to_normal[i];
    const auto  oc_index      = this->_bdry_index_to_oc_index[i];
    const auto  oc_solution_v = this->_solution.const_solution_vector(oc_index);
    auto        oc_residual_v = this->residual_vector(oc_index);

    auto& boundary_flux_function = this->_bdry_index_to_flux_function[i];

    boundary_flux_function->calculate(flux.data(), oc_solution_v, normal);

    ms::math::blas::x_plus_assign_cy(oc_residual_v.data(), -volume, flux_v.data(), n);
  }

  // calculate residual at innerface
  for (int i = 0; i < this->_num_inner_faces; ++i)
  {
    const auto  volume              = this->_infc_index_to_volume[i];
    const auto& normal              = this->_infc_index_to_normal[i];
    const auto [oc_index, nc_index] = this->_infc_index_to_oc_nc_index[i];

    const auto oc_solution_v = this->_solution.const_solution_vector(oc_index);
    const auto nc_solution_v = this->_solution.const_solution_vector(nc_index);

    this->_numerical_flux_function->calculate(oc_solution_v, nc_solution_v, normal);

    auto oc_residual_v = this->residual_vector(oc_index);
    auto nc_residual_v = this->residual_vector(nc_index);

    ms::math::blas::x_plus_assign_cy(oc_residual_v.data(), -volume, flux_v.data(), n);
    ms::math::blas::x_plus_assign_cy(nc_residual_v.data(), volume, flux_v.data(), n);
  }

  // scailing
  for (int i = 0; i < this->_num_cells; ++i)
  {
    const auto reciprocal_volume = this->_cell_index_to_reciprocal_volume[i];    
    
    auto residual_v = this->residual_vector(i);
    residual_v *= reciprocal_volume;    
  }

  // boundary flux 만들기
  // grid로부터 boundary data 만드는 코드 생성자에 만들기
  // numerical flux 만들기
  // grid로부터 innerface data 만드는 코드 생성자에 만들기
  //  periodic이랑 intercell face랑 합쳐야됨!
  // grid로부터 cell data 만드는 코드 생성자에 만들기
  // residual update하는 수식 맞는지 확인하기
}

double Semi_Discrete_Equation_FVM::calculate_time_step(void) const
{
  auto time_step = std::numeric_limits<double>::max();

  std::vector<double> characteristic_velocity;
  for (int i = 0; i < this->_num_cells; ++i)
  {
    this->_solution.cal_characteristic_velocity(characteristic_velocity.data(), i);
    const auto allowable_time_step = this->_time_step_calculator_uptr->calculate(characteristic_velocity.data(), i);

    if (allowable_time_step < time_step) time_step = allowable_time_step;
  }

  return time_step;
}
