#pragma once

class Initial_Condition
{
public:
  virtual void calculate_solution(double* solution, const double* coordinates) const = 0;
};