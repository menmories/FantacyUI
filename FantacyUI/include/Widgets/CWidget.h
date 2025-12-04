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
	virtual void onMousePress(EMouseButon button);
	virtual void onMouseRelease(EMouseButon button);
    virtual void onMouseMove(const CPoint* pos);
	virtual void onMouseWheel(int direction) {}

	virtual void prePaint(CPainter* painter);
	virtual void preEvent(const CEvent& e);
protected:
private:
	void paintChild(CPainter* painter);
private:
	CRect m_rect;
	CWindow* m_window;
};



#endif // !CWIDGET_H
