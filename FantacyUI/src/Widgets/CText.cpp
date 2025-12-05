#include "Widgets/CText.h"

CText::CText(CWidget* parent)
	: CWidget(parent)
{
}

CText::CText(const FaString& text, CWidget* parent)
	: CWidget(parent)
	, m_text(text)
{
}

CText::~CText()
{
}

void CText::onPaint(CPainter* painter)
{
	painter->setFont(m_font);
	painter->drawText(m_text, rect(), m_textColor);
}

