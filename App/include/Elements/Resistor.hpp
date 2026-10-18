#pragma once

#include "Element.hpp"

class Resistor : public Element {

private:
	int nodeA;
	int nodeB;
	double resistance;

public:
	Resistor(int a, int b, double r) 
		: nodeA(a), nodeB(b), resistance(r) {}

	void stampToEquation(
		Spice::Matrix& G, Spice::Vector& I, 
		double dt) override {
		if (this->resistance <= 0.0) return;

		double conductance = 1 / resistance;

		G.add(nodeA, nodeB, conductance);
	}
};