#pragma once

#include "Element.hpp"

class CurrentSource : public Element {
private:
	int nodeA;
	int nodeB;
	double current;
public:

	CurrentSource(int nA, int nB, double i)
		: nodeA(nA), nodeB(nB), current(i) {
	}

	CurrentSource(int n, double i) 
		: nodeA(n),nodeB(0), current(i) {}

	void stampToEquation(
			Spice::Matrix& G, Spice::Vector& I,
			double dt = 0.0
	) override {

		I.add(nodeA, current);
		I.add(nodeB, -current);
	}

};