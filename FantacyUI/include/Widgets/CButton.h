#ifndef __CBUTTON_H__
#define __CBUTTON_H__

#include "PlatformDef.h"
#include "CText.h"

enum class EButtonStatus
{
    Button_Normal,
    Button_Hot,
    Button_Pushed,
    Button_Disabled,
};

class CButton : public CText
{
public:
    CButton();
    ~CButton();

    void setNormalColor(const CColor& color);
    void setHotColor(const CColor& color);
    void setPushedColor(const CColor& color);
    void setDisabledColor(const CColor& color);

protected:
    virtual void onPaint(CPainter* painter);
private:
    CColor m_normalColor;
    CColor m_hotColor;
    CColor m_pushedColor;
    CColor m_disabledColor;
    EButtonStatus m_status;
};


#endif  //__CBUTTON_H__

