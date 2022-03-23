#ifndef HOSTDETECTOR_COLORBUTTON_H
#define HOSTDETECTOR_COLORBUTTON_H

#include <QPushButton>
#include <QColor>

class ColorButton :public QPushButton
{
	Q_OBJECT;
public:
	ColorButton(QColor color,QWidget* parent = nullptr);
	~ColorButton() {};

	QColor getColor();

signals:
	void colorChanged(QColor);

private:
	void setColor(QColor);

	QColor m_color;
};


#endif // HOSTDETECTOR_COLORBUTTON_H

