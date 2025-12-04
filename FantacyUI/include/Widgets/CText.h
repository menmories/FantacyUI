#ifndef __CTEXT_H__
#define __CTEXT_H__


#include "PlatformDef.h"

#include "Widgets/CWidget.h"

class FANTACY_API CText : public CWidget
{
public:
	CText(CWidget* parent = nullptr);
	CText(const FaString& text, CWidget* parent = nullptr);
	~CText();

	FANTACY_INLINE FaString text() const
	{
		return m_text;
	}

	FANTACY_INLINE void setText(const FaString& text)
	{
		m_text = text;
	}

	FANTACY_INLINE void setTextColor(u32 color)
	{
		m_textColor = color;
	}

	virtual void onPaint(CPainter* painter);
private:
	FaString m_text;
	CBrush m_textColor;
};



#endif // !__CTEXT_H__
