#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include <qobject.h>
#include <qmetatype.h>
#include <qstring.h>
#include <qmetaobject.h>

#include <Logger\ProcyonConstants.h>

class DebugLog : public QObject
{
	Q_OBJECT

		Q_PROPERTY(READ text NOTIFY textChanged)

public:
	DebugLog(QObject *parent = 0);
	virtual ~DebugLog();

	//Q_INVOKABLE void reset();

	QString text();
	void setText(QString text) {
		QString formattedClearSignal = QString(SHARED_MEMORY_CLEAR);
		QString nullString = '\0';
		if (!m_debugText.compare(formattedClearSignal))
			emit textChanged(m_debugText);
		else
			emit textChanged(nullString);
		
	}

signals:
	void textChanged(QString text);

private:
	QString m_debugText;
};

#endif
