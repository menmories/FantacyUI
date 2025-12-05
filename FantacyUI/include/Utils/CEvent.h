#ifndef CEVENT_H
#define CEVENT_H

#include "PlatformDef.h"
#include "Painter/CGeometry.h"
#include "CInput.h"
class CEvent
{
public:
    enum EventType
    {
        EventType_None = 0,
        EventType_MouseMove,
        EventType_MouseDown,
        EventType_MouseUp,
        EventType_MouseWheel,
        EventType_KeyDown,
        EventType_KeyUp,
        EventType_Char,
        EventType_Resize,
    };

    CEvent();
    CEvent(int type, void* data);
    ~CEvent();

    FANTACY_INLINE void setType(int type)
    {
        m_type = type;
    }

    FANTACY_INLINE void setData(void* data)
    {
        m_data = data;
    }

    FANTACY_INLINE int type() const
    {
        return m_type;
    }

    FANTACY_INLINE void* data()
    {
        return m_data;
    }
private:
    int     m_type;
    void*   m_data;
};


class FANTACY_API CMouseEvent
{
public:
    CMouseEvent()
        : m_button(EMouseButton::MouseButton_None)
        , m_state(EMouseButton::MouseButton_None)
    {

    }

    CMouseEvent(EMouseButton button, EMouseButton state, const CPoint& globalPos, const CPoint& pos)
        : m_button(button)
        , m_state(state)
        , m_globalPos(globalPos)
        , m_pos(pos)
    {

    }

    ~CMouseEvent()
    {

    }

    FANTACY_INLINE void setButton(EMouseButton button)
    {
        m_button = button;
    }

    FANTACY_INLINE void setGlobalPos(const CPoint& pos)
    {
        m_globalPos = pos;
    }

    FANTACY_INLINE CPoint globalPos()const
    {
        return m_pos;
    }

    FANTACY_INLINE void setPos(const CPoint& pos)
    {
        m_pos = pos;
    }

    FANTACY_INLINE CPoint pos()const
    {
        return m_pos;
    }

    FANTACY_INLINE EMouseButton state()const
    {
        return m_state;
    }

    FANTACY_INLINE void setState(EMouseButton state)
    {
        m_state = state;
    }
private:
    EMouseButton m_button;
    EMouseButton m_state;
    CPoint m_globalPos;
    CPoint m_pos;
};

#endif // !
