#pragma once

#include "Element.hpp"

class CurrentSource : public Element {
private:
	int node;
	double current;
public:
	CurrentSource(int n, double i) 
		: node(n), current(i) {}

	void stampToEquation(
		Spice::Matrix& G, Spice::Vector& I,
		double dt = 0.0
	) override {

		I.add(node, current);
	}

};