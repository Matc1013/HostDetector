#ifndef HOSTDETECTOR_HOSTSTATUSWIDGET_H
#define HOSTDETECTOR_HOSTSTATUSWIDGET_H

#include <QFrame>
#include <QMap>
#include "hoststatusitem.h"


class HostStatusWidget :public QFrame
{
	Q_OBJECT;
public:
	HostStatusWidget(QWidget* parent = nullptr);
	~HostStatusWidget();

	void setHostResult(QString,int);
	void resetAllItemStatus();
private:
	QList<HostStatusItem*> m_itemList;
};

#endif // HOSTDETECTOR_HOSTSTATUSWIDGET_H

