#include "Time_Step_Calculator_Impl.h"

#include "msexception/Exception.h"
#include <algorithm>

CFL::CFL(const double cfl, const ms::grid::Grid& grid)
    : _CFL(cfl)
{
  const auto num_cells = grid.num_cells();
  this->_cell_number_to_volume.resize(num_cells);
  this->_cell_number_to_projected_volumes.resize(num_cells);

  const auto dim = grid.dimension();

  if (dim == 1)
  {
    this->_radii_calculator = std::make_unique<Radii_Calculator_1D>();
  }
  else if (dim == 2)
  {
    this->_radii_calculator = std::make_unique<Radii_Calculator_2D>();
  }
  else
  {
    EXCEPTION("not supported dimension");
  }

  for (int i = 0; i < num_cells; ++i)
  {
    auto& volume            = this->_cell_number_to_volume[i];
    auto& projected_volumes = this->_cell_number_to_projected_volumes[i];

    volume = grid.cell_volume(i);

    if (grid.is_line_cell(i))
    {
      projected_volumes.resize(1);
      projected_volumes[0] = 1;
    }
    else
    {
      projected_volumes.resize(dim);
      grid.cell_projected_volume(projected_volumes.data(), i);
    }
  }
}

double CFL::calculate(const ms::math::Vector_Const_Wrapper characteristic_velocity_vec, const int cell_number) const
{
  const auto& projected_volumes = this->_cell_number_to_projected_volumes[cell_number];
  const auto  radii             = this->_radii_calculator->calculate(projected_volumes.data(), characteristic_velocity_vec);
  const auto  volume            = this->_cell_number_to_volume[cell_number];
  return this->_CFL * volume / radii;
}

double Constant_Dt::calculate(const ms::math::Vector_Const_Wrapper characteristic_velocity_vec, const int cell_number) const
{
  return this->constant_dt_;
}