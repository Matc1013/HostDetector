#include "colorbutton.h"
#include <QColorDialog>

ColorButton::ColorButton(QColor color, QWidget* parent)
	:QPushButton(parent)
{
	setColor(color);
	connect(this, &QPushButton::clicked, this, [this] {
		QColor c = QColorDialog::getColor(m_color);
		if (c.isValid())
			setColor(c);
		});
}

QColor ColorButton::getColor()
{
	return m_color;
}

void ColorButton::setColor(QColor color)
{
	if (m_color == color) return;

	m_color = color;
	this->setStyleSheet(QString("background-color:%1").arg(m_color.name(QColor::HexRgb)));
	emit colorChanged(m_color);
}
