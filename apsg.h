//
// Created by pwszebor on 14.05.17.
//

#pragma once

#include <QObject>
#include <QtQml/QJSEngine>
#include <QtQml/QQmlEngine>

namespace apsg {
Q_NAMESPACE

class APSG : public QObject {
    Q_OBJECT
public:

    enum class Algorithm {
        RLS,
        LMS
    };
    Q_ENUM(Algorithm)

    static APSG &sharedInstance();
    static QObject *typeProvider(QQmlEngine *, QJSEngine *);

    Q_PROPERTY(Algorithm algorithm READ algorithm WRITE changeAlgorithm NOTIFY algorithmChange)

    const Algorithm algorithm() const;
    void changeAlgorithm(const Algorithm algorithm);

signals:
    void algorithmChange();

private slots:
    void algorithmChanged();

private:
    APSG();
    ~APSG();

    APSG(const APSG &) = delete;
    APSG(APSG &&) = delete;

    Algorithm _algorithm;
};

}
