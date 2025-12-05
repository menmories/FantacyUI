#include "Widgets/CWidget.h"
#include <vector>
#include <cassert>
#include <unordered_set>
CWidget::CWidget(CWidget* parent)
	: CObject(parent)
{
    if (parent)
    {
        m_window = parent->m_window;
    }
    else
    {
        m_window = nullptr;
    }
}

CWidget::~CWidget()
{
    
}

void CWidget::setParent(CWidget* widget)
{
    CObject::setParent(widget);
}

void CWidget::addWidget(CWidget* widget)
{
    widget->setParent(this);
}

void CWidget::onPaint(CPainter* painter)
{
    CBrush brush(0xff2387ff);
    painter->setBrush(brush);
    painter->fillRect(this->rect());
}

void CWidget::onResize(const CSize& size)
{

}

void CWidget::onMousePress(CMouseEvent* e)
{
    printf("CWidget::onMousePress(CMouseEvent* e)");
}

void CWidget::onMouseRelease(CMouseEvent* e)
{
    printf("CWidget::onMouseRelease(CMouseEvent* e)");
}

void CWidget::onMouseMove(CMouseEvent* e)
{

}

void CWidget::prePaint(CPainter* painter)
{
	onPaint(painter);
    paintChild(painter);
}

void CWidget::preEvent(const CEvent& e)
{
    /*switch (e.type())
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
    }*/
}

void CWidget::preMousePress(CMouseEvent* e)
{
    CWidget* widget = findChildByPos(e->pos());
    widget->onMousePress(e);
}

void CWidget::preMouseRelease(CMouseEvent* e)
{
    CWidget* widget = findChildByPos(e->pos());
    widget->onMousePress(e);
}

CWidget* CWidget::findChildByPos(const CPoint& pos)
{
    std::unordered_set<CObject*>* childs = (std::unordered_set<CObject*>*)children();
    for (auto iter = childs->begin(); iter != childs->end(); iter++)
    {
        CWidget* widget = (CWidget*)*iter;
        if (widget->rect().ptInRect(pos))
        {
            return widget->findChildByPos(pos);
        }
    }
    return this;
}

void CWidget::paintChild(CPainter* painter)
{
    std::unordered_set<CObject*>* childs = (std::unordered_set<CObject*>*)children();
    for (auto iter = childs->begin(); iter != childs->end(); iter++)
    {
        CWidget* widget = (CWidget*)*iter;
        widget->prePaint(painter);
    }
}
