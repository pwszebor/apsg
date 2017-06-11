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

    void setData(const std::vector<std::vector<double>> &data, const QString &title, const QString &xAxis,
                 const QString &yAxis, bool logarithmic);

    Q_INVOKABLE void plot();

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

private slots:

    void afterReplot();

private:
    const std::vector<QColor> getNColors(unsigned long n);

    void routeMouseEvents(const QMouseEvent *event);

    void routeWheelEvents(const QWheelEvent *event);

    void showContextMenu(const QPoint &pos);

    void zoomToOriginal();

    void saveGraph();

private:
    std::vector<std::vector<double>> _data;
    std::unique_ptr<QCustomPlot> _plot;
    std::unique_ptr<QCPTextElement> _title;
    QString _graphTitle;
    QString _xAxis;
    QString _yAxis;
    bool _logarithmic;
    QSharedPointer<QCPAxisTickerLog> _logTicker;
    QSharedPointer<QCPAxisTicker> _linTicker;
    std::unique_ptr<QMenu> _contextMenu;
};



