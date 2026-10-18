#pragma once

#include <Math/Types.hpp>

class Element {
public:
	virtual ~Element() = default;
	
	virtual void stampToEquation(
		Spice::Matrix& G, 
		Spice::Vector& I, 
		double deltaTime = 0.0
	) = 0;
};