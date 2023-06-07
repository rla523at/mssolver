#include "Boundary_Flux_Impl.h"

#include "Numerical_Flux.h"

void Initial_Constant_BC::calculate(double* bdry_flux_ptr, const ms::math::Vector_Const_Wrapper oc_solution_v, const ms::math::Vector_Const_Wrapper normal_v) const
{
	this->calculate_neighbor_solution(oc_solution_v);
	this->_numerical_flux->calculate(bdry_flux_ptr, oc_solution_v, this->_neighbor_solution_v, normal_v);
}

void Initial_Constant_BC::calculate_neighbor_solution(const ms::math::Vector_Const_Wrapper& oc_solution_v) const
{
	if (!this->_is_initialized)
	{
    this->_neighbor_solution_v.change_value(oc_solution_v);
		this->_is_initialized = true;
	}
}

//Euclidean_Vector Slip_Wall_BC::calculate(const Euclidean_Vector& oc_solution, const Euclidean_Vector& normal)
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
//}
//
//void Slip_Wall_BC::calculate(double* bdry_flux_ptr, const Euclidean_Vector& oc_solution, const Euclidean_Vector& normal)
//{
//	const auto p = oc_solution[this->pressure_index_];
//
//	for (ushort i = 0; i < this->space_dimension_; ++i)
//	{
//		bdry_flux_ptr[1 + i] = p * normal[i];
//	}
//}