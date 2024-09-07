#include "mylabel.h"
 
MyLabel::MyLabel(QWidget *parent)
    : QLabel(parent)
{
    color = QColor(Qt::black);
    setPalette(QPalette(color));
}
 
MyLabel::~MyLabel()
{
}
 
void MyLabel::setTextColor(const QColor &c)
{
    color = c;
    setPalette(QPalette(color));
}
 
QColor MyLabel::textColor() const
{
    return color;
}