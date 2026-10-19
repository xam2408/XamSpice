#include <iostream>
#include <vector>
#include <memory>
#include "Math/Types.hpp"
#include "Elements/Resistor.hpp"
#include "Elements/VoltageSource.hpp"
#include "Elements/Capacitor.hpp"
#include "Circuit.hpp"
#include "SimulationStructs.hpp"
#include "Utils/NetlistParser.hpp"

int main() {
	
	NetlistParser parser;
	
	parser.readNetlistToString("C:/Users/PC/Desktop/circuit.txt");
	std::cout << "NETLIST LENGTH: " << parser.netlistText.size() << "\n";
	parser.ParseNetlist(parser.netlistText);

	Circuit circuit(parser.GetNodeCount());

	parser.AddElements(parser.netlistToParse, circuit);

	const double dt = 0.0001;
	double totalTime = 0.01;

	std::vector<TransientResult> results = circuit.runTransient(totalTime, dt);
	
	for (const auto& step : results) {
		std::cout << step.time << "\t\t";

		for (size_t node = 0; node <= parser.GetNodeCount(); ++node) {
			std::cout << step.voltages.getVoltage(node) << "\t\t";
		}
		std::cout << "\n";
	}

	return 0;
}