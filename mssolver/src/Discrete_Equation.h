#pragma once
#include "msconfig/Data.h"
#include "msgrid/Grid.h"

class Semi_Discrete_Equation;
class Time_Discrete_Scheme;
class Solve_End_Controller;
class Solve_Post_Controller;

class Discrete_Equation
{
public:
  Discrete_Equation(const ms::config::Data& problem_data, const ms::config::Data& discretization_data, const ms::grid::Grid& grid);
  ~Discrete_Equation(void); // to resolve pimpl with unique ptr issue

public:
  void solve(const ms::config::Data& solve_option_data);

private:
  double calculate_time_step(const Solve_End_Controller& end_controller, const Solve_Post_Controller& post_controller, const double current_time) const;

private:
  std::unique_ptr<Semi_Discrete_Equation> _semi_discrete_equation;
  std::shared_ptr<Time_Discrete_Scheme>   _time_discrete_scheme;
};