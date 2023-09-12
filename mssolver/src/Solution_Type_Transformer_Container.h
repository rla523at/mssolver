#pragma once
#include <map>
#include <memory>
#include <string_view>

class Governing_Equation;
class Solution_Type_Transformer;

class Solution_Type_Transformer_Container
{
public:
  Solution_Type_Transformer_Container(void) = delete;

public:
  static const Solution_Type_Transformer&                  get(const std::string_view solution_type, const std::shared_ptr<Governing_Equation>& governing_equation_sptr);
  static const std::shared_ptr<Solution_Type_Transformer>& get_sptr(const std::string_view solution_type, const std::shared_ptr<Governing_Equation>& governing_equation_sptr);

private:
  static void create_and_store(const std::string_view KEY, const std::shared_ptr<Governing_Equation>& governing_equation_sptr);

private:
  inline static std::map<std::string, std::shared_ptr<Solution_Type_Transformer>> _container;

private:
  using THIS = Solution_Type_Transformer_Container;
};