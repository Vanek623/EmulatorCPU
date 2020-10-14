#ifndef BUILDER_H
#define BUILDER_H

#include "command.h"
#include <QList>
#include <QString>
#include <QMap>
#include <QRegExp>
#include <QDebug>
#include "comnames.h"
#include "cominfo.h"

class Builder
{
private:
    QList<Command*> *program;
    QMap<QString, COMINFO> *commandList;
    QMap<QString, quint16> *marks;

public:
    Builder();
    ~Builder();
    int compile(const QString &rawProgTxt);
    QList<Command*> *getProgrammList() const;

signals:
    void sendResultMsg(const QString &msg);

private:
    void setupCommandList();
    int parse(const QStringList &words);
    COMINFO getInfo(const QString &word,const QList<int> &shifts) const;
};

#endif // BUILDER_H
