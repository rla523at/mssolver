#include "Boundary_Flux_Impl.h"

#include "Numerical_Flux.h"

void Initial_Constant_BC::calculate(ms::math::Vector_Wrap boundary_flux_vec, const ms::math::Vector_View oc_solution_vec, const ms::math::Vector_View normal_vec) const
{
  this->calculate_neighbor_solution(oc_solution_vec);
  return this->_numerical_flux->calculate(boundary_flux_vec, oc_solution_vec, this->_neighbor_solution_vec, normal_vec);
}

void Initial_Constant_BC::calculate_neighbor_solution(const ms::math::Vector_View& oc_solution_vec) const
{
  if (!this->_is_initialized)
  {
    this->_neighbor_solution_vec.resize(static_cast<int>(oc_solution_vec.dimension()));
    this->_neighbor_solution_vec.change_value(oc_solution_vec);
    this->_is_initialized = true;
  }
}

// Euclidean_Vector Slip_Wall_BC::calculate(const Euclidean_Vector& oc_solution, const Euclidean_Vector& normal)
//{
//	Euclidean_Vector sol(oc_solution.size());
//
//	const auto p = oc_solution[this->pressure_index_];
//
//	for (ushort i = 0; i < this->space_dimension_; ++i)
//	{
//		const auto soution_index = 1 + i;
//		sol[soution_index] = p * normal[i];
//	}
//
//	return sol;
// }
//
// void Slip_Wall_BC::calculate(double* bdry_flux_ptr, const Euclidean_Vector& oc_solution, const Euclidean_Vector& normal)
//{
//	const auto p = oc_solution[this->pressure_index_];
//
//	for (ushort i = 0; i < this->space_dimension_; ++i)
//	{
//		bdry_flux_ptr[1 + i] = p * normal[i];
//	}
// }