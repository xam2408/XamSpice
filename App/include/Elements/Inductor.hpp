#pragma once
#include "Elements/Element.hpp"

class Inductor : public Element {
private:
	int nodeA;
	int nodeB;
	double inductance;
	double pastVoltage = 0.0;
	double pastCurrent = 0.0;

	const double shortResistance = 1e-6;
	const double dcConductance = 1.0 / shortResistance;

public:
	Inductor(int nA, int nB, double L, double prevV = 0.0, double prevC = 0.0) :
		nodeA(nA), nodeB(nB), inductance(L), pastVoltage(prevV), pastCurrent(prevC) {
	}

	void stampToEquation(
		Spice::Matrix& G, Spice::Vector& I,
		double dt = 0.0) override {

		if (dt <= 0.0) {
			G.add(nodeA, nodeB, dcConductance);
			return;
		}

		stampToEquationTransient(G, I, dt);
	}

	void stampToEquationTransient(
		Spice::Matrix& G, Spice::Vector& I,
		double dt) {

		//v(t) = L * di(t)/dt
		//i = in-1 + geq * vn-1

		double gEquivalent = dt / (2.0 * inductance);
		double iHist = pastCurrent + (gEquivalent * pastVoltage);

		G.add(nodeA, nodeB, gEquivalent);

		if (nodeA > 0) I.add(nodeA, -iHist);
		if (nodeB > 0) I.add(nodeB, iHist);
	}

	void updateState(const Spice::Vector& V, double dt) override {
		double vA = V.getVoltage(nodeA);
		double vB = V.getVoltage(nodeB);
		double currentVoltage = vA - vB;

		if (dt <= 0.0) {
			pastVoltage = currentVoltage;
			pastCurrent = currentVoltage / shortResistance;
			return;
		}

		double gEquivalent = dt / (2.0 * inductance);
		double iHist = pastCurrent + (gEquivalent * pastVoltage);

		double currentCurrent = (gEquivalent * currentVoltage) + iHist;

		pastVoltage = currentVoltage;
		pastCurrent = currentCurrent;
	}
};