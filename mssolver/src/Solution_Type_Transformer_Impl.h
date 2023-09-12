#pragma once
#include "Solution_Type_Transformer.h"

class Governing_Equation;

class To_Conservative_Solution : public Solution_Type_Transformer
{
public:
  To_Conservative_Solution(const std::shared_ptr<Governing_Equation>& governing_equation_sptr)
      : _governing_equation_sptr(governing_equation_sptr){};

public:
  void transform_solution_type(ms::math::Vector_Wrap conservative_solution, const ms::math::Vector_View equation_solution) const override;

private:
  std::shared_ptr<Governing_Equation> _governing_equation_sptr;
};

class To_Extended_Solution : public Solution_Type_Transformer
{
public:
  To_Extended_Solution(const std::shared_ptr<Governing_Equation>& governing_equation_sptr)
      : _governing_equation_sptr(governing_equation_sptr){};

public:
  void transform_solution_type(ms::math::Vector_Wrap extended_solution, const ms::math::Vector_View equation_solution) const override;

private:
  std::shared_ptr<Governing_Equation> _governing_equation_sptr;
};

class To_Primitive_Solution : public Solution_Type_Transformer
{
public:
  To_Primitive_Solution(const std::shared_ptr<Governing_Equation>& governing_equation_sptr)
      : _governing_equation_sptr(governing_equation_sptr){};

public:
  void transform_solution_type(ms::math::Vector_Wrap primitive_solution, const ms::math::Vector_View equation_solution) const override;

private:
  std::shared_ptr<Governing_Equation> _governing_equation_sptr;
};