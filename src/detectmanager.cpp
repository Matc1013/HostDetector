#include "detectmanager.h"

const int workerCount = 6;

DetectManager::DetectManager(QObject* parent)
	:QObject(parent)
{
	for (int idx = 0; idx < workerCount; ++idx)
	{
		DetectWorker* work = new DetectWorker;
		QMetaObject::invokeMethod(work, "doWork", Qt::QueuedConnection);
		connect(work, &DetectWorker::detectFinished, this, &DetectManager::detectResult);
		connect(work, &DetectWorker::allFinished, this, &DetectManager::allFinished);
		m_workers.append(work);
	}
}

DetectManager::~DetectManager()
{
	DetectWorker::stopAll();
	qDeleteAll(m_workers);
}

void DetectManager::doDetect(QString ipSegment)
{
	QList<QString> sl;
	for (int idx = 1; idx < 256; ++idx)
		sl << QString("%1.%2").arg(ipSegment).arg(QString::number(idx));
	
	DetectWorker::addTask(sl);
}

void DetectManager::stopDetect()
{
	DetectWorker::stopAll(false);
}
