#include "Semi_Discrete_Equation_Factory.h"

#include "Semi_Discrete_Equation_Impl.h"
#include "msstring/string.h"

std::unique_ptr<Semi_Discrete_Equation> Semi_Discrete_Equation_Factory::make(const ms::config::Data& problem_data, const ms::config::Data& discretization_data, const ms::grid::Grid& grid)
{
  const auto& space_data     = discretization_data.get_data<ms::config::Data>("space");
  const auto& scheme_name    = space_data.get_data<std::string>("scheme");
  const auto& time_step_data = discretization_data.get_data<ms::config::Data>("Time_Step");

  if (ms::string::contain_icase(scheme_name, "FVM"))
  {
    return std::make_unique<Semi_Discrete_Equation_FVM>(problem_data, time_step_data, grid);
  }
  else
  {
    EXCEPTION(scheme_name + "is not supported space discretization scheme");
    return nullptr;
  }
}
