#include "Widgets/CWidget.h"

CWidget::CWidget(CWidget* parent)
	: CObject(parent)
{
}

CWidget::~CWidget()
{
}

void CWidget::onPaint(CPainter* painter)
{
}

void CWidget::onResize(const CSize& size)
{

}

void CWidget::onMousePress()
{
}

void CWidget::onMouseRelease()
{
}

void CWidget::onMouseMove()
{
}

void CWidget::prePaint(CPainter* painter)
{
	onPaint(painter);
}

void CWidget::preEvent(const CEvent& e)
{
    switch (e.type())
    {
    case CEvent::EventType_MouseDown:
        onMousePress();
        break;
    case CEvent::EventType_MouseUp:
        onMouseRelease();
        break;
    case CEvent::EventType_MouseMove:
        onMouseMove();
        break;
    default:
        break;
    }
}
