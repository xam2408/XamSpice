#include <iostream>
#include <vector>
#include <memory>
#include "Math/Types.hpp"
#include "Elements/Resistor.hpp"
#include "Elements/VoltageSource.hpp"
#include "Elements/Capacitor.hpp"
#include "Circuit.hpp"
#include "SimulationStructs.hpp"


int main() {
	

	const int nodes{ 2 };

	std::unique_ptr<Resistor> r1 = 
		std::make_unique<Resistor>(1, 2, 1000.0);

	std::unique_ptr<Capacitor> c1 =
		std::make_unique<Capacitor>(2, 0, 1e-6, 0.0, 0.0);
	
	std::unique_ptr<VoltageSource> i1 =
		std::make_unique<VoltageSource>(1, 5.0);

	Circuit circuit(nodes);
	circuit.addElement(std::move(r1));
	circuit.addElement(std::move(c1));
	circuit.addElement(std::move(i1));

	std::vector<TransientResult> voltages = circuit.runTransient(0.01, 0.0001);

	for (const auto& step : voltages) {
		double time = step.time;
		double v1 = step.voltages.getVoltage(1);
		double v2 = step.voltages.getVoltage(2);

		std::cout << time << "\t\t" << v1 << "\t\t" << v2 << "\n";

	}


	return 0;
}