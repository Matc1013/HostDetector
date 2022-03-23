#include "detectworker.h"
#include <QMutexLocker>
#include <QDebug>

QSemaphore DetectWorker::s_resource(0);
QQueue<QString> DetectWorker::s_taskQueue;
QMutex DetectWorker::s_taskMutex;
bool DetectWorker::s_stopFlag = false;
int DetectWorker::s_workerCount = 0;
QAtomicInt DetectWorker::s_taskCount = 0;
QAtomicInt DetectWorker::s_taskFinishCount = 0;

DetectWorker::DetectWorker()
{
	this->moveToThread(&m_workThread);

	m_workThread.start();

	++s_workerCount;
}

DetectWorker::~DetectWorker()
{
	m_workThread.quit();
	m_workThread.wait();
}

void DetectWorker::addTask(QString ip)
{
	s_taskMutex.lock();
	s_taskQueue.enqueue(ip);
	s_taskMutex.unlock();

	s_resource.release();
	++s_taskCount;
}

void DetectWorker::addTask(QList<QString>& ip)
{
	s_taskMutex.lock();
	for (auto it : ip)
	{
		s_taskQueue.enqueue(it);
	}
	s_taskMutex.unlock();

	s_resource.release(ip.size());
	s_taskCount += ip.size();
}

void DetectWorker::stopAll(bool isQuit)
{
	s_taskCount = 0;
	s_taskFinishCount = 0;
	s_taskMutex.lock();
	s_taskQueue.clear();
	s_resource.acquire(s_resource.available());
	s_taskMutex.unlock();

	if (isQuit)
	{
		s_stopFlag = true;
		s_resource.release(s_workerCount);
	}
}

void DetectWorker::doWork()
{
	QProcess process;
	while (1)
	{
		s_resource.acquire();

		if (s_stopFlag) return;

		s_taskMutex.lock();
		if (s_taskQueue.isEmpty())
		{
			s_taskMutex.unlock();
			continue;
		}
		QString ip = s_taskQueue.dequeue();
		s_taskMutex.unlock();

		QString cmd = QString("ping %1 -n 2").arg(ip);

		process.start(cmd);
		process.waitForFinished();
		QString output = QString::fromLocal8Bit(process.readAllStandardOutput());
		QString key = tr("Average = ");
		int pos = output.indexOf(key);
		if (pos != -1)
		{
			output = output.mid(pos + key.size());
			int pos2 = output.indexOf("ms");
			int value = output.mid(0, pos2).toInt();
			emit detectFinished(ip, value);
		}
		else
		{
			emit detectFinished(ip, -1);
		}

		if (++s_taskFinishCount == s_taskCount)
		{
			s_taskCount = 0;
			s_taskFinishCount = 0;
			emit allFinished();
		}
	}
}

