#ifndef HOSTDETECTOR_GLOBALSETTING_H
#define HOSTDETECTOR_GLOBALSETTING_H

#include <QColor>
#include <QtGlobal>
#include <QMap>

enum class HostNetworkStatus
{
	HNS_UNRELY,
	HNS_GOOD,
	HNS_FINE,
	HNS_BAD
};

class GlobalSetting
{
public:
	static GlobalSetting* getInstance()
	{
		static GlobalSetting instance;
		return &instance;
	}

	QColor getColorByStatus(HostNetworkStatus status)
	{
		return m_statusColorTable.value(status);
	}

	void setStatusColor(HostNetworkStatus status, QColor color)
	{
		m_statusColorTable[status] = color;
	}

protected:
	GlobalSetting() 
	{
		m_statusColorTable[HostNetworkStatus::HNS_UNRELY] = QColor("#696969");
		m_statusColorTable[HostNetworkStatus::HNS_GOOD] = QColor("#00FF00");
		m_statusColorTable[HostNetworkStatus::HNS_FINE] = QColor("#CAFF70");
		m_statusColorTable[HostNetworkStatus::HNS_BAD] = QColor("#FFFF00");
	};

	GlobalSetting(const GlobalSetting&) = delete;
	GlobalSetting& operator==(const GlobalSetting&) = delete;

private:
	QMap<HostNetworkStatus, QColor> m_statusColorTable;
};

#endif // HOSTDETECTOR_GLOBALSETTING_H
