#include "GraphView.h"

#include "ui_GraphView.h"

namespace s21 {
GraphWindow::GraphWindow(Controller *c, QWidget *parent)
    : QDialog(parent), ui(new Ui::GraphWindow), controller(c) {
  ui->setupUi(this);
}

GraphWindow::~GraphWindow() { delete ui; }

void GraphWindow::signal() {
  ui->graph->xAxis->setRange(-10, 10);
  ui->graph->yAxis->setRange(-10, 10);
  controller->CalcGraph(graph_points, xBegin, xEnd);
  ui->graph->addGraph();
  ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->graph->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
  qfirst =
      QVector<double>(graph_points.first.begin(), graph_points.first.end());
  qsecond =
      QVector<double>(graph_points.second.begin(), graph_points.second.end());
  ui->graph->graph(0)->addData(qfirst, qsecond);
  ui->graph->replot();
  ui->graph->setInteraction(QCP::iRangeZoom, true);
  ui->graph->setInteraction(QCP::iRangeDrag, true);
}

void GraphWindow::on_graph_button_clicked() {
  if (ui->xend->value() > ui->xbegin->value()) {
    controller->CalcGraph(graph_points, ui->xbegin->value(), ui->xend->value());
    qfirst =
        QVector<double>(graph_points.first.begin(), graph_points.first.end());
    qsecond =
        QVector<double>(graph_points.second.begin(), graph_points.second.end());
    ui->graph->graph(0)->addData(qfirst, qsecond);
  }
}
}  // namespace s21
