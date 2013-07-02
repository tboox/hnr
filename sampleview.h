#ifndef SAMPLEVIEW_H
#define SAMPLEVIEW_H

#include "prefix.h"
#include <QTreeView>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QList>
#include <QImage>
#include <QPixmap>

class SampleView : public QTreeView
{

public:
	SampleView(QWidget * parent = 0);
	~SampleView();

private:
	void	initView();

public:
	bool	openSampleDB(QString const& filename);
	bool	loadSamples(QString const& table);
	bool	addSample(QString const& table, int digit, QImage const& image);
	void	removeSample(QString const& table);

public:
	QSqlDatabase&		sampleDB()							{ return m_sampleDB;	}
	QSqlDatabase const& sampleDB() const					{ return m_sampleDB;	}
	void				sampleDB(QSqlDatabase const& db)	{ m_sampleDB = db;		}

	QList<QStandardItem *>&			rootList()			{ return m_rootList;	}
	QList<QStandardItem *> const&	rootList() const	{ return m_rootList;	}

private:
	QSqlDatabase			m_sampleDB;
	QList<QStandardItem *>	m_rootList;
};

#endif // SAMPLEVIEW_H
