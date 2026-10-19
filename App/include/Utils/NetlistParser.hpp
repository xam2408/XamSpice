#pragma once
#include <fstream>
#include <string>
#include "SimulationStructs.hpp"
#include "Elements/Element.hpp"
#include "Circuit.hpp"
#include <vector>

struct NetlistItem {
	std::string elementType;
	int nodeA;
	int nodeB;
	double value;
};

class NetlistParser {
private:
	std::string netlistFilePath;
public:
	std::string netlistText;
	std::vector<NetlistItem> netlistToParse;
	int nodeCount = 0;

	NetlistParser() {}
	
	void readNetlistToString(const std::string& netlistFilePath);
	void ParseNetlist(const std::string& rawNetlist);
	void AddElements(const std::vector<NetlistItem>& items, Circuit& circuit);
	int GetNodeCount() const { return nodeCount; }
};