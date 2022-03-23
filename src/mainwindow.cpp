#include "mainwindow.h"
#include "hoststatuswidget.h"
#include "detectmanager.h"
#include "operatewidget.h"

MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
{
	setFixedSize(1000, 700);
	setWindowTitle(tr("HostDetector"));

	QWidget* centerWidet = new QWidget;
	centerWidet->setFixedSize(1000, 700);

	{
		QVBoxLayout* mainLayout = new QVBoxLayout(centerWidet);
		mainLayout->setContentsMargins(40, 20, 40, 20);

		QHBoxLayout* layout = new QHBoxLayout;
		mainLayout->addLayout(layout);

		m_operateWidget = new OperateWidget;
		connect(m_operateWidget, &OperateWidget::startDetect, this, &MainWindow::onStartDetect);
		connect(m_operateWidget, &OperateWidget::stopDetect, this, &MainWindow::onStopDetect);
		layout->addWidget(m_operateWidget);

		m_hostStatusWidget = new HostStatusWidget;
		layout->addWidget(m_hostStatusWidget);
	}

	setCentralWidget(centerWidet);

	m_detectManager = new DetectManager(this);
	connect(m_detectManager, &DetectManager::detectResult, this, &MainWindow::processDetectResult);
	connect(m_detectManager, &DetectManager::allFinished, this, &MainWindow::onAllFinished);
}

MainWindow::~MainWindow()
{

}

void MainWindow::processDetectResult(QString ip, int value)
{ 
	m_hostStatusWidget->setHostResult(ip, value);

	QString str;
	if (value >= 0)
		str = tr("ip(%1): response %2 ms").arg(ip).arg(value);
	else
		str = tr("ip(%1): no response!").arg(ip);

	m_operateWidget->appendOutput(str);
}

void MainWindow::onStartDetect(QString ip)
{
	m_hostStatusWidget->resetAllItemStatus();
	m_operateWidget->clearOutput();
	m_detectManager->doDetect(ip);
	m_operateWidget->setStartButtonEnable(false);
	m_operateWidget->setStopButtonEnable(true);
}

void MainWindow::onStopDetect()
{
	m_operateWidget->appendOutput(tr("Cancel detect!"));

	m_detectManager->stopDetect();

	m_operateWidget->setStartButtonEnable(true);
}

void MainWindow::onAllFinished()
{
	m_operateWidget->setStartButtonEnable(true);
	m_operateWidget->appendOutput(tr("Detect done!"));
}
