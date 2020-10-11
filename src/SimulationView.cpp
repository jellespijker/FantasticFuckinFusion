//
// Created by Jelle Spijker on 10/11/20.
//

#include <QtGui/QPen>
#include <QtGui/QPainter>

#include <spdlog/spdlog.h>

#include "FFF/SimulationView.h"

namespace FFF {

PieChart::PieChart(QQuickItem* parent) : QQuickPaintedItem(parent)
{
  spdlog::debug("Constructing a new PieChart");
}

QString PieChart::name() const
{
  return m_name;
}

void PieChart::setName(const QString& name)
{
  spdlog::debug("Setting the name to {}", name.toStdString());
  m_name = name;
}

QColor PieChart::color() const
{
  return m_color;
}

void PieChart::setColor(const QColor& color)
{
  spdlog::debug("Setting the color to {}", color.name().toStdString());
  m_color = color;
}

void PieChart::paint(QPainter* painter)
{
  spdlog::debug("Painting");
  QPen pen(m_color, 2);
  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);
  painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
}


}// namespace FFF
