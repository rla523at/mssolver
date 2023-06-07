#include "Time_Discrete_Scheme_Impl.h"

#include "Semi_Discrete_Equation.h"
#include "msmath/BLAS.h"

void Euler_Explicit::update(Semi_Discrete_Equation& semi_discrete_equation, const double time_step) const
{
  auto       solution_v = semi_discrete_equation.solution_vector();
  const auto RHS_v      = semi_discrete_equation.const_residual_vector();

  const auto n = static_cast<int>(solution_v.dimension());

  semi_discrete_equation.update_residual();

  // solution_v = solution_v + time_step * initial_RHS;
  ms::math::blas::x_plus_assign_cy(solution_v.data(), time_step, RHS_v.data(), n);
}

// void SSPRK33::update(Semi_Discrete_Equation& semi_discrete_equation, const double time_step) const
//{
//     constexpr auto c1_3 = 1.0 / 3.0;
//
// auto solution_vw = semi_discrete_equation.discrete_solution_vector_wrapper();
// const auto RHS_cvw = semi_discrete_equation.RHS_constant_vector_wrapper();
// const auto initial_solution_v = semi_discrete_equation.discrete_solution_vector();
//
// semi_discrete_equation.calculate_RHS();

// const auto n = static_cast<int>(solution_vw.size());

////stage 1
////solution_vw = solution_vw + time_step * initial_RHS;
// ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), time_step, RHS_cvw.data());
//
//    semi_discrete_equation.reconstruct();
//    semi_discrete_equation.calculate_RHS();
//
//    //stage 2
//    //solution_vw = 0.25 * (solution_vw + 3 * initial_solution_v + time_step * stage1_RHS);
//    ms::BLAS::cx(0.25, n, solution_vw.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.75, initial_solution_v.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.25 * time_step, RHS_cvw.data());
//
//    semi_discrete_equation.reconstruct();
//    semi_discrete_equation.calculate_RHS();
//
//    //stage 3
//    //solution_vw = c1_3 * (2 * solution_vw + initial_solution_v + 2 * time_step * stage2_RHS);
//    ms::BLAS::cx(2 * c1_3, n, solution_vw.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), c1_3, initial_solution_v.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), c1_3 * 2 * time_step, RHS_cvw.data());
//
//    semi_discrete_equation.reconstruct();
//
//    //std::exit(523);
//}
//
// void SSPRK54::update(Semi_Discrete_Equation& semi_discrete_equation, const double time_step) const
//{
//    auto solution_vw = semi_discrete_equation.discrete_solution_vector_wrapper();
//    const auto RHS_cvw = semi_discrete_equation.RHS_constant_vector_wrapper();
//    const auto initial_solution_v = semi_discrete_equation.discrete_solution_vector();
//
//    semi_discrete_equation.calculate_RHS();
//
//    const auto n = static_cast<int>(solution_vw.size());
//
//    //stage 1
//    //solution_vw = solution_vw + 0.391752226571890 * time_step * initial_RHS;
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.391752226571890 * time_step, RHS_cvw.data());
//
//    semi_discrete_equation.reconstruct();
//    semi_discrete_equation.calculate_RHS();
//
//    //stage 2
//    //solution_vw = 0.555629506348765 * solution_vw + 0.444370493651235 * initial_solution_v + 0.368410593050371 * time_step * stage1_RHS;
//    ms::BLAS::cx(0.555629506348765, n, solution_vw.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.444370493651235, initial_solution_v.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.368410593050371 * time_step, RHS_cvw.data());
//
//    semi_discrete_equation.reconstruct();
//    semi_discrete_equation.calculate_RHS();
//
//    const auto stage2_solution_v = semi_discrete_equation.discrete_solution_vector();
//
//    //stage 3
//    //solution_vw = 0.379898148511597 * solution_vw + 0.620101851488403 * initial_solution_v + 0.251891774271694 * time_step * stage2_RHS;
//    ms::BLAS::cx(0.379898148511597, n, solution_vw.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.620101851488403, initial_solution_v.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.251891774271694 * time_step, RHS_cvw.data());
//
//    semi_discrete_equation.reconstruct();
//    semi_discrete_equation.calculate_RHS();
//
//    const auto stage3_solution_v = semi_discrete_equation.discrete_solution_vector();
//    const auto stage3_RHS_v = semi_discrete_equation.RHS_vector();
//
//    //stage 4
//    //solution_vw = 0.821920045606868 * solution_vw + 0.178079954393132 * initial_solution_v + 0.544974750228521 * time_step * stage3_RHS;
//    ms::BLAS::cx(0.821920045606868, n, solution_vw.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.178079954393132, initial_solution_v.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.544974750228521 * time_step, RHS_cvw.data());
//
//    semi_discrete_equation.reconstruct();
//    semi_discrete_equation.calculate_RHS();
//
//    //stage 5
//    //solution_vw = 0.386708617503269 * solution_vw + 0.517231671970585 * stage2_solution_v + 0.096059710526147 * stage3_solution_v + 0.063692468666290 * time_step * stage3_RHS + 0.226007483236906 * time_step * stage4_RHS;
//    ms::BLAS::cx(0.386708617503269, n, solution_vw.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.517231671970585, stage2_solution_v.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.096059710526147, stage3_solution_v.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.063692468666290 * time_step, stage3_RHS_v.data());
//    ms::BLAS::x_plus_assign_cy(n, solution_vw.data(), 0.226007483236906 * time_step, RHS_cvw.data());
//
//    semi_discrete_equation.reconstruct();
//}

