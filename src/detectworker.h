#ifndef HOSTDETECTOR_DETECTWORKER_H
#define HOSTDETECTOR_DETECTWORKER_H

#include <QThread>
#include <QProcess>
#include <QSemaphore>
#include <QQueue>
#include <QMutex>
#include <QAtomicInt>

class DetectWorker :public QObject
{
	Q_OBJECT;
public:
	DetectWorker();
	~DetectWorker();

	static void addTask(QString ip);
	static void addTask(QList<QString>& ip);
	static void stopAll(bool isQuit = true);

signals:
	void detectFinished(QString ip, int value);
	void allFinished();

public slots:
	void doWork();

private:
	QThread m_workThread;

	static QSemaphore s_resource;
	static QQueue<QString> s_taskQueue;
	static QMutex s_taskMutex;
	static bool s_stopFlag;
	static int s_workerCount;
	static QAtomicInt s_taskCount;
	static QAtomicInt s_taskFinishCount;
};


#endif // HOSTDETECTOR_DETECTWORKER_H

