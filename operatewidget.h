#ifndef HOSTDETECTOR_OPERATEWIDGET_H
#define HOSTDETECTOR_OPERATEWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QRegExpValidator>

class OperateWidget :public QWidget 
{
	Q_OBJECT;
public:
	OperateWidget(QWidget* parent = nullptr);
	~OperateWidget();

	void setStartButtonEnable(bool enable);
	void setStopButtonEnable(bool enable);

	void clearOutput();
	void appendOutput(QString);

signals:
	void startDetect(QString);
	void stopDetect();

private slots:
	void onStartDetect();
	void onStopDetect();

private:
	QLineEdit* m_networkSegmentEdit = nullptr;
	QPushButton* m_startButton = nullptr;
	QPushButton* m_stopButton = nullptr;
	QPlainTextEdit* m_outputEdit = nullptr;

};


#endif // HOSTDETECTOR_OPERATEWIDGET_H

