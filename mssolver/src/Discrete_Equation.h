#pragma once
#include "msconfig/Data.h"
#include "msgrid/Grid.h"

class Semi_Discrete_Equation;
class Time_Discrete_Scheme;

class Discrete_Equation
{
public:
  Discrete_Equation(const ms::config::Data& problem_data, const ms::config::Data& discretization_data, const ms::grid::Grid& grid);

public:
  void solve(const ms::config::Data& solve_option_data);

private:
  void controll_time_step(const double current_time, double& time_step) const;

private:
  std::unique_ptr<Semi_Discrete_Equation> _semi_discrete_equation;
  std::shared_ptr<Time_Discrete_Scheme>   _time_discrete_scheme;
};