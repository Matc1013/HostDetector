#include "operatewidget.h"
#include "colorbutton.h"
#include "globalsetting.h"
#include <QTimer>


OperateWidget::OperateWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	setMinimumWidth(200);
	QGroupBox* groupBox = new QGroupBox(this);

	QVBoxLayout* mainLayout = new QVBoxLayout(groupBox);
	mainLayout->setContentsMargins(20, 20, 20, 20);
	mainLayout->setSpacing(10);

	{
		QHBoxLayout* itemLayout = new QHBoxLayout;

		{
			QVBoxLayout* tipsLayout = new QVBoxLayout;

			QStringList tips;
			tips << tr("Net segment:") << tr("0 - 100 ms:") << tr("100 - 300 ms:") << tr("> 300 ms:");

			for (auto it: tips)
			{
				QLabel* tipLabel = new QLabel(it);
				tipLabel->setAlignment(Qt::AlignRight);
				tipsLayout->addWidget(tipLabel);
			}

			itemLayout->addLayout(tipsLayout);
		}

		{
			QVBoxLayout* editorsLayout = new QVBoxLayout;

			m_networkSegmentEdit = new QLineEdit;
			m_networkSegmentEdit->setAlignment(Qt::AlignCenter);
			m_networkSegmentEdit->setValidator(new QRegExpValidator(QRegExp("((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})(\\.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){2}")));
			m_networkSegmentEdit->setPlaceholderText("192.168.1");
			editorsLayout->addWidget(m_networkSegmentEdit);

			{
				QColor c = GlobalSetting::getInstance()->getColorByStatus(HostNetworkStatus::HNS_GOOD);
				ColorButton* colorButton = new ColorButton(c);
				connect(colorButton, &ColorButton::colorChanged, this, [](QColor _c) {
					GlobalSetting::getInstance()->setStatusColor(HostNetworkStatus::HNS_GOOD, _c);
					});
				editorsLayout->addWidget(colorButton);
			}

			{
				QColor c = GlobalSetting::getInstance()->getColorByStatus(HostNetworkStatus::HNS_FINE);
				ColorButton* colorButton = new ColorButton(c);
				connect(colorButton, &ColorButton::colorChanged, this, [](QColor _c) {
					GlobalSetting::getInstance()->setStatusColor(HostNetworkStatus::HNS_FINE, _c);
					});
				editorsLayout->addWidget(colorButton);
			}

			{
				QColor c = GlobalSetting::getInstance()->getColorByStatus(HostNetworkStatus::HNS_BAD);
				ColorButton* colorButton = new ColorButton(c);
				connect(colorButton, &ColorButton::colorChanged, this, [](QColor _c) {
					GlobalSetting::getInstance()->setStatusColor(HostNetworkStatus::HNS_BAD, _c);
					});
				editorsLayout->addWidget(colorButton);
			}

			itemLayout->addLayout(editorsLayout);
		}
		mainLayout->addLayout(itemLayout);
	}

	{
		QHBoxLayout* itemLayout = new QHBoxLayout;

		m_startButton = new QPushButton(tr("Start"));
		connect(m_startButton, &QPushButton::clicked, this, &OperateWidget::onStartDetect);
		m_startButton->setDefault(true);


		m_stopButton = new QPushButton(tr("Stop"));
		connect(m_stopButton, &QPushButton::clicked, this, &OperateWidget::onStopDetect);

		itemLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding));
		itemLayout->addWidget(m_startButton);
		itemLayout->addSpacing(20);
		itemLayout->addWidget(m_stopButton);
		itemLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding));

		mainLayout->addLayout(itemLayout);
	}

	mainLayout->addSpacing(20);

	{
		m_outputEdit = new QPlainTextEdit;
		m_outputEdit->setMinimumHeight(400);
		m_outputEdit->setReadOnly(true);

		mainLayout->addWidget(m_outputEdit);
	}

	QTimer::singleShot(0, this, [this] { m_startButton->setFocus(); });
}

OperateWidget::~OperateWidget()
{

}

void OperateWidget::setStartButtonEnable(bool enable)
{
	m_startButton->setEnabled(enable);
}

void OperateWidget::setStopButtonEnable(bool enable)
{
	m_stopButton->setEnabled(enable);
}

void OperateWidget::clearOutput()
{
	m_outputEdit->clear();
}

void OperateWidget::appendOutput(QString text)
{
	m_outputEdit->appendPlainText(text);
}

void OperateWidget::onStartDetect()
{
	QString text = m_networkSegmentEdit->text();
	if (text.split(".", Qt::SkipEmptyParts).size() == 3)
	{
		emit startDetect(text);
	}
	else
	{
		QMessageBox::information(nullptr, tr("Info"), tr("Please input valid network segment!"), QMessageBox::Ok);
		m_networkSegmentEdit->setFocus();
	}
}

void OperateWidget::onStopDetect()
{
	emit stopDetect();
}

