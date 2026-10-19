#include <iostream>
#include <vector>
#include <memory>
#include "Math/Types.hpp"
#include "Elements/Resistor.hpp"
#include "Elements/VoltageSource.hpp"
#include "Circuit.hpp"

int main() {
	
	const int nodes{ 2 };

	std::unique_ptr<Resistor> r1 = 
		std::make_unique<Resistor>(1, 2, 100.0);

	std::unique_ptr<Resistor> r2 =
		std::make_unique<Resistor>(2, 0, 100.0);
	
	std::unique_ptr<VoltageSource> i1 =
		std::make_unique<VoltageSource>(1, 10.0);

	Circuit circuit(nodes);
	circuit.addElement(std::move(r1));
	circuit.addElement(std::move(r2));
	circuit.addElement(std::move(i1));


	Spice::Vector voltages = circuit.runSimulation();

	std::cout << "Node 1 voltage: " << voltages.getVoltage(1) << "\n";
	std::cout << "Node 2 voltage: " << voltages.getVoltage(2) << "\n";


	return 0;
}