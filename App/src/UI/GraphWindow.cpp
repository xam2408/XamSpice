#include "UI/GraphWindow.hpp"
#include <memory>

GraphWindow::GraphWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("XamSpice");
    resize(800, 500);

    chart = new QChart();
    chart->legend()->setVisible(true);

    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);
}

void GraphWindow::SetVoltageData(const std::vector<TransientResult>& results, int node) {

    if (results.empty()) return;

    std::unique_ptr<QLineSeries> lineSeries = std::make_unique<QLineSeries>();
    lineSeries->setName(QString("V(%1)").arg(node));

    for (const auto& item : results) {
        lineSeries->append(item.time, item.voltages.getVoltage(node));
    }

    chart->addSeries(lineSeries.release());
    chart->createDefaultAxes();

}