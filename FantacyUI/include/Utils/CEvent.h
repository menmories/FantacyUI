#ifndef CEVENT_H
#define CEVENT_H

#include "PlatformDef.h"
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

#endif // !
