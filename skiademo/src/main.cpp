
#pragma warning(disable: 4244)

#include <stdio.h>
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLInterface.h"
#include "include/gpu/ganesh/GrDirectContext.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"

#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkStream.h"
#include "include/core/SkSurface.h"

void gl_example(int width, int height, void (*draw)(SkCanvas*), const char* path) {
	// You've already created your OpenGL context and bound it.
	sk_sp<const GrGLInterface> interface = nullptr;
	// Leaving interface as null makes Skia extract pointers to OpenGL functions for the current
	// context in a platform-specific way. Alternatively, you may create your own GrGLInterface
	// and initialize it however you like to attach to an alternate OpenGL implementation or
	// intercept Skia's OpenGL calls.
	sk_sp<const GrGLInterface> glInterface = GrGLMakeNativeInterface();
	sk_sp<GrDirectContext> context = GrDirectContexts::MakeGL(interface);

	//GrGLFramebufferInfo fbInfo;
	//fbInfo.fFBOID = 0; // Standard backbuffer
	//fbInfo.fFormat = GL_RGBA8; // Typical format

	//// Define the render target
	//GrBackendRenderTarget backendRT(width, height,
	//	0, // Sample count
	//	8, // Stencil bits
	//	fbInfo);

	//// Create the SkSurface
	//SkSurfaceProps props(0, kUnknown_SkPixelGeometry);
	//sk_sp<SkSurface> surface = SkSurfaces::WrapBackendRenderTarget(
	//	context.get(), backendRT, kBottomLeft_GrSurfaceOrigin,
	//	kRGBA_8888_SkColorType, nullptr, &props);

	//SkCanvas* canvas = surface->getCanvas();
}

int main(int argc, char** argv)
{
	gl_example(0, 0, nullptr, nullptr);
    return 0;
}

