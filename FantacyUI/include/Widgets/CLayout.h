#ifndef CLAYOUT_H
#define CLAYOUT_H

#include "CWidget.h"
class CLayout : public CWidget
{
public:
    CLayout(CWidget* parent = nullptr);
    ~CLayout();


protected:
    virtual void onPaint(CPainter* painter);
    
    virtual void prePaint(CPainter* painter);
};


#endif  // CLAYOUT_H
