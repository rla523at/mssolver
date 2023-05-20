#pragma once
#include "msconfig/Data.h"
#include <string_view>

// forward declaration
class Governing_Equation;

// static class declaration
class Governing_Equation_Container
{
public:
  static std::shared_ptr<Governing_Equation> get(const ms::config::Data& problem_data);

private:
  static void create_and_store(const std::string_view KEY, const ms::config::Data& problem_data);

private:
  inline static std::map<std::string, std::shared_ptr<Governing_Equation>> _container;

private:
  // Static class doesn't need to create object.
  // Thus, access to the constructor is restricted to prevent unnecessary creation.
  Governing_Equation_Container(void) = delete;

private:
  using THIS = Governing_Equation_Container;
};
