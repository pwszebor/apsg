//
// Created by pwszebor on 14.05.17.
//

#pragma once

#include <QObject>
#include <QtQml/QJSEngine>
#include <QtQml/QQmlEngine>
#include <QVariant>
#include "algorithm.h"
#include "plot.h"

class APSG : public QObject {
    Q_OBJECT
public:
    enum class AlgorithmType {
        RLS,
        LMS
    };
    Q_ENUM(AlgorithmType)

    static APSG &sharedInstance();
    static QObject *typeProvider(QQmlEngine *, QJSEngine *);

    Q_PROPERTY(AlgorithmType algorithm READ algorithm WRITE changeAlgorithm NOTIFY algorithmChange)
    Q_PROPERTY(int simulation READ simulation NOTIFY simulationStatusChanged)

    const AlgorithmType algorithm() const;
    void changeAlgorithm(const AlgorithmType algorithm);

    Q_INVOKABLE QVariant changeParameters(const QJSValue parameters);
    Q_INVOKABLE const QString errorString(int errorCode) const;

    const int simulation() const;
    Q_INVOKABLE int simulate();
    Q_INVOKABLE int stopSimulation();
    void changeStatus(SIMULATION_STATUS status);

    Q_INVOKABLE void setDataForPlotter(Plot *plotter, const QString &plotType, const QString &title, const QString &xAxis, const QString &yAxis, bool logarithmic);

signals:
    void algorithmChange();
    void simulationStatusChanged();

private slots:
    void algorithmChanged();

private:
    APSG();
    ~APSG();

    APSG(const APSG &) = delete;
    APSG(APSG &&) = delete;

    AlgorithmType _algorithmType;
    Algorithm *_algorithm;
    QJSValue _parameters;
    SIMULATION_STATUS _simulation;
};
