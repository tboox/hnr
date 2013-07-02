#include "qimagescene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

QImageScene::QImageScene(QObject * parent)
		: QGraphicsScene(parent)
		, m_showedImage(new QImage())
		, m_pimages_info_row()
		, m_is_pressed(false)
		, m_release_time(QTime::currentTime())
{
	setSceneRect(0, 0, xtl_max(((QGraphicsView*)parent)->width() - 10, 0),  xtl_max(((QGraphicsView*)parent)->height() - 10, 0));
	//setSceneRect(0, 0, 480, 320);
	// initialize image
	showedImage().fill(qRgb(255, 255, 255));
}

void QImageScene::drawForeground(QPainter *painter, const QRectF &/*rect*/)
{
	setSceneRect(0, 0, xtl_max(((QGraphicsView*)parent())->width() - 10, 0),  xtl_max(((QGraphicsView*)parent())->height() - 10, 0));
	painter->drawImage(0, 0, showedImage());
}

// load image
void QImageScene::LoadImage(QString const& filename)
{
	// load image
	showedImage().load(filename);

	// update handledImage
	image_type tmp(showedImage().width(), showedImage().height());
	for (int x = 0; x < (int)tmp.width(); ++x)
	{
		for (int y = 0; y < (int)tmp.height(); ++y)
		{
			tmp.at(x, y).red(qRed(showedImage().pixel(x, y)));
			tmp.at(x, y).green(qGreen(showedImage().pixel(x, y)));
			tmp.at(x, y).blue(qBlue(showedImage().pixel(x, y)));
			tmp.at(x, y).alpha(qAlpha(showedImage().pixel(x, y)));
		}
	}
	handledImage(tmp);
	update_image();

	// off-line mode
	m_is_online = false;
}
void QImageScene::update_image()
{
	this->invalidate();
}
// analyze
bool QImageScene::analyze()
{
	if (handledImage().is_empty())
	{
		QMessageBox::warning(NULL, tr(""), tr("No Sample Image!"));
		return false;
	}

	// pre-proccess image
	handledImage(sh_pp_preprocess(handledImage(), m_is_online, &m_pimages_info_row));

	// show split image
	if (showedImage().width() != handledImage().width()
	|| showedImage().height() != handledImage().height())
	{
		showedImage() = showedImage().scaled(handledImage().width(), handledImage().height());
	}
	qimage_painter qpainter(showedImage());
	showedImage().fill(QColor(255, 255, 255).rgb());
	qpainter.draw_image(handledImage());
	update_image();

	return true;
}

void QImageScene::showImgs(scoped_buffer<image_type> const& imgs)
{
	int hm = 60, wm = 40;
	image_type tmp(10 * (wm + 10), 5 * (hm + 10));
	for (int py = 0; py < tmp.height(); ++py)
		for (int px = 0; px < tmp.width(); ++px)
			tmp.at(px, py).gray(200);

	for (int i = 0; i < (int)imgs.size(); ++i)
	{
		for (int py = 0; py < imgs[i].height(); ++py)
		{
			for (int px = 0; px < imgs[i].width(); ++px)
			{
				tmp.at((i % 10) * wm + px, (i / 10) * hm + py).is_black(imgs[i].at(px, py).is_black());
			}
		}
	}

	// update showedImage
	showedImage() = showedImage().scaled(tmp.width(), tmp.height());
	qimage_painter qpainter(showedImage());
	qpainter.draw_image(tmp);

	update_image();
}
void QImageScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton);
	if (!m_is_pressed)
	{
		m_ploygon << mouseEvent->scenePos();
		m_is_pressed = true;

		QImage img((int)width(), (int)height(), QImage::Format_RGB32);
		if (m_release_time.msecsTo(QTime::currentTime()) > 1000) img.fill(qRgb(255, 255, 255));
		else img = showedImage();
		QPainter painter(&img);
		painter.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter.drawPolyline(m_ploygon);
		showedImage() = img;
		update_image();
	}
}
void QImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton);

	if (m_is_pressed)
	{
		m_ploygon << mouseEvent->scenePos();

		QPainter painter(&showedImage());
		painter.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter.drawPolyline(m_ploygon);
		update_image();
	}
}
void QImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton);

	if (m_is_pressed)
	{
		m_ploygon << mouseEvent->scenePos();
		QPainter painter(&showedImage());
		painter.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter.drawPolyline(m_ploygon);
		update_image();

		m_ploygon.clear();
		handledImage(ImageConvector::convect(showedImage()));
		m_is_pressed = false;
		m_release_time = QTime::currentTime();

		// on-line mode
		m_is_online = true;
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * edge detect
 */
void QImageScene::sobel()
{
	sh_ed_sobel_4_edge_detect(handledImage(), 5);

	// update showedImage
	qimage_painter qpainter(showedImage());
	qpainter.draw_image(handledImage());

	update_image();
}

void QImageScene::prewitt()
{
	sh_ed_prewitt_edge_detect(handledImage(), 5);

	// update showedImage
	qimage_painter qpainter(showedImage());
	qpainter.draw_image(handledImage());

	update_image();
}
void QImageScene::kirsch()
{
	sh_ed_kirsch_edge_detect(handledImage(), 5);

	// update showedImage
	qimage_painter qpainter(showedImage());
	qpainter.draw_image(handledImage());

	update_image();
}
void QImageScene::isotropic()
{
	sh_ed_isotropic_sobel_edge_detect(handledImage(), 5);

	// update showedImage
	qimage_painter qpainter(showedImage());
	qpainter.draw_image(handledImage());

	update_image();
}
void QImageScene::marr()
{
	sh_ed_marr_edge_detect(handledImage(), 5);

	// update showedImage
	qimage_painter qpainter(showedImage());
	qpainter.draw_image(handledImage());

	update_image();
}

// deskew
void QImageScene::deskew()
{
	handledImage(sh_dk_horizontal_side_slip_deskew(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::thinning()
{
	handledImage(sh_tn_thinning(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
// make gray image
void QImageScene::gy_general()
{
	handledImage(sh_gy_general(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::gy_stretch()
{
	handledImage(sh_gy_stretch(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::gy_histogram()
{
	handledImage(sh_gy_histogram(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::gy_part_histogram()
{
	handledImage(sh_gy_part_histogram(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::oh_mean_smooth()
{
	handledImage(sh_oh_mean_smooth(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::th_global_basic_threshold()
{
	handledImage(sh_th_global_basic_threshold(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::th_global_otsu_threshold()
{
	handledImage(sh_th_global_otsu_threshold(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::th_partial_basic_threshold()
{
	handledImage(sh_th_partial_basic_threshold(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::th_partial_otsu_threshold()
{
	handledImage(sh_th_partial_otsu_threshold(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());
	update_image();
}
void QImageScene::cs_kmean_split()
{
	handledImage(sh_cs_kmean_splited_image(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::cs_fcm_split()
{
	handledImage(sh_cs_kmean_splited_image(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::cs_labeling_split()
{
	handledImage(sh_rl_labeling_split_on_color(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void  QImageScene::dn_median_denoising()
{
	handledImage(sh_dn_median_denoising(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void  QImageScene::dn_discrete_denoising()
{
	handledImage(sh_dn_discrete_denoising(handledImage()));
	showedImage() = ImageConvector::convect(handledImage());

	update_image();
}
void QImageScene::pp_preprocess()
{
	handledImage(sh_pp_preprocess(handledImage(), m_is_online));
	showedImage() = ImageConvector::convect(handledImage());
	update_image();
}
