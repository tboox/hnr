#ifndef QIMAGE_PAINTER_H
#define QIMAGE_PAINTER_H

#include <QtGui/QImage>
#include "prefix.h"

class qimage_painter
	: public painter_base<qimage_painter, image_type>
{
	/// \name Types
	/// @{
	public:
		typedef painter_base<qimage_painter, image_type>	base_type;
		typedef qimage_painter								class_type;
		typedef QImage										qimage_type;
		typedef base_type::bool_type						bool_type;
		typedef base_type::color_type						color_type;
		typedef color_type::rgba_type						rgba_type;
		typedef base_type::int_type							int_type;
		typedef base_type::rect_type						rect_type;
	/// @}

	/// \name Members
	/// @{
	private:
		qimage_type&										m_qimage;
	/// @}

	/// \name Constructors
	/// @{
	public:
		qimage_painter(qimage_type& qimage)
			: base_type(rect_type(0, 0, qimage.width(), qimage.height()))
			, m_qimage(qimage)
		{}
	/// @}

	/// \name Attributes
	/// @{
	public:
		qimage_type&			qimage()			{ return m_qimage;									}
		qimage_type const&		qimage()	const	{ return static_cast<qimage_type const&>(m_qimage);	}
	/// @}

	/// \name Implementions
	/// @{
	public:
		void		do_pixel(int_type x, int_type y, color_type const& c)
		{
			EXTL_ASSERT(x >= 0 && y >= 0);
			qimage().setPixel(x, y, qRgb(c.red(), c.green(), c.blue()));
		}

		color_type	do_pixel(int_type x, int_type y)
		{
			EXTL_ASSERT(x >= 0 && y >= 0);
			QRgb qrgb = qimage().pixel(x, y);
			return color_type(qRed(qrgb), qGreen(qrgb), qBlue(qrgb));
		}
	/// @}
};

#endif // QIMAGE_PAINTER_H
