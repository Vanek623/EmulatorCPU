#include "regsWidget.h"

RegsWiget::RegsWiget(const QString title, const quint16 value){
    title = new QLabel(title);
    value = new QLabel(value);
}
