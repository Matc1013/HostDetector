#ifndef HOSTDETECTOR_DETECTMANAGER_H
#define HOSTDETECTOR_DETECTMANAGER_H

#include "hoststatuswidget.h"
#include "detectworker.h"

class DetectManager :public QObject
{
	Q_OBJECT;
public:
	DetectManager(QObject* parent = nullptr);
	~DetectManager();

	void doDetect(QString ipSegment);
	void stopDetect();

signals:
	void detectResult(QString, int);
	void allFinished();

private:
	QList<DetectWorker*> m_workers;
};

#endif // HOSTDETECTOR_DETECTMANAGER_H

