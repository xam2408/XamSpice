#pragma once
#include <QMainWindow>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <vector>
#include "SimulationStructs.hpp"


class GraphWindow : public QMainWindow {
	Q_OBJECT
private:
	QChart* chart = nullptr;
	QChartView* chartView = nullptr;
public:
	explicit GraphWindow(QWidget* parent = nullptr);
	~GraphWindow() override = default;

	void SetVoltageData(const std::vector<TransientResult>& results, int node);
};

