#pragma once
#include <limits>
#include "Element.hpp"

class VoltageSource : public Element {
private:
	int node;
	double voltage;
	double eps = std::numeric_limits<double>::epsilon();
public:
	VoltageSource(int n, int v) : node(n), voltage(v) {}

	void stampToEquation(
		Spice::Matrix& G, Spice::Vector& I,
		double dt) override {

		double internalResistor = eps;
		double conductance = 1.0 / internalResistor;
		double current = voltage / internalResistor;

		G.add(node, 0, conductance);
		I.add(node, current);
	}
};