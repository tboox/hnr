#ifndef QIMAGESCENE_H
#define QIMAGESCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QPainter>
#include <QPolygonF>
#include <QTime>

#include "prefix.h"
#include "imageconvector.h"
#include "qimage_painter.h"
//#include "sample_helper.h"

#include "sh_pp.h"

class QImageScene : public QGraphicsScene
{
	Q_OBJECT
public:
	QImageScene( QObject * parent = 0 );

public:
	bool					analyze();
	void					LoadImage(QString const& filename);

public:
	pimages_info_row_type const&	pimages_info_row() const	{ return m_pimages_info_row;	}
	pimages_info_row_type&			pimages_info_row()		{ return m_pimages_info_row;	}

protected:
	void drawForeground(QPainter *painter, const QRectF &rect);
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
	void update_image();

public:
	QImage&				showedImage()			{ EXTL_ASSERT(NULL != m_showedImage); return *m_showedImage;	}
	QImage const&		showedImage() const		{ EXTL_ASSERT(NULL != m_showedImage); return *m_showedImage;	}

	image_type&			handledImage()							{ return m_handledImage;	}
	image_type const&	handledImage() const					{ return m_handledImage;	}
	void				handledImage(image_type const& image)	{ m_handledImage = image;	}

	void				showImgs(scoped_buffer<image_type> const& imgs);

private slots:
	// make gray
	void				gy_general();
	void				gy_stretch();
	void				gy_histogram();
	void				gy_part_histogram();

	// smooth
	void				oh_mean_smooth();

	// threshold
	void				th_global_basic_threshold();
	void				th_global_otsu_threshold();
	void				th_partial_basic_threshold();
	void				th_partial_otsu_threshold();

	// denoising
	void				dn_median_denoising();
	void				dn_discrete_denoising();

	// split
	void				cs_kmean_split();
	void				cs_fcm_split();
	void				cs_labeling_split();

	// edge detect
	void				sobel();
	void				prewitt();
	void				kirsch();
	void				isotropic();
	void				marr();

	// deskew
	void				deskew();

	// thinning
	void				thinning();

	// pre-process
	void				pp_preprocess();

private:
	QImage*					m_showedImage;
	image_type				m_handledImage;
	pimages_info_row_type	m_pimages_info_row;
	bool					m_is_pressed;
	QPolygonF				m_ploygon;
	QTime					m_release_time;
	bool					m_is_online;

};

#endif // QIMAGESCENE_H
