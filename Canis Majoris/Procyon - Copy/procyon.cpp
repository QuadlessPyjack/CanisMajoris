#include "procyon.h"

Procyon::Procyon(QWidget *parent)
	: QMainWindow(parent), CMDebugPool("DBG_LOG_MEM")
{
	ui.setupUi(this);
	model = new QStringListModel(this);

	QStringList list;

	if (!CMDebugPool.attach())
	{
		list << "Failed to access shared memory or renderer not started";
		return;
	}

	QBuffer buffer;
	QDataStream in(&buffer);

	CMDebugPool.lock();
	buffer.setData((char*)CMDebugPool.constData(), CMDebugPool.size());
	buffer.open(QBuffer::ReadOnly);
	in >> list;
	CMDebugPool.unlock();
	CMDebugPool.detach();
	list << "test 1" << "test2" << "ceaun";

	model->setStringList(list);

	ui.listView->setModel(model);
}

Procyon::~Procyon()
{

}
