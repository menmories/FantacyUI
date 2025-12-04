#ifndef __CIMAGERECT_H__
#define __CIMAGERECT_H__

#include "PlatformDef.h"
#include "CWidget.h"


class FANTACY_API CImageRect : public CWidget
{
public:
	CImageRect(CWidget* parent = nullptr);
	~CImageRect();

	void setImage(const char* image);

	virtual void onPaint(CPainter* painter);
private:
	CPixmap m_image;
};





#endif // !__CIMAGERECT_H__
