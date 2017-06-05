//
// Created by pwszebor on 05.06.17.
//

#pragma once

#include <QtQuick/QQuickPaintedItem>
#include <vector>
#include "qcustomplot.h"
#include <memory>
#include <QSharedPointer>

class Plot : public QQuickPaintedItem {
Q_OBJECT

public:
    Plot(QQuickItem *parent = Q_NULLPTR);
    ~Plot();

    void paint(QPainter *painter) override;
    void setData(const std::vector<std::vector<double>> &data, const QString &xAxis, const QString &yAxis, bool logarithmic);

    Q_INVOKABLE void plot();

private slots:
    void afterReplot();

private:
    std::vector<QColor> getNColors(unsigned long n);

private:
    std::vector<std::vector<double>> _data;
    std::unique_ptr<QCustomPlot> _plot;
    QString _xAxis;
    QString _yAxis;
    bool _logarithmic;
    QSharedPointer<QCPAxisTickerLog> _logTicker;
    QSharedPointer<QCPAxisTicker> _linTicker;
};



