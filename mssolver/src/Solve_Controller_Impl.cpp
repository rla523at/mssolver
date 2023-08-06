#include "Solve_Controller_Impl.h"

#include "msexception/Exception.h"
#include <iomanip>
#include <sstream>

bool Solve_End_Controller_By_Time::is_need_to_control_time_step(const double current_time, const double time_step) const
{
  const double expect_time = current_time + time_step;
  return this->end_time_ < expect_time;
}

bool Solve_End_Controller_By_Time::is_time_to_end(const int current_iter, const double current_time) const
{
  return current_time == this->end_time_;
}

void Solve_End_Controller_By_Time::control_time_step(const double current_time, double& time_step) const
{
  time_step = this->end_time_ - current_time;
}

std::string Solve_End_Controller_By_Time::progress_percentage_str(const int current_iter, const double current_time) const
{
  std::ostringstream oss;
  oss << std::setprecision(2) << std::fixed << current_time * 100 / this->end_time_ << "%";
  return oss.str();
}

/*








*/

bool Solve_End_Controller_By_Iter::is_need_to_control_time_step(const double current_time, const double time_step) const
{
  return false;
}

bool Solve_End_Controller_By_Iter::is_time_to_end(const int current_iter, const double current_time) const
{
  return current_iter == this->end_iter_;
}

void Solve_End_Controller_By_Iter::control_time_step(const double current_time, double& time_step) const
{
  EXCEPTION("controller by iter never controll time step");
  return;
}

std::string Solve_End_Controller_By_Iter::progress_percentage_str(const int current_iter, const double current_time) const
{
  std::ostringstream oss;
  oss << std::setprecision(2) << std::fixed << current_iter * 100 / this->end_iter_ << "%";
  return oss.str();
}

/*








*/

Solve_Post_Controller_By_Time::Solve_Post_Controller_By_Time(const double post_time_unit, const bool is_post_initial, const bool is_post_final)
    : _post_time_unit(post_time_unit),
      _is_post_initiali_solution(is_post_initial),
      _is_post_final_solution(is_post_final)
{
  this->update_post_time();
};

void Solve_Post_Controller_By_Time::control_time_step(const double current_time, double& time_step) const
{
  time_step = this->_post_time - current_time;
}

bool Solve_Post_Controller_By_Time::is_need_to_control_time_step(const double current_time, const double time_step) const
{
  const auto expect_time = current_time + time_step;
  return this->_post_time < expect_time;
}

bool Solve_Post_Controller_By_Time::is_time_to_post(const int current_iter, const double current_time) const
{
  if (current_time == this->_post_time)
  {
    this->update_post_time();
    return true;
  }
}

bool Solve_Post_Controller_By_Time::is_post_initial_solution(void) const
{
  return this->_is_post_initiali_solution;
};

bool Solve_Post_Controller_By_Time::is_post_final_solution(void) const
{
  return this->_is_post_final_solution;
};

void Solve_Post_Controller_By_Time::update_post_time(void) const
{
  this->_post_time += this->_post_time_unit;
}

/*








*/

Solve_Post_Controller_By_Iter::Solve_Post_Controller_By_Iter(const int post_iter_unit, const bool is_post_initial, const bool is_post_final)
    : _post_iter_unit(post_iter_unit),
      _is_post_initiali_solution(is_post_initial),
      _is_post_final_solution(is_post_final)
{
  this->update_post_iter();
};

void Solve_Post_Controller_By_Iter::control_time_step(const double current_time, double& time_step) const
{
  EXCEPTION("controller by iter never controll time step");
  return;
}

bool Solve_Post_Controller_By_Iter::is_time_to_post(const int current_iter, const double current_time) const
{
  if (current_iter == this->_post_iter)
  {
    this->update_post_iter();
    return true;
  }
}

bool Solve_Post_Controller_By_Iter::is_need_to_control_time_step(const double current_time, const double time_step) const { return false; }

bool Solve_Post_Controller_By_Iter::is_post_initial_solution(void) const
{
  return this->_is_post_initiali_solution;
};

bool Solve_Post_Controller_By_Iter::is_post_final_solution(void) const
{
  return this->_is_post_final_solution;
};

void Solve_Post_Controller_By_Iter::update_post_iter(void) const
{
  this->_post_iter += this->_post_iter_unit;
}