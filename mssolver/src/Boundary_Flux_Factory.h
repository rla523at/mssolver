#pragma once
#include "msgrid/Data.h"
#include <memory>

// forward declaration
class Boundary_Flux;
class Numerical_Flux;

// static class
class Boundary_Flux_Factory
{
public:
  static std::unique_ptr<Boundary_Flux> make_unique(const ms::grid::Element_Type elem_type, const std::shared_ptr<Numerical_Flux>& numerical_flux);

private:
  Boundary_Flux_Factory(void) = delete;
};