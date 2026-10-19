#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <memory>
#include "Utils/NetlistParser.hpp"
#include "Elements/ElementIncludes.hpp"

void NetlistParser::readNetlistToString(const std::string& netlistFilePath) {
	std::ifstream NetlistFile(netlistFilePath);
	std::string line;

	while (std::getline(NetlistFile, line)) {
		netlistText.append(line + "\n");
	}

	NetlistFile.close();
}

void NetlistParser::ParseNetlist(const std::string& rawNetlist) {
	std::istringstream stream(rawNetlist);
	std::string line;

	while (std::getline(stream, line)) {
		if (line.empty()) continue;
		if (line[0] == '!') continue;

		std::istringstream lineStream(line);
		std::string name;
		std::string nodeAStr;
		std::string nodeBStr;
		double value;

		if (lineStream >> name >> nodeAStr >> nodeBStr >> value) {
			NetlistItem netlistItem;

			netlistItem.elementType = name;
			netlistItem.nodeA = std::stoi(nodeAStr);
			netlistItem.nodeB = std::stoi(nodeBStr);
			netlistItem.value = value;

			nodeCount = std::max({ nodeCount, netlistItem.nodeA, netlistItem.nodeB });
			netlistToParse.push_back(netlistItem);
		}
	}
}

void NetlistParser::AddElements(const std::vector<NetlistItem>& items, Circuit& circuit) {
	for (const auto& item : items) {
		
		char component = std::toupper(item.elementType[0]);

		int netA = item.nodeA;
		int netB = item.nodeB;
		double value = item.value;


		switch (component) {
		case 'R':
			circuit.addElement(
				std::make_unique<Resistor>(netA, netB, value));
			break;
		case 'C':
			circuit.addElement(
				std::make_unique<Capacitor>(netA, netB, value));
			break;
		case 'V':
			circuit.addElement(
				std::make_unique<VoltageSource>(netA, netB, value));
			break;
		case 'I':
			circuit.addElement(
				std::make_unique<CurrentSource>(netA, netB, value));
			break;
		default:
			break;
		}
	}
}

