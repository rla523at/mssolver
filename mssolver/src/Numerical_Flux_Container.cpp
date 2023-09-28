#include "Numerical_Flux_Container.h"

#include "Governing_Equation_Container.h"
#include "Numerical_Flux_Impl.h"
#include "msstring/string.h"

std::shared_ptr<Numerical_Flux> Numerical_Flux_Container::get(const ms::config::Data& problem_data, const std::string_view numerical_flux_name)
{
  const auto KEY = ms::string::upper_case(numerical_flux_name);

  if (!THIS::_container.contains(KEY))
  {
    THIS::create_and_store(KEY, problem_data);
  }
}

void Numerical_Flux_Container::create_and_store(const std::string_view KEY, const ms::config::Data& problem_data)
{
  if (ms::string::contain(KEY, "GODUNOV"))
  {
    const auto& governing_equation_name = problem_data.get_data<std::string>("governing_equation");

    if (ms::string::contain_icase(governing_equation_name, "linear", "advection"))
    {
      THIS::_container.emplace(KEY, std::make_shared<Godunov_Flux_Linear_Advection>(Governing_Equation_Container::get_linear_advection(problem_data)));
    }
  }
  else if (ms::string::contain(KEY, "UNSTABLE"))
  {
    THIS::_container.emplace(KEY, std::make_shared<Unstable_Flux>(Governing_Equation_Container::get_sptr(problem_data)));
  }
  // else if (ms::string::contain(KEY, "LAX", "FRIDRICHS"))
  //{
  // }
  else
  {
    EXCEPTION(std::string(KEY) + " is not supported numerical flux");
  }
}
