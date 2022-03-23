#ifndef HOSTDETECTOR_MAINWINDOW_H
#define HOSTDETECTOR_MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>

class MainWindow :public QMainWindow
{
	Q_OBJECT;
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void processDetectResult(QString,int);
	void onStartDetect(QString);
	void onStopDetect();
	void onAllFinished();

private:
	class DetectManager* m_detectManager = nullptr;
	class HostStatusWidget* m_hostStatusWidget = nullptr;
	class OperateWidget* m_operateWidget = nullptr;
};

#endif // HOSTDETECTOR_MAINWINDOW_H

