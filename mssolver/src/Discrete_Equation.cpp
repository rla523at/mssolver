#include "Discrete_Equation.h"

#include "Governing_Equation_Container.h"
#include "Semi_Discrete_Equation.h"
#include "Semi_Discrete_Equation_Factory.h"
#include "Time_Discrete_Scheme.h"
#include "Time_Discrete_Scheme_Container.h"

Discrete_Equation::Discrete_Equation(const ms::config::Data& problem_data, const ms::config::Data& discretization_data, const ms::grid::Grid& grid)
{
  const auto& time_data = discretization_data.get_data<ms::config::Data>("time");

  this->_semi_discrete_equation = Semi_Discrete_Equation_Factory::make(problem_data, discretization_data, grid);
  this->_time_discrete_scheme   = Time_Discrete_Scheme_Container::get(time_data);
}

void Discrete_Equation::solve(const ms::config::Data& solve_option_data)
{
  auto current_iter = 0;
  auto current_time = 0.0;
  // Post_Processor::syncronize_solution_time(this->current_time_);
  // Post_Processor::post_grid();

  // if (this->post_controller_->is_post_initial_solution())
  //{
  // Post_Processor::record_solution();
  // Post_Processor::post_solution("initial");
  //}

  while (true)
  {
    // if (this->end_controller_->is_time_to_end(current_iter, this->current_time_))
    //{
    //   if (this->post_controller_->is_post_final_solution())
    //   {
    //     Post_Processor::record_solution();
    //     Post_Processor::post_solution("final");
    //   }
    //   break;
    // }

    // if (this->post_controller_->is_time_to_post(current_iter, this->current_time_))
    //{
    //   Post_Processor::record_solution();
    //   Post_Processor::post_solution();
    //   this->post_controller_->increase_num_post();
    // }

    // Profiler::set_time_point();

    auto time_step = this->_semi_discrete_equation->calculate_time_step();
    this->controll_time_step(current_time, time_step);

    this->_time_discrete_scheme->update(*this->_semi_discrete_equation, time_step);

    current_time += time_step;
    current_iter += 1;

    // LOG << std::left;
    // LOG << std::setw(10) << "Iter:" + std::to_string(current_iter);
    // LOG << std::setw(25) << "Time:" + std::to_string(this->current_time_) + "(" + this->end_controller_->progress_percentage_str(current_iter, this->current_time_) + ")";
    // LOG << std::setw(25) << "Computation cost:" + std::to_string(Profiler::get_time_duration()) + "s \n"        << LOG.print_;
  }
}

// void Discrete_Equation::controll_time_step(const double current_time, double& time_step) const
//{
//   if (this->end_controller_->is_need_to_controll_time_step(current_time, time_step))
//   {
//     this->end_controller_->controll_time_step(current_time, time_step);
//     return;
//   }
//
//   if (this->post_controller_->is_need_to_controll_time_step(current_time, time_step))
//   {
//     this->post_controller_->controll_time_step(current_time, time_step);
//   }
// }