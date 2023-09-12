#pragma once
#include "msgrid/Grid.h"
#include "msmath/Vector.h"

// class declaration;
class Time_Step_Calculator
{
public:
  virtual ~Time_Step_Calculator(void) = default;

public:
  virtual double calculate(const ms::math::Vector_View characteristic_velocity_vec, const int cell_number) const = 0;
};
