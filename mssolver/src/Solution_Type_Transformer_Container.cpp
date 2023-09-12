#include "Solution_Type_Transformer_Container.h"

#include "Governing_Equation.h"
#include "Solution_Type_Transformer_Impl.h"
#include "msstring/string.h"

const Solution_Type_Transformer& Solution_Type_Transformer_Container::get(const std::string_view solution_type, const std::shared_ptr<Governing_Equation>& governing_equation_sptr)
{
  return *THIS::get_sptr(solution_type, governing_equation_sptr);
}

const std::shared_ptr<Solution_Type_Transformer>& Solution_Type_Transformer_Container::get_sptr(const std::string_view solution_type, const std::shared_ptr<Governing_Equation>& governing_equation_sptr)
{
  const auto KEY = ms::string::upper_case(solution_type);

  if (!THIS::_container.contains(KEY))
  {
    THIS::create_and_store(KEY, governing_equation_sptr);
  }

  return THIS::_container.at(KEY);
}

void Solution_Type_Transformer_Container::create_and_store(const std::string_view KEY, const std::shared_ptr<Governing_Equation>& governing_equation_sptr)
{
  if (KEY == "CONSERVATIVE")
  {
    THIS::_container.emplace(KEY, std::make_shared<To_Conservative_Solution>(governing_equation_sptr));
  }
  else if (KEY == "PRIMITIVE")
  {
    THIS::_container.emplace(KEY, std::make_shared<To_Primitive_Solution>(governing_equation_sptr));
  }
  else if (KEY == "EXTENDED")
  {
    THIS::_container.emplace(KEY, std::make_shared<To_Extended_Solution>(governing_equation_sptr));
  }
  else
  {
    EXCEPTION(std::string(KEY) + " is not supported solution type");
  }
}