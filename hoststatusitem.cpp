#include "hoststatusitem.h"
#include <QPainter>

const int itemWidth = 40;
const int itemHeight = 20;

HostStatusItem::HostStatusItem(int itemIdx, QWidget* parent /*= nullptr*/)
	:QLabel(parent),m_itemIdx(itemIdx)
{
	setFixedSize(itemWidth, itemHeight);
	setAlignment(Qt::AlignCenter);

	setFrameShape(QFrame::Box);
}

HostStatusItem::~HostStatusItem()
{

}

void HostStatusItem::setStatus(HostNetworkStatus status)
{
	m_status = status;
	update();
}

int HostStatusItem::getItemWidth()
{
	return itemWidth;
}

int HostStatusItem::getItemHeight()
{
	return itemHeight;
}

void HostStatusItem::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.setPen(Qt::black);
	painter.setBrush(GlobalSetting::getInstance()->getColorByStatus(m_status));
	painter.drawRect(0, 0, this->width()-2, this->height()-2);
	painter.drawText(this->rect(), Qt::AlignCenter, QString::number(m_itemIdx));
}
