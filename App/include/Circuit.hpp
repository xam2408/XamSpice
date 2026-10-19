#pragma once
#include <memory>
#include <vector>
#include "Elements/Element.hpp"

class Circuit {

private:

	int nodes;
	std::vector<std::unique_ptr<Element>> elements;

public:

	Circuit(int nodes);
	
	void addElement(std::unique_ptr<Element> element);
	
	Spice::Vector runSimulation(double dt = 0.0);
};