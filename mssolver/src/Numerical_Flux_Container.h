#pragma once
#include <map>
#include <memory>
#include <msconfig/Data.h>
#include <string_view>

// foward declaration
class Numerical_Flux;

// static class declaration
class Numerical_Flux_Container
{
public:
  static std::shared_ptr<Numerical_Flux> get(const ms::config::Data& problem_data, const std::string_view numerical_flux_name);

private:
  static void create_and_store(const std::string_view KEY, const ms::config::Data& problem_data);

private:
  inline static std::map<std::string, std::shared_ptr<Numerical_Flux>> _container;

private:
  Numerical_Flux_Container(void) = delete;

  using THIS = Numerical_Flux_Container;
};