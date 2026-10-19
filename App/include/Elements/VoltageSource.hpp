#pragma once
#include <limits>
#include "Element.hpp"

class VoltageSource : public Element {
private:
	int nodeA;
	int nodeB;
	double voltage;
	double eps = std::numeric_limits<double>::epsilon();
	//double eps = 1e-3;
public:
	VoltageSource(int n, double v) : nodeA(n), nodeB(0), voltage(v) {}
	VoltageSource(int nA, int nB, double v) : nodeA(nA), nodeB(nB), voltage(v) {}

	void stampToEquation(
			Spice::Matrix& G, Spice::Vector& I,
			double dt) override {

		double internalResistor = eps;
		double conductance = 1.0 / internalResistor;
		double current = voltage / internalResistor;

		G.add(nodeA, nodeB, conductance);
		I.add(nodeA, current);
		I.add(nodeB, -current);
	}
};