#ifndef HOSTDETECTOR_HOSTSTATUSITEM_H
#define HOSTDETECTOR_HOSTSTATUSITEM_H

#include <QLabel>
#include <QPixmap>
#include "globalsetting.h"

class HostStatusItem :public QLabel
{
public:
	HostStatusItem(int itemIdx,QWidget* parent = nullptr);
	~HostStatusItem();

	void setStatus(HostNetworkStatus status);

	static int getItemWidth();
	static int getItemHeight();

protected:
	void paintEvent(QPaintEvent*);

private:
	int m_itemIdx = 0;
	HostNetworkStatus m_status = HostNetworkStatus::HNS_UNRELY;
};

#endif // HOSTDETECTOR_HOSTSTATUSITEM_H

