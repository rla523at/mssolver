#pragma once

class Semi_Discrete_Equation;

class Time_Discrete_Scheme
{
public:
	virtual void update(Semi_Discrete_Equation& semi_discrete_equation, const double time_step) const abstract;    
};



