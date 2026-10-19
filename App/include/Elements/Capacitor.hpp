#pragma once

#include "Element.hpp"

class Capacitor : public Element {
private:
	int nodeA;
	int nodeB;
	double capacitance;
	double previousVoltage = 0.0;
	double previousCurrent = 0.0;
public:
	Capacitor(int a, int b, double c, double prevV, double prevC) :
		nodeA(a), nodeB(b), capacitance(c), previousVoltage(prevV), previousCurrent(prevC) { }

	void stampToEquation(
			Spice::Matrix& G, Spice::Vector& I,
			double dt) override {

		if (dt == 0.0) {
			return;
		}

		stampToEquationTransient(G, I, dt);
	
	}

	void stampToEquationTransient(
		Spice::Matrix& G, Spice::Vector& I,
		double dt) {

		if (dt <= 0.0) return;

		//i(t) = C* dv(t)/dt
		//delta v = dt/2C(in + in-1)
		//i = 2C/dt * vn - in-1  ~ 2C/dt * vc

		double gEquivalent = 2.0 * capacitance / dt;
		double i = (gEquivalent * previousVoltage) + previousCurrent;

		G.add(nodeA, nodeB, gEquivalent);
		
		if (nodeA > 0) I.add(nodeA, i);
		if (nodeB > 0) I.add(nodeB, -i);

	}

	void updateState(const Spice::Vector& V, double dt) {
		double vA = V.getVoltage(nodeA);
		double vB = V.getVoltage(nodeB);

		double currentVoltage = vA - vB;

		double gEquivalent = (2.0 * capacitance) / dt;

		double currentCurrent = 
			(gEquivalent * currentVoltage) - (gEquivalent * previousVoltage + previousCurrent);

		previousVoltage = currentVoltage;
		previousCurrent = currentCurrent;
	}
};