#pragma once
#include <memory>
#include <vector>
#include "Elements/Element.hpp"
#include "SimulationStructs.hpp"

class Circuit {

private:

	int nodes;
	std::vector<std::unique_ptr<Element>> elements;

public:

	Circuit(int n) : nodes(n) {}
	
	void addElement(std::unique_ptr<Element> element);
	
	Spice::Vector runSimulation(double dt = 0.0);
	std::vector<TransientResult> runTransient(double stopTime, double dt);
};