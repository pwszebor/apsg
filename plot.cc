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
        _xAxis(),
        _yAxis(),
        _logarithmic(false),
        _logTicker(QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog)),
        _linTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker)) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    setFlag(QQuickItem::ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
    _plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    _logTicker->setLogBase(10.0);
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

void Plot::setData(const std::vector<std::vector<double>> &data, const QString &xAxis, const QString &yAxis, bool logarithmic) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    _data = data;
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

std::vector<QColor> Plot::getNColors(unsigned long n) {
    std::vector<QColor> colors;
    if (n == 1) {
        colors.push_back(QColor(Qt::darkBlue));
        return colors;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    for (unsigned i = 0; i < n; ++i) {
        QColor color;
        color.setHsl(dis(gen), 200, 175);
        colors.push_back(color);
    }
    return colors;
}
