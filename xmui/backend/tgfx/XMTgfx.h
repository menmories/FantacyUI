#ifndef XMUI_TGFX_H
#define XMUI_TGFX_H

#ifdef XMUI_USE_TGFX_BACKEND


#include <tgfx/core/Point.h>
#include <tgfx/core/Rect.h>
#include <tgfx/gpu/opengl/wgl/WGLWindow.h>
#include <Core/XMPainter.h>


class XMTgfxPainter : public XMPainter
{
public:
	virtual void beginDraw() override;
	virtual void endDraw() override;
	virtual void release() override;
};

#endif

#endif	// XMUI_TGFX_H


