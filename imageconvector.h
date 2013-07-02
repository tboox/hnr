#ifndef IMAGECONVECTOR_H
#define IMAGECONVECTOR_H

#include <QImage>

#include "prefix.h"

class ImageConvector
{
public:
    ImageConvector();

public:
	static image_type	convect(QImage const& qimage);
	static QImage		convect(image_type const& image);
};

#endif // IMAGECONVECTOR_H
