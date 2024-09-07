#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel {
  Q_OBJECT
  Q_PROPERTY(QColor color READ textColor WRITE setTextColor)

public:
  MyLabel(QWidget *parent = nullptr);
  ~MyLabel();
  void setTextColor(const QColor &c);
  QColor textColor() const;

private:
  QColor color;
};

#endif // MYLABEL_H