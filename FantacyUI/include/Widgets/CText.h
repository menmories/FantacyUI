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

	FANTACY_INLINE void setTextColor(const CColor& color)
	{
		m_textColor.setColor(color);
	}

	FANTACY_INLINE void setFont(const CFont& font)
	{
		m_font = font;
	}

	virtual void onPaint(CPainter* painter);
private:
	FaString m_text;
	CBrush m_textColor;
	CFont  m_font;
};



#endif // !__CTEXT_H__
