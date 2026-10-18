#include <iostream>
#include <vector>
#include <memory>
#include "Math/Types.hpp"
#include "Elements/Resistor.hpp"

int main() {
	
	const int nodes{ 2 };

	Spice::Matrix G(nodes, nodes);	//conductance Matrix
	Spice::Vector I(nodes);			//current Vector
	G.setZero();
	I.setZero();

	std::vector<std::unique_ptr<Element>> elements;

	std::unique_ptr<Resistor> r1 = 
		std::make_unique<Resistor>(1, 2, 100.0);

	std::unique_ptr<Resistor> r2 =
		std::make_unique<Resistor>(2, 0, 100.0);

	
	elements.push_back(std::move(r1));
	elements.push_back(std::move(r2));
	I.add(1, 1.0);

	for (auto& element : elements) 
		element->stampToEquation(G, I, 0.0);

	Spice::Vector voltages = I.solve(G);

	std::cout << "Node 1 voltage: " << voltages.getVoltage(1) << "\n";
	std::cout << "Node 2 voltage: " << voltages.getVoltage(2) << "\n";


	return 0;
}