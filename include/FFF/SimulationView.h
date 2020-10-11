//
// Created by Jelle Spijker on 10/11/20.
//

#ifndef FANTASTICFUCKINFUSION_SIMULATIONVIEW_H
#define FANTASTICFUCKINFUSION_SIMULATIONVIEW_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>

namespace FFF {

class PieChart : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName)
  Q_PROPERTY(QColor color READ color WRITE setColor)
  QML_ELEMENT

public:
  explicit PieChart(QQuickItem* parent = 0);

  [[nodiscard]] QString name() const;
  void setName(const QString& name);

  QColor color() const;
  void setColor(const QColor& color);

  void paint(QPainter* painter);

private:
  QString m_name;
  QColor m_color;
};

}// namespace FFF

#endif//FANTASTICFUCKINFUSION_SIMULATIONVIEW_H
