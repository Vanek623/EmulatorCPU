#include "lexeme.h"

lexeme::lexeme()
{
    type = UNKWNOWN;
    value = "";
}

lexeme::lexeme(const LexType type, const QString value)
{
    this->type = type;
    this->value = value;
}

LexType lexeme::getType() const
{
    return type;
}

QString lexeme::getValue() const
{
    return value;
}

void lexeme::setType(const LexType type)
{
    this->type = type;
}

void lexeme::setValue(const QString value)
{
    this->value = value;
}
