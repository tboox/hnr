#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// note: include it firstly
#include "network.h"

#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QToolBar>
#include <QtGui/QTextEdit>
#include <QtGui/QGraphicsView>
#include <QtGui/QMenu>
#include <QtGui/QLabel>
#include <QComboBox>
#include "qimagescene.h"
#include "ui_mainwindow.h"

#define SAMPLES_TYPE_TRAIN		(0)
#define SAMPLES_TYPE_TEST		(1)

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

#ifdef USING_PCA
#	ifdef USING_BAYES_CLASSIFIER
	typedef Network<pca_mixed_policy_with_bayes_classifier<ada_boosting_policy> >	network_type;
#	else
	typedef Network<pca_mixed_policy<ada_boosting_policy> >	network_type;
#	endif
#else
	typedef Network<bp_policy>							network_type;
	//typedef Network<wga_policy>							network_type;
	//typedef Network<ada_boosting_policy>					network_type;
	//typedef Network<bagging_policy>						network_type;
	//typedef Network<wga_ada_boosting_policy>				network_type;
#endif

private:
	Ui::MainWindowClass						*ui;
	network_type*							m_network;
	QLabel*									m_statusInfo;
	QComboBox*								m_samples_type;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
	network_type&		network()		{ return *m_network;	}
	network_type const&	network() const	{ return *m_network;	}

	QLabel&				statusInfo()		{ return *m_statusInfo;	}
	QLabel const&		statusInfo() const	{ return *m_statusInfo;	}

	QImageScene*		scene()				{ return static_cast<QImageScene*>(ui->graphicsView->scene());			}
	QImageScene const*	scene() const		{ return static_cast<QImageScene const*>(ui->graphicsView->scene());	}

private:
	void		createMenu();
	QString		test_info();

private slots:
	void open();
	void about();
	void exit();
	void add();
	void remove();
	void train();
	void recognize();

private slots:
	void OnSamplesTypeChanged(int index);

private:
	static DWORD WINAPI network_init(LPVOID lpParam);
	static DWORD WINAPI network_train(LPVOID lpParam);
};

#endif // MAINWINDOW_H
