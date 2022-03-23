#include "hoststatuswidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QDebug>

int rowItemCount = 12;

HostStatusWidget::HostStatusWidget(QWidget* parent)
	:QFrame(parent)
{
	int width = rowItemCount * (HostStatusItem::getItemWidth() + 10);
	int height = ((255 / rowItemCount) + 1) * (HostStatusItem::getItemHeight() + 10);
	setFixedSize(width,height);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setSpacing(10);

	//255/10 = 25---5
	QHBoxLayout* rowLayout = nullptr;
	for (int idx = 1; idx < 256; ++idx)
	{
		if ((idx-1) % rowItemCount == 0)
		{
			rowLayout = new QHBoxLayout;
			rowLayout->setSpacing(10);
			mainLayout->addLayout(rowLayout);
		}

		HostStatusItem* item = new HostStatusItem(idx);
		rowLayout->addWidget(item);
		m_itemList.append(item);

		if (idx == 255 && 255 % rowItemCount != 0)
		{
			rowLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
		}
		
	}

	this->setFrameShape(QFrame::Panel);
}

HostStatusWidget::~HostStatusWidget()
{

}

void HostStatusWidget::setHostResult(QString ip, int value)
{
	QStringList sl = ip.split(".", Qt::SkipEmptyParts);
	int idx = sl[3].toInt() - 1;
	if (value == -1)
		m_itemList[idx]->setStatus(HostNetworkStatus::HNS_UNRELY);
	else if (value >= 0 && value < 100)
		m_itemList[idx]->setStatus(HostNetworkStatus::HNS_GOOD);
	else if (value >= 100 && value < 300)
		m_itemList[idx]->setStatus(HostNetworkStatus::HNS_FINE);
	else if (value >= 300)
		m_itemList[idx]->setStatus(HostNetworkStatus::HNS_BAD);
	else
		qDebug() << "Unexpected logic!";
}

void HostStatusWidget::resetAllItemStatus()
{
	for (auto it: m_itemList)
	{
		it->setStatus(HostNetworkStatus::HNS_UNRELY);
	}
}

