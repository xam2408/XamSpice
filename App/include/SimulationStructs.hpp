#pragma once
#include <vector>
#include "Math/Types.hpp"

struct TransientResult {
	double time;
	Spice::Vector voltages;
};

struct TransientResultSingle {
	double time;
	double voltage;
};