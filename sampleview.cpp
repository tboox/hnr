#include "sampleview.h"
#include <QTimer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QBuffer>
#include <QByteArray>
#include <QUuid>
#include <QModelIndexList>

SampleView::SampleView(QWidget * parent)
		: QTreeView(parent)
{
	initView();
	if (openSampleDB(SAMPLES_DB_PATH)) loadSamples(TRAIN_SAMPLE_DB_NAME);
	else QMessageBox::warning(NULL, "", "cannot open sample database!");
	//QTimer::singleShot(0, this, SLOT(loadSampleDB()));
}
SampleView::~SampleView()
{
	sampleDB().close();
}
void SampleView::initView()
{
	QStandardItemModel* model= new QStandardItemModel();
	this->setModel(model);


	rootList().append(new QStandardItem(QIcon(":/new/others/digital"), "0"));
	rootList().append(new QStandardItem(QIcon(":/new/others/digital"), "1"));
	rootList().append(new QStandardItem(QIcon(":/new/others/digital"), "2"));
	rootList().append(new QStandardItem(QIcon(":/new/others/digital"), "3"));
	rootList().append(new QStandardItem(QIcon(":/new/others/digital"), "4"));
	rootList().append(new QStandardItem(QIcon(":/new/others/digital"), "5"));
	rootList().append(new QStandardItem(QIcon(":/new/others/digital"), "6"));
	rootList().append(new QStandardItem(QIcon(":/new/others/digital"), "7"));
	rootList().append(new QStandardItem(QIcon(":/new/others/digital"), "8"));
	rootList().append(new QStandardItem(QIcon(":/new/others/digital"), "9"));

	QStandardItem *rootItem = model->invisibleRootItem();
	rootItem->appendRows(rootList());

	//QImage image(IMAGE_W, IMAGE_H, QImage::Format_RGB32);
	//rootList()[0]->appendRow(new QStandardItem(QIcon(QPixmap().fromImage(image)), ""));
	//rootList()[0]->appendRow(new QStandardItem(QIcon(QPixmap().fromImage(image)), ""));
	//rootList()[0]->appendRow(new QStandardItem(QIcon(QPixmap().fromImage(image)), ""));
	//rootList()[0]->appendRow(new QStandardItem(QIcon(QPixmap().fromImage(image)), ""));
}
bool SampleView::openSampleDB(QString const& filename)
{
	QString dbName = tr("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=%1").arg(filename);
	sampleDB(QSqlDatabase::addDatabase("QODBC"));
	sampleDB().setDatabaseName(dbName);
	return sampleDB().open();
}
bool SampleView::loadSamples(QString const& table)
{
	QSqlQuery query(QObject::tr("SELECT * FROM %1").arg(table));
	int id_field = query.record().indexOf("id");
	int digit_field = query.record().indexOf("digit");
	int image_field = query.record().indexOf("image");

	// clear
	for (int i = 0; i < 10; ++i)
		rootList()[i]->removeRows(0, rootList()[i]->rowCount());

	// insert items
	QImage image;
	while (query.next())
	{
		QString id_str = query.value(id_field).toString();
		int digit = query.value(digit_field).toInt(NULL);
		QByteArray data = query.value(image_field).toByteArray();

		if (digit >= 0 && digit < 10)
		{
			image.loadFromData(data, "bmp");
			QStandardItem* item = new QStandardItem(QIcon(QPixmap().fromImage(image)), "");
			item->setData(id_str, Qt::UserRole + 1);
			rootList()[digit]->appendRow(item);
		}
	}
	return true;
}
bool SampleView::addSample(QString const& table, int digit, QImage const& image)
{
	if (digit < 0 || digit > 9) return false;

	// QImage => QBuffer => QByteArray
	QByteArray data;
	QBuffer buffer(&data);
	image.save(&buffer, "bmp");

	QSqlQuery query;
	query.prepare(QObject::tr("INSERT INTO %1(id, digit, image) "
					"VALUES(?, ?, ?)").arg(table));

	query.addBindValue(QUuid::createUuid().toString());
	query.addBindValue(digit);
	query.addBindValue(data);

	/*query.prepare(QObject::tr("INSERT INTO %1(id, digit, image) "
					"VALUES(?, ?, ?)").arg(SAMPLE_DB_NAME));

	query.bindValue(":id", QUuid::createUuid().toString());
	query.bindValue(":digit", digit);
	query.bindValue(":image", data);*/

	return query.exec();
}
void SampleView::removeSample(QString const& table)
{
	QModelIndexList list = this->selectedIndexes();
	for (int i = 0; i < list.size(); ++i)
	{
		// gets uuid
		QString id_str = list[i].data(Qt::UserRole + 1).toString();
		if (!id_str.isEmpty())
		{
			// delete from database
			QSqlQuery query;
			query.prepare(QObject::tr("DELETE FROM %1 "
							"WHERE id = ?").arg(table));

			query.addBindValue(id_str);
			if (query.exec())
			{
				// remove item
				((QStandardItemModel*)(this->model()))->itemFromIndex(list[i].parent())->removeRow(list[i].row());
			}
		}
	}
}
