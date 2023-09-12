#pragma once
#include "Boundary_Flux.h"

#include <memory>
#include <vector>

class Numerical_Flux;

class Initial_Constant_BC : public Boundary_Flux
{
public:
  Initial_Constant_BC(const std::shared_ptr<Numerical_Flux>& numerical_flux_function)
      : _numerical_flux(numerical_flux_function){};

public:
  void calculate(ms::math::Vector_Wrap boundary_flux_vec, const ms::math::Vector_View oc_solution_vec, const ms::math::Vector_View normal_vec) const override;

private:
  void calculate_neighbor_solution(const ms::math::Vector_View& oc_solution_v) const;

private:
  mutable bool                    _is_initialized        = false;
  mutable ms::math::Vector<0>     _neighbor_solution_vec = ms::math::Vector<0>::null_vector();
  std::shared_ptr<Numerical_Flux> _numerical_flux;
};

// class Slip_Wall_BC : public Boundary_Flux
//{
// public:
//   Slip_Wall_BC(const std::shared_ptr<Governing_Equation>& governing_equation, const std::shared_ptr<Numerical_Flux>& numerical_flux_function)
//       : pressure_index_(governing_equation->pressure_index()),
//         space_dimension_(governing_equation->space_dimension()),
//         numerical_flux_function_(numerical_flux_function){};
//
// public: // Query
//   Euclidean_Vector calculate(const Euclidean_Vector& oc_solution, const Euclidean_Vector& normal) override;
//   void             calculate(double* bdry_flux_ptr, const Euclidean_Vector& oc_solution, const Euclidean_Vector& normal) override;
//
// private:
//   ushort                          pressure_index_  = 0;
//   ushort                          space_dimension_ = 0;
//   std::shared_ptr<Numerical_Flux> numerical_flux_function_;
// };

// template <ushort num_equation>
// class Supersonic_Inlet1_Neighbor_Solution_Calculator
//{
// private:
//	Supersonic_Inlet1_Neighbor_Solution_Calculator(void) = delete;
//
// private:
//	inline static Euclidean_Vector<num_equation> inflow_;
//
// public:
//	static void initialize(const Euclidean_Vector<num_equation>& inflow) { inflow_ = inflow; };
//	static Euclidean_Vector<num_equation> calculate(void) { return inflow_; };
// };
//
//
// template <ushort num_equation>
// class Supersonic_Inlet2_Neighbor_Solution_Calculator
//{
// private:
//	Supersonic_Inlet2_Neighbor_Solution_Calculator(void) = delete;
//
// private:
//	inline static Euclidean_Vector<num_equation> inflow_;
//
// public:
//	static void initialize(const Euclidean_Vector<num_equation>& inflow) { inflow_ = inflow; };
//	static Euclidean_Vector<num_equation> calculate(void) { return inflow_; };
// };

// template <ushort num_equation>
// class Slip_Wall_Neighbor_Solution_Calculator
//{
// private:
//	Slip_Wall_Neighbor_Solution_Calculator(void) = delete;
//
// public:
//	static Euclidean_Vector<num_equation> calculate(const Euclidean_Vector<num_equation>& solution) {
//		std::array<double, num_equation> values = -1 * solution;
//		values.front() *= -1;
//		values.back() *= -1;
//		return values;
//	};
// };
//
//
// template <ushort num_equation>
// class Initial_Constant_BC_Neighbor_Solution_Calculator
//{
// private:
//	bool is_first_ = true;
//	Euclidean_Vector<num_equation> initial_constant_;
//
// public:
//	Euclidean_Vector<num_equation> calculate(const Euclidean_Vector<num_equation>& solution) {
//		if (this->is_first_) {
//			this->initial_constant_ = solution;
//			this->is_first_ = false;
//		}
//
//		return this->initial_constant_;
//	};
// };

// template <typename Numerical_Flux>
// class Supersonic_Inlet1 : public Boundary_Flux_Function<Numerical_Flux>
//{
// private:
//	using This_			= Supersonic_Inlet1<Numerical_Flux>;
//	using Space_Vector_ = This_::Space_Vector_;
//	using Solution_		= This_::Solution_;
//
// public:
//	This_::Boundary_Flux_ calculate(const Solution_& solution, const Space_Vector_& normal) const override {
//		return Numerical_Flux::calculate(solution, Supersonic_Inlet1_Neighbor_Solution_Calculator<This_::num_equation_>::calculate(), normal);
//	}
// };

// template <typename Numerical_Flux>
// class Supersonic_Inlet2 : public Boundary_Flux_Function<Numerical_Flux>
//{
// private:
//	using This_			= Supersonic_Inlet2<Numerical_Flux>;
//	using Space_Vector_ = This_::Space_Vector_;
//	using Solution_		= This_::Solution_;
//
// public:
//	This_::Boundary_Flux_ calculate(const Solution_& solution, const Space_Vector_& normal) const override {
//		return Numerical_Flux::calculate(solution, Supersonic_Inlet2_Neighbor_Solution_Calculator<This_::num_equation_>::calculate(), normal);
//	}
// };

// template <typename Numerical_Flux>
// class Supersonic_Outlet : public Boundary_Flux_Function<Numerical_Flux>
//{
// private:
//	using This_			= Supersonic_Outlet<Numerical_Flux>;
//	using Space_Vector_ = This_::Space_Vector_;
//	using Solution_		= This_::Solution_;
//
// public:
//	This_::Boundary_Flux_ calculate(const Solution_& solution, const Space_Vector_& normal) const override {
//		return Numerical_Flux::calculate(solution, solution, normal);
//	}
// };
