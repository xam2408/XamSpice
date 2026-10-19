#include <execution>
#include <algorithm>
#include "Circuit.hpp"

Circuit::Circuit(int n) : nodes(n) {}

void Circuit::addElement(std::unique_ptr<Element> element) {
	elements.push_back(std::move(element));
}

Spice::Vector Circuit::runSimulation(double dt) {
	Spice::Matrix G(nodes, nodes);
	Spice::Vector I(nodes);

	G.setZero();
	I.setZero();

	std::for_each(
		std::execution::par, 
		elements.begin(), elements.end(),

		[&](auto& element) {
			element->stampToEquation(G, I, dt);
		});

	return I.solve(G);
}