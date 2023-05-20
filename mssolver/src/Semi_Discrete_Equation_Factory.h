#pragma once
#include "msconfig/Data.h"
#include "msgrid/Grid.h"
#include <memory>

class Semi_Discrete_Equation;

class Semi_Discrete_Equation_Factory
{
public:
  static std::unique_ptr<Semi_Discrete_Equation> make(const ms::config::Data& problem_data, const ms::config::Data& discretization_data, const ms::grid::Grid& grid);
};