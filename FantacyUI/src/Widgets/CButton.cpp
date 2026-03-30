#include "Widgets/CButton.h"


CButton::CButton()
	: m_normalColor(0xff0098FF)
	, m_hotColor(0xff00AAFF)
	, m_pushedColor(0xff0078FF)
	, m_disabledColor(0xffC9C9C9)
	, m_status(EButtonStatus::Button_Normal)
{
}

CButton::~CButton()
{
}

void CButton::setNormalColor(const CColor& color)
{
	m_normalColor = color;
	update();
}

void CButton::setHotColor(const CColor& color)
{
	m_hotColor = color;
	update();
}

void CButton::setPushedColor(const CColor& color)
{
	m_pushedColor = color;
	update();
}

void CButton::setDisabledColor(const CColor& color)
{
	m_disabledColor = color;
	update();
}

void CButton::onPaint(CPainter* painter)
{
	CBrush brush(m_normalColor);
	switch (m_status)
	{
	case EButtonStatus::Button_Normal:
	{
		brush.setColor(m_normalColor);
		break;
	}
	case EButtonStatus::Button_Hot:
	{
		brush.setColor(m_hotColor);
		break;
	}
	case EButtonStatus::Button_Pushed:
	{
		brush.setColor(m_pushedColor);
		break;
	}
	case EButtonStatus::Button_Disabled:
	{
		brush.setColor(m_disabledColor);
		break;
	}
	}
	painter->setBrush(brush);
	painter->fillRect(this->rect());
	CText::onPaint(painter);
}

