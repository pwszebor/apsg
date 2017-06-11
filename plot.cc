//
// Created by pwszebor on 05.06.17.
//

#include <iostream>
#include "plot.h"
#include <algorithm>
#include <thread>
#include <random>

Plot::Plot(QQuickItem *parent) :
        QQuickPaintedItem(parent),
        _plot(std::make_unique<QCustomPlot>()),
        _graphTitle(),
        _xAxis(),
        _yAxis(),
        _logarithmic(false),
        _logTicker(QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog)),
        _linTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker)),
        _contextMenu(std::make_unique<QMenu>()) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";

    setFlag(QQuickItem::ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);

    _title = std::make_unique<QCPTextElement>(_plot.get());
    _plot->plotLayout()->insertRow(0);
    _plot->plotLayout()->addElement(0, 0, _title.get());
    _title->setFont(QFont("sans", 12, QFont::Bold));

    _plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    _logTicker->setLogBase(10.0);

    _contextMenu->addAction("Save as...", this, &Plot::saveGraph);
    _contextMenu->addAction("Zoom out to original size", this, &Plot::zoomToOriginal);

    connect(_plot.get(), SIGNAL(afterReplot()), this, SLOT(afterReplot()));
}

Plot::~Plot() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
}

void Plot::paint(QPainter *painter) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";

    if (!_data.size())
        return;

    QRect rect = boundingRect().toRect();
    rect.setTopLeft(QPoint(0, 0));
    _plot->setGeometry(rect);
    _plot->setViewport(rect);

    QPixmap picture(boundingRect().size().toSize());
    QCPPainter qcpPainter(&picture);
    _plot->toPainter(&qcpPainter);
    painter->drawPixmap(QPoint(), picture);

}

void Plot::setData(const std::vector<std::vector<double>> &data, const QString &title, const QString &xAxis, const QString &yAxis, bool logarithmic) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    _data = data;
    _graphTitle = title;
    _xAxis = xAxis;
    _yAxis = yAxis;
    _logarithmic = logarithmic;
}

void Plot::plot() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";

    _plot->xAxis->setLabel(_xAxis);
    _plot->yAxis->setLabel(_yAxis);
    if (_logarithmic) {
        _plot->yAxis->setScaleType(QCPAxis::stLogarithmic);
        _plot->yAxis->setTicker(_logTicker);
    } else {
        _plot->yAxis->setScaleType(QCPAxis::stLinear);
        _plot->yAxis->setTicker(_linTicker);
    }
    _title->setText(_graphTitle);

    if (!_data.size())
        return;
    _plot->xAxis->setRange(0, _data.at(0).size());

    _plot->clearGraphs();
    double min = _data.front().front(), max = _data.front().front();
    for (auto i = 0; i < _data.size(); ++i) {
        double mmax = *std::max_element(_data[i].begin(), _data[i].end());
        max = mmax > max ? mmax : max;
        double mmin = *std::min_element(_data[i].begin(), _data[i].end());
        min = mmin < min ? mmin : min;
        _plot->addGraph();
    }
    _plot->yAxis->setRange(min, max);

    QCPGraph *graph;
    int i = 0;
    auto colors = getNColors(_data.size());
    for (const auto &plot : _data) {
        graph = _plot->graph(i);
        graph->setPen(QPen(colors[i]));
        std::vector<double> samples(plot.size());
        std::iota(samples.begin(), samples.end(), 0);
        graph->setData(QVector<double>::fromStdVector(samples), QVector<double>::fromStdVector(plot), true);
        ++i;
    }

    _plot->replot();
}

void Plot::afterReplot() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    update();
}

const std::vector<QColor> Plot::getNColors(unsigned long n) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    std::vector<QColor> colors;

    for (unsigned i = 0; i < n; ++i) {
        QColor color;
        color.setHsl(dis(gen), 200, 100);
        colors.push_back(color);
    }
    return colors;
}

void Plot::mousePressEvent(QMouseEvent *event) {
//    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    routeMouseEvents(event);
}

void Plot::mouseMoveEvent(QMouseEvent *event) {
//    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    routeMouseEvents(event);
}

void Plot::mouseReleaseEvent(QMouseEvent *event) {
//    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    if (event->button() == Qt::RightButton) {
        showContextMenu(event->globalPos());
    }
    routeMouseEvents(event);
}

void Plot::mouseDoubleClickEvent(QMouseEvent *event) {
//    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    routeMouseEvents(event);
}

void Plot::wheelEvent(QWheelEvent *event) {
//    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    routeWheelEvents(event);
}

void Plot::routeMouseEvents(const QMouseEvent *event) {
//    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    QMouseEvent *newEvent = new QMouseEvent(event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers());
    QCoreApplication::postEvent(_plot.get(), newEvent);
}

void Plot::routeWheelEvents(const QWheelEvent *event) {
//    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    QWheelEvent *newEvent = new QWheelEvent(event->pos(), event->delta(), event->buttons(), event->modifiers(), event->orientation());
    QCoreApplication::postEvent(_plot.get(), newEvent);
}

void Plot::showContextMenu(const QPoint &pos) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    if (_plot->graphCount()) {
        _contextMenu->popup(pos);
    }
}

void Plot::zoomToOriginal() {
    if (_plot->graphCount()) {
        _plot->rescaleAxes();
        _plot->replot();
    }
}

void Plot::saveGraph() {
    QString file = QFileDialog::getSaveFileName(Q_NULLPTR, "Save graph", QDir::homePath(), "*.png");
    if (!file.isEmpty()) {
        _plot->savePng(file);
    }
}
