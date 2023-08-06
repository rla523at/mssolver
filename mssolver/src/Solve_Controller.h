#pragma once
#include <string>

class Solve_End_Controller
{
public:
  virtual bool        is_need_to_control_time_step(const double current_time, const double time_step) const = 0;
  virtual void        control_time_step(const double current_time, double& time_step) const                 = 0;
  virtual bool        is_time_to_end(const int current_iter, const double current_time) const               = 0;
  virtual std::string progress_percentage_str(const int current_iter, const double current_time) const      = 0;
};

class Solve_Post_Controller
{
public:
  virtual bool is_need_to_control_time_step(const double current_time, const double time_step) const = 0;
  virtual void control_time_step(const double current_time, double& time_step) const                 = 0;
  virtual bool is_time_to_post(const int current_iter, const double current_time) const              = 0;
  virtual bool is_post_initial_solution(void) const                                                  = 0;
  virtual bool is_post_final_solution(void) const                                                    = 0;

  // protected:
  // int num_post_ = 0;
};