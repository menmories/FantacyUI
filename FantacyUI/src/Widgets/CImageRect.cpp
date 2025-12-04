#include "Widgets/CImageRect.h"

CImageRect::CImageRect(CWidget* parent)
	: CWidget(parent)
{
}

CImageRect::~CImageRect()
{
}

void CImageRect::setImage(const char* image)
{
	m_image.destroy();
	m_image.loadFile(image);
}

void CImageRect::onPaint(CPainter* painter)
{
	painter->drawPixmap(m_image, rect());
}
