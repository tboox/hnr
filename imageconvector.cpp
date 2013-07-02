#include "imageconvector.h"

ImageConvector::ImageConvector()
{
}

image_type ImageConvector::convect(QImage const& qimage)
{
	image_type image(qimage.width(), qimage.height());

	for (int px = 0; px < qimage.width(); ++px)
	{
		for (int py = 0; py < qimage.height(); ++py)
		{
			QRgb qrgb = qimage.pixel(px, py);
			image.at(px, py).red(qRed(qrgb));
			image.at(px, py).green(qGreen(qrgb));
			image.at(px, py).blue(qBlue(qrgb));
		}
	}

	return image;
}
QImage ImageConvector::convect(image_type const& image)
{
	QImage qimage(image.width(), image.height(), QImage::Format_RGB32);

	for (int px = 0; px < image.width(); ++px)
	{
		for (int py = 0; py < image.height(); ++py)
		{
			qimage.setPixel(px, py, qRgb(image.at(px, py).red(), image.at(px, py).green(), image.at(px, py).blue()));
		}
	}

	return qimage;
}
