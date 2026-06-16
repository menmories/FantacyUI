#ifndef XM_DIRECT2D_H
#define XM_DIRECT2D_H

#ifdef XMUI_USE_DIRECT2D_BACKEND


#include <Core/XMPainter.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include "Core/XMFont.h"
#include "Window/XMWindow.h"

bool InitDirect2D();
void DestroyDirect2D();
IDWriteFactory* GetDirectWriteFactory();
ID2D1Factory* GetDirectFactory();


class XMDirect2D : public XMPainter
{
public:
    XMDirect2D(XMWindow* owner);
    virtual ~XMDirect2D();

    void resize(int width, int height) override;

    virtual void beginDraw() override;
    virtual void endDraw() override;
    virtual void release() override;
    virtual void drawImage(const XMImage& image, int x, int y, int width, int height, float opcity = 1.0f) override;

    virtual void fillRect(const XMRect& rect, const XMBrush& brush) override;
    virtual void drawRect(const XMRect& rect, const XMBrush& brush, const XMPen& pen) override;

    virtual void drawText(const XMString& text, const XMRect& rect, const XMBrush& brush, const XMFont& font) override;

    virtual void* renderData() override
    {
        return m_renderTarget;
    }
private:
    XMWindow* m_window;
    ID2D1HwndRenderTarget* m_renderTarget;
    ID2D1SolidColorBrush* m_pBrush;
};


#endif


#endif  // XM_DIRECT2D_H


