#pragma once

#include <QString>

enum LexType{
    UNKWNOWN,
    COMMAND,
    OPERAND,
    MARK_U,
    MARK_I
};

class lexeme
{
private:
    LexType type;
    QString value;

public:
    lexeme();
    lexeme(const LexType type, const QString value);

    LexType getType() const;
    QString getValue() const;

    void setType(const LexType type);
    void setValue(const QString value);
};
