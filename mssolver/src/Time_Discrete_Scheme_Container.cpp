#include "Time_Discrete_Scheme_Container.h"

#include "Time_Discrete_Scheme_Impl.h"
#include "msstring/string.h"

std::shared_ptr<Time_Discrete_Scheme> Time_Discrete_Scheme_Container::get(const ms::config::Data& time_discretization_data)
{
  const auto& scheme_name = time_discretization_data.get_data<std::string>("scheme");
  const auto  KEY         = ms::string::upper_case(scheme_name);

  if (!THIS::_container.contains(KEY))
  {
    THIS::create_and_store(KEY);
  }

  return THIS::_container.at(KEY);
};

void Time_Discrete_Scheme_Container::create_and_store(const std::string_view KEY)
{
  if (ms::string::contain(KEY, "EULER", "EXPLICIT"))
  {
    THIS::_container.emplace(KEY, std::make_shared<Euler_Explicit>());
  }
  // else if (ms::string::contains_icase(scheme_name, "SSPRK", "33"))
  //{
  //   return std::make_unique<SSPRK33>();
  // }
  // else if (ms::string::contains_icase(scheme_name, "SSPRK", "54"))
  //{
  //   return std::make_unique<SSPRK54>();
  // }
  else
  {
    EXCEPTION(std::string(KEY) + " is not supproted time discretization scheme ");
  }
}
