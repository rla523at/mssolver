#pragma once
#include "msgrid/Grid.h"
#include "msmath/Vector.h"

// class declaration;
class Time_Step_Calculator
{
public:
  virtual double calculate(const double* characteristic_velocity, const int cell_number) const = 0;
};
