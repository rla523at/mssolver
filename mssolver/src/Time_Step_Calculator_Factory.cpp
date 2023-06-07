#include "Time_Step_Calculator_Factory.h"

#include "Time_Step_Calculator_Impl.h"
#include "msstring/string.h"

std::unique_ptr<Time_Step_Calculator> Time_Step_Calculator_Factory::make(const ms::config::Data& time_step_data, const ms::grid::Grid& grid)
{
  const auto& time_step_type      = time_step_data.get_data<std::string>("type");
  const auto  time_step_criterion = time_step_data.get_data<double>("criterion");

  if (ms::string::contain_icase(time_step_type, "CFL"))
  {
    return std::make_unique<CFL>(time_step_criterion, grid);
  }
  else if (ms::string::contain_icase(time_step_type, "Constant", "dt"))
  {
    return std::make_unique<Constant_Dt>(time_step_criterion);
  }
  else
  {
    EXCEPTION(time_step_type + " in configuration file is not supported time step type");
    return nullptr;
  }
}