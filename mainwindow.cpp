#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QByteArray>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindowClass)
	, m_network(NULL)
{
    ui->setupUi(this);

	QImageScene *scene = new QImageScene(ui->graphicsView);
	ui->graphicsView->setScene(scene);

	m_statusInfo = new QLabel;
	this->statusBar()->addWidget(m_statusInfo);

	createMenu();

	// initialize
	HANDLE hThread = ::CreateThread(NULL, 0, network_init, (LPVOID)this, 0, NULL);
	::CloseHandle(hThread);
}
// need long time
DWORD MainWindow::network_init(LPVOID lpParam)
{
	MainWindow* pMainWindow = (MainWindow*)lpParam;

	// initialize network
	pMainWindow->m_network = new network_type();

	// show validation info
	pMainWindow->statusInfo().setText(pMainWindow->test_info());

	return 0;
}

MainWindow::~MainWindow()
{
    delete ui;
	if (m_network)
	{
		delete m_network;
		m_network = NULL;
	}
}
QString	MainWindow::test_info()
{
	QString info;
	QImage image;
	int digit_field, image_field;

	// load train samples to network
	QSqlQuery train_query(QObject::tr("SELECT * FROM %1").arg(TRAIN_SAMPLE_DB_NAME));
	digit_field = train_query.record().indexOf("digit");
	image_field = train_query.record().indexOf("image");

	network().clear();
	while (train_query.next())
	{
		int digit = train_query.value(digit_field).toInt(NULL);
		QByteArray data = train_query.value(image_field).toByteArray();

		if (digit >= 0 && digit < 10)
		{
			image.loadFromData(data, "bmp");
			network().add(digit, image);
		}
	}

	//! \note only for pca_mixed_policy_with_bayes_classifier
#ifdef USING_BAYES_CLASSIFIER
	if (network().is_prepared())
	{
		network().policy().encode_samples(network().samples());
		network().policy().init_classifier(network().samples());
	}
#endif

	if (network().is_prepared()) info += "train:"  + network().info();

	// load test samples to network
	QSqlQuery test_query(QObject::tr("SELECT * FROM %1").arg(TEST_SAMPLE_DB_NAME));
	digit_field = test_query.record().indexOf("digit");
	image_field = test_query.record().indexOf("image");

	network().clear();
	while (test_query.next())
	{
		int digit = test_query.value(digit_field).toInt(NULL);
		QByteArray data = test_query.value(image_field).toByteArray();

		if (digit >= 0 && digit < 10)
		{
			image.loadFromData(data, "bmp");
			network().add(digit, image);
		}
	}
#ifdef USING_BAYES_CLASSIFIER
	if (network().is_prepared()) network().policy().encode_samples(network().samples());
#endif
	if (network().is_prepared()) info += " test:"  + network().info();

	// show validation info
	return info;
}
void MainWindow::createMenu()
{
	// file menu
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

	// file menu => open
	QAction* openAction = fileMenu->addAction(QIcon(":/new/filemenu/open"), tr("&Open"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

	// file menu => add
	QAction* addAction = fileMenu->addAction(QIcon(":/new/filemenu/add"), tr("&Add"));
	connect(addAction, SIGNAL(triggered()), this, SLOT(add()));

	// file menu => remove
	QAction* removeAction = fileMenu->addAction(QIcon(":/new/filemenu/remove"), tr("&Remove"));
	connect(removeAction, SIGNAL(triggered()), this, SLOT(remove()));

	// file menu => separator
	fileMenu->addSeparator();

	// file menu => exit
	QAction* exitAction = fileMenu->addAction(QIcon(":/new/filemenu/exit"), tr("&Exit"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

	// image menu
	QMenu* imageMenu = menuBar()->addMenu(tr("&Image"));

	// image menu => gray menu
	QMenu* grayMenu = imageMenu->addMenu(tr("gray"));
	QAction* gy_generalAction = grayMenu->addAction(tr("general"));
	QAction* gy_stretchAction = grayMenu->addAction(tr("stretch"));
	QAction* gy_histogramAction = grayMenu->addAction(tr("histogram"));
	QAction* gy_part_histogramAction = grayMenu->addAction(tr("partial histogram"));
	connect(gy_generalAction, SIGNAL(triggered()), scene(), SLOT(gy_general()));
	connect(gy_stretchAction, SIGNAL(triggered()), scene(), SLOT(gy_stretch()));
	connect(gy_histogramAction, SIGNAL(triggered()), scene(), SLOT(gy_histogram()));
	connect(gy_part_histogramAction, SIGNAL(triggered()), scene(), SLOT(gy_part_histogram()));

	QMenu* smoothMenu = imageMenu->addMenu(tr("smooth"));
	QAction* oh_mean_smoothAction = smoothMenu->addAction(tr("mean"));
	connect(oh_mean_smoothAction, SIGNAL(triggered()), scene(), SLOT(oh_mean_smooth()));

	// image menu => threshold menu
	QMenu* thresholdMenu = imageMenu->addMenu(tr("threshold"));
	QMenu* global_thresholdMenu = thresholdMenu->addMenu(tr("global"));
	QMenu* partial_thresholdMenu = thresholdMenu->addMenu(tr("partial"));
	QAction* th_global_basic_thresholdAction = global_thresholdMenu->addAction(tr("basic"));
	QAction* th_global_otsu_thresholdAction = global_thresholdMenu->addAction(tr("otsu"));
	QAction* th_partial_basic_thresholdAction = partial_thresholdMenu->addAction(tr("basic"));
	QAction* th_partial_otsu_thresholdAction = partial_thresholdMenu->addAction(tr("otsu"));
	connect(th_global_basic_thresholdAction, SIGNAL(triggered()), scene(), SLOT(th_global_basic_threshold()));
	connect(th_global_otsu_thresholdAction, SIGNAL(triggered()), scene(), SLOT(th_global_otsu_threshold()));
	connect(th_partial_basic_thresholdAction, SIGNAL(triggered()), scene(), SLOT(th_partial_basic_threshold()));
	connect(th_partial_otsu_thresholdAction, SIGNAL(triggered()), scene(), SLOT(th_partial_otsu_threshold()));

	// image menu => denoising menu
	QMenu* denoisingMenu = imageMenu->addMenu(tr("denoising"));
	QAction* dn_medianAction = denoisingMenu->addAction(tr("median"));
	QAction* dn_discreteAction = denoisingMenu->addAction(tr("discrete"));
	connect(dn_medianAction, SIGNAL(triggered()), scene(), SLOT(dn_median_denoising()));
	connect(dn_discreteAction, SIGNAL(triggered()), scene(), SLOT(dn_discrete_denoising()));

	// image menu => split menu
	QMenu* splitMenu = imageMenu->addMenu(tr("split"));
	QAction* cs_kmeanAction = splitMenu->addAction(tr("k-mean"));
	QAction* cs_fcmAction = splitMenu->addAction(tr("fuzzy c-mean"));
	QAction* cs_labelingAction = splitMenu->addAction(tr("labeling"));
	connect(cs_kmeanAction, SIGNAL(triggered()), scene(), SLOT(cs_kmean_split()));
	connect(cs_fcmAction, SIGNAL(triggered()), scene(), SLOT(cs_fcm_split()));
	connect(cs_labelingAction, SIGNAL(triggered()), scene(), SLOT(cs_labeling_split()));

	// image menu => edge detect
	QMenu* edgeMenu = imageMenu->addMenu(tr("edge"));
	QAction* sobelAction = edgeMenu->addAction(tr("sobel"));
	QAction* prewittAction = edgeMenu->addAction(tr("prewitt"));
	QAction* kirschAction = edgeMenu->addAction(tr("kirsch"));
	QAction* isotropicAction = edgeMenu->addAction(tr("isotropic"));
	QAction* marrAction = edgeMenu->addAction(tr("marr"));
	connect(sobelAction, SIGNAL(triggered()), scene(), SLOT(sobel()));
	connect(prewittAction, SIGNAL(triggered()), scene(), SLOT(prewitt()));
	connect(kirschAction, SIGNAL(triggered()), scene(), SLOT(kirsch()));
	connect(isotropicAction, SIGNAL(triggered()), scene(), SLOT(isotropic()));
	connect(marrAction, SIGNAL(triggered()), scene(), SLOT(marr()));

	// image menu => deskew
	QAction* deskewAction = imageMenu->addAction(tr("deskew"));
	connect(deskewAction, SIGNAL(triggered()), scene(), SLOT(deskew()));

	// image menu => thinning
	QAction* thinningAction = imageMenu->addAction(tr("thinning"));
	connect(thinningAction, SIGNAL(triggered()), scene(), SLOT(thinning()));

	// image menu => pre-process
	QAction* pp_preprocessAction = imageMenu->addAction(tr("pre-process"));
	connect(pp_preprocessAction, SIGNAL(triggered()), scene(), SLOT(pp_preprocess()));

	// network menu
	QMenu* networkMenu = menuBar()->addMenu(tr("&Network"));
	QAction* trainAction = networkMenu->addAction(tr("train"));
	connect(trainAction, SIGNAL(triggered()), this, SLOT(train()));

	// help menu
	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
	QAction* aboutAction = helpMenu->addAction(QIcon(":/new/main/main"), tr("&About"));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

	// file toolbar
	QToolBar* fileToolBar = addToolBar(tr("&File"));
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(addAction);
	fileToolBar->addAction(removeAction);
	fileToolBar->addSeparator();
	fileToolBar->addAction(aboutAction);
	fileToolBar->addAction(exitAction);
	fileToolBar->addSeparator();

	m_samples_type = new QComboBox(this);
	m_samples_type->insertItem(SAMPLES_TYPE_TRAIN, "train samples");
	m_samples_type->insertItem(SAMPLES_TYPE_TEST, "test samples");
	connect(m_samples_type, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSamplesTypeChanged(int)));
	fileToolBar->addWidget(m_samples_type);
}
// about
void MainWindow::about()
{
	QMessageBox abt;
	abt.setText(tr("HDR 1.0\nauthor: waruqi\nemail: waruqi@yahoo.cn"));
	abt.exec();
}
// exit
void MainWindow::exit()
{
	this->close();
}

// open file
void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Sample Image (*.bmp *.jpg *.jpeg *.png)"));
	if (!fileName.isEmpty()) scene()->LoadImage(fileName);
}
// add sample
void MainWindow::add()
{
	// gets analyzed sample images
	pimages_info_row_type const& pimages_info_row = scene()->pimages_info_row();
	if (pimages_info_row.is_empty())
	{
		QMessageBox::warning(this, "", tr("please analyze sample image first!"));
		return ;
	}

	// gets analyzed result
	QString result = ui->resultEdit->toPlainText();
	if (result.isEmpty())
	{
		QMessageBox::warning(this, "", tr("please input analyzed result first!"));
		return ;
	}

	// splits result
	result = result.trimmed();
	QStringList strs = result.split(QRegExp("\\s+"));
	int image_n = 0;
	for (int k = 0; k < (int)pimages_info_row.size(); ++k)
		image_n += pimages_info_row[k].size();
	if (strs.size() != image_n)
	{
		QMessageBox::warning(this, "", tr("the number of result is not matched with images!"));
		return ;
	}

	// select samples db type
	int index = m_samples_type->currentIndex();
	QString sampleTable(TRAIN_SAMPLE_DB_NAME);
	if (index == SAMPLES_TYPE_TRAIN) sampleTable = TRAIN_SAMPLE_DB_NAME;
	else if (index == SAMPLES_TYPE_TEST) sampleTable = TEST_SAMPLE_DB_NAME;

	// add samples to database
	image_n = 0;
	ui->treeView->sampleDB().transaction();
	for (int i = 0; i < (int)pimages_info_row.size(); ++i)
	{
		for (int j = 0; j < (int)pimages_info_row[i].size(); ++j)
		{
			if (strs[image_n] != "-")
			{
				bool ret = ui->treeView->addSample(sampleTable, strs[image_n].toInt(), ImageConvector::convect(pimages_info_row[i][j]->image));
				if (!ret)
				{
					QMessageBox::warning(this, "", tr("Failed to add sample!"));
					ui->treeView->sampleDB().rollback();
					return ;
				}
			}
			++image_n;
		}
	}
	ui->treeView->sampleDB().commit();

	// reload samples
	ui->treeView->loadSamples(sampleTable);
	QMessageBox::warning(this, "", tr("Add sample successfully!"));
}
// remove sample
void MainWindow::remove()
{
	// select samples db type
	int index = m_samples_type->currentIndex();
	QString sampleTable(TRAIN_SAMPLE_DB_NAME);
	if (index == SAMPLES_TYPE_TRAIN) sampleTable = TRAIN_SAMPLE_DB_NAME;
	else if (index == SAMPLES_TYPE_TEST) sampleTable = TEST_SAMPLE_DB_NAME;

	ui->treeView->removeSample(sampleTable);
}
// trains samples
void MainWindow::train()
{
	// start train thread
	HANDLE hThread = ::CreateThread(NULL, 0, network_train, (LPVOID)this, 0, NULL);
	::CloseHandle(hThread);
}

// need long time
DWORD MainWindow::network_train(LPVOID lpParam)
{
	QTime t;
	QString info;
	MainWindow* pMainWindow = (MainWindow*)lpParam;

	// load trained samples to network
	QSqlQuery query(QObject::tr("SELECT * FROM %1").arg(TRAIN_SAMPLE_DB_NAME));
	int digit_field = query.record().indexOf("digit");
	int image_field = query.record().indexOf("image");

	QImage image;
	pMainWindow->network().clear();
	while (query.next())
	{
		int digit = query.value(digit_field).toInt(NULL);
		QByteArray data = query.value(image_field).toByteArray();

		if (digit >= 0 && digit < 10)
		{
			image.loadFromData(data, "bmp");
			pMainWindow->network().add(digit, image);
		}
	}

	// start time
	t.start();
	pMainWindow->network().train();
	//info = pMainWindow->network().train();
	//pMainWindow->statusInfo().setText(info);
	// show image recognize time
	QMessageBox::warning(NULL, "", QObject::tr("network train time:%1 ms").arg(t.elapsed()));

	// show validation info
	pMainWindow->statusInfo().setText(pMainWindow->test_info());

	return 0;
}

void MainWindow::recognize()
{
	// start time
	QTime t;
	t.start();

	// analyze image
	if (!scene()->analyze())
		return ;

	if (!network().is_prepared())
	{
		QMessageBox::warning(this, "", tr("network hasn't prepared!"));
		return ;
	}

	// gets analyzed sample images
	pimages_info_row_type const& pimages_info_row = scene()->pimages_info_row();
	if (pimages_info_row.is_empty())
	{
		QMessageBox::warning(this, "", tr("please analyze sample image first!"));
		return ;
	}

	// recognize and show result
	QString result;
	for (int i = 0; i < (int)pimages_info_row.size(); ++i)
	{
		for (int j = 0; j < (int)pimages_info_row[i].size(); ++j)
		{
			int digit = network().recognize(ImageConvector::convect(pimages_info_row[i][j]->image));
			result += (digit >= 0 && digit < 10)? tr("%1 ").arg(digit) : "- ";
			if (j == (int)pimages_info_row[i].size() - 1) result += "\r\n";
		}
	}

	ui->resultEdit->setDocument(new QTextDocument(result, this));

	// show image recognize time
	QMessageBox::warning(NULL, "", QObject::tr("image recognize time:%1 ms").arg(t.elapsed()));
}
void MainWindow::OnSamplesTypeChanged(int index)
{
	if (index == SAMPLES_TYPE_TRAIN) ui->treeView->loadSamples(TRAIN_SAMPLE_DB_NAME);
	else if (index == SAMPLES_TYPE_TEST) ui->treeView->loadSamples(TEST_SAMPLE_DB_NAME);
}

