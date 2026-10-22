#pragma once
#include "Element.hpp"

class Pulse : public Element{
private:
	int nodeA;
	int nodeB;
	
	double voltageHigher;
	double voltageLower;
	double periodMs;			//ms
	double timeOn;
	double timeOff;
	double currentTime = 0.0;

	double eps = 1e-9;
	
public:
	Pulse(
		int a, int b, double vH, double vL,
		double T, double tOn) :
		nodeA(a), nodeB(b), voltageHigher(vH), voltageLower(vL),
		periodMs(T), timeOn(tOn), timeOff(T - tOn) {}

	void stampToEquation(
		Spice::Matrix& G, Spice::Vector& I,
		double deltaTime = 0.0
	) override;

};