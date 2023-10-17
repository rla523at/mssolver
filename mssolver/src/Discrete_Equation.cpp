#include "Discrete_Equation.h"

#include "Governing_Equation_Container.h"
#include "Semi_Discrete_Equation.h"
#include "Solve_Controller.h"
#include "Solve_Controller_Container.h"
#include "Time_Discrete_Scheme.h"

Discrete_Equation ::~Discrete_Equation(void) = default;

void Discrete_Equation::solve(const ms::config::Data& solve_option_data)
{
  const auto& solve_end_option  = solve_option_data.get_data<ms::config::Data>("End");
  const auto& solve_post_option = solve_option_data.get_data<ms::config::Data>("POST");
  const auto& end_controller    = Solve_End_Controller_Container::get(solve_end_option);
  const auto& post_controller   = Solve_Post_Controller_Container::get(solve_post_option);

  auto current_iter = 0;
  auto current_time = 0.0;
  // Post_Processor::syncronize_solution_time(this->current_time_);

  if (post_controller.is_post_initial_solution())
  {
    this->_semi_discrete_equation->post_solution(current_time);
  }

  while (!end_controller.is_time_to_end(current_iter, current_time))
  {
    if (post_controller.is_time_to_post(current_iter, current_time))
    {
      this->_semi_discrete_equation->post_solution(current_time);
    }

    // Profiler::set_time_point();

    const auto time_step = this->calculate_time_step(end_controller, post_controller, current_time);
    this->_time_discrete_scheme->update(*this->_semi_discrete_equation, time_step);

    current_time += time_step;
    current_iter += 1;

    // LOG << std::left;
    // LOG << std::setw(10) << "Iter:" + std::to_string(current_iter);
    // LOG << std::setw(25) << "Time:" + std::to_string(this->current_time_) + "(" + end_controller.progress_percentage_str(current_iter, this->current_time_) + ")";
    // LOG << std::setw(25) << "Computation cost:" + std::to_string(Profiler::get_time_duration()) + "s \n"        << LOG.print_;
  }

  if (post_controller.is_post_final_solution())
  {
    this->_semi_discrete_equation->post_solution(current_time);
  }
}

double Discrete_Equation::calculate_time_step(const Solve_End_Controller& end_controller, const Solve_Post_Controller& post_controller, const double current_time) const
{
  auto allowable_time_step = this->_semi_discrete_equation->calculate_allowable_time_step();
  if (end_controller.is_need_to_control_time_step(current_time, allowable_time_step))
  {
    end_controller.control_time_step(current_time, allowable_time_step);
  }

  if (post_controller.is_need_to_control_time_step(current_time, allowable_time_step))
  {
    post_controller.control_time_step(current_time, allowable_time_step);
  }

  return allowable_time_step;
}
