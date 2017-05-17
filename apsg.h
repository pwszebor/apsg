//
// Created by pwszebor on 14.05.17.
//

#pragma once

#include <QObject>
#include <QtQml/QJSEngine>
#include <QtQml/QQmlEngine>

namespace apsg {

class APSG : public QObject {
    Q_OBJECT
public:
    static APSG &sharedInstance();
    static QObject *typeProvider(QQmlEngine *, QJSEngine *);

    Q_PROPERTY(int num READ num WRITE setNum NOTIFY numChanged)

    void setNum(int n) {
        _num = n;
    }

    int num() {
        return _num;
    }

signals:
    void numChanged();

private slots:
    void numChange();

private:
    APSG();
    ~APSG();

    APSG(const APSG &) = delete;
    APSG(APSG &&) = delete;

    int _num;
};

}
