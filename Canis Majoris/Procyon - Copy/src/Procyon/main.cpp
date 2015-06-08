#include <QGuiApplication>
#include <qqmlapplicationengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <qvariant.h>
#include <qdebug.h>

#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <Logger/DebugLog.h>

int main(int argc, char *argv[])
{
	using namespace boost::interprocess;
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	engine.load(QUrl(QStringLiteral("qrc:/Procyon_Toolbox.qml")));

	windows_shared_memory shm(open_only, "DBG_LOG_MEM", read_only);
	mapped_region region(shm, read_only);

	char *myChar = new char[100];
	memcpy(myChar, region.get_address(), 100);

	DebugLog *dbgLogger = new DebugLog(engine.rootObjects().value(0));

	//qmlRegisterType<DebugLog>("debugUtils", 1, 0, "DebugLog");
	qRegisterMetaType<DebugLog*>("DebugLog");
	QString temp = QString(myChar);
	temp.insert(0, "[INFO] ");
	int index = 0;
	int test = temp.length();
	int test2 = temp.count();
	int test3 = temp.size();

	for (int i = 1; i < temp.length(); ++i)
	{
		if (temp[index] == '0') break;
		++index;
	}
	temp.resize(index);

	dbgLogger->setText(temp);
	engine.rootContext()->setContextProperty("dbgLog", QVariant::fromValue(dbgLogger));

	qDebug() << "$ERESTES\n";

	return app.exec();
}
