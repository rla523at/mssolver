#include "Boundary_Flux_Factory.h"

#include "Boundary_Flux_Impl.h"
#include "msexception/Exception.h"

std::unique_ptr<Boundary_Flux> Boundary_Flux_Factory::make_unique(const ms::grid::Element_Type elem_type, const std::shared_ptr<Numerical_Flux>& numerical_flux)
{
  switch (elem_type)
  {
  case ms::grid::Element_Type::INTIAL_CONSTANT:
    return std::make_unique<Initial_Constant_BC>(numerical_flux);
  // case ElementType::slip_wall:
  //   bdry_flux_functions[i] = make_slip_wall_BC(governing_equation, numerical_flux_function);
  //   break;
  default:
    EXCEPTION("not supported boundary type");
    return nullptr;
  }
}