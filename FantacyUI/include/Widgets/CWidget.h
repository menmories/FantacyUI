#ifndef CWIDGET_H
#define CWIDGET_H

#include "CObject.h"
#include "Painter/CPainter.h"
#include "Utils/CEvent.h"
#include "Utils/CInput.h"

class CPainter;
class FANTACY_API CWidget : public CObject
{
public:
	CWidget(CWidget* parent = nullptr);
	~CWidget();

	FANTACY_INLINE CRect rect() const
	{
		return m_rect;
	}

	FANTACY_INLINE void move(int x, int y)
	{
        m_rect.move(x, y);
	}

	FANTACY_INLINE void resize(int width, int height)
	{
		m_rect.resize(width, height);
	}

    FANTACY_INLINE void setRect(int x, int y, int width, int height)
    {
        m_rect.setRect(x, y, width, height);
    }

	FANTACY_INLINE void setWidth(int width)
	{
		m_rect.setWidth(width);
	}
	FANTACY_INLINE void setHeight(int height)
	{
		m_rect.setHeight(height);
	}

	FANTACY_INLINE void setOwner(CWindow* window)
	{
		m_window = window;
	}

	void setParent(CWidget* widget);
	virtual void addWidget(CWidget* widget);

	virtual void onPaint(CPainter* painter);
	virtual void onResize(const CSize& size);
	virtual void onMousePress(CMouseEvent* e);
	virtual void onMouseRelease(CMouseEvent* e);
    virtual void onMouseMove(CMouseEvent* e);
	virtual void onMouseWheel(int direction) {}


	//预处理
	virtual void prePaint(CPainter* painter);
	virtual void preEvent(const CEvent& e);
	void preMousePress(CMouseEvent* e);
	void preMouseRelease(CMouseEvent* e);

protected:
	virtual CWidget* findChildByPos(const CPoint& pos);
private:
	void paintChild(CPainter* painter);
private:
	CRect m_rect;
	CWindow* m_window;
};



#endif // !CWIDGET_H
