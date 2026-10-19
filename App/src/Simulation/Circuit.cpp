#include <execution>
#include <algorithm>
#include "Circuit.hpp"
#include "SimulationStructs.hpp"

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
			elements.begin(), elements.end(),

		[&](auto& element) {
			element->stampToEquation(G, I, dt);
		});

	return I.solve(G);
}

std::vector<TransientResult> Circuit::runTransient(
	double stopTime, double dt) {

	std::vector<TransientResult> voltagesHistory;
	double currentTime = 0.0;
	
	while (currentTime <= stopTime) {

		Spice::Matrix G(nodes, nodes);
		Spice::Vector I(nodes);

		G.setZero();
		I.setZero();

		std::for_each(
			elements.begin(), elements.end(),
			[&](auto& element) {
				element->stampToEquation(G, I, dt);
			});

		Spice::Vector voltages = I.solve(G);
		voltagesHistory.push_back({currentTime, voltages});

		std::for_each(
			elements.begin(), elements.end(),
			[&](auto& element) {
				element->updateState(voltages, dt);
			});

		currentTime += dt;
	}

	return voltagesHistory;
	
}