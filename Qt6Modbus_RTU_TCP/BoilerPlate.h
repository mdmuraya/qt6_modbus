#ifndef BOILERPLATE_H
#define BOILERPLATE_H

#include <QObject>

class BoilerPlate : public QObject
{
    Q_OBJECT
public:
    explicit BoilerPlate(QObject *parent = nullptr);

signals:
};

#endif // BOILERPLATE_H
