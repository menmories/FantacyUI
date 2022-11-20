#ifndef __FANTACY_CANVAS_H__
#define __FANTACY_CANVAS_H__


#include "Base/String.h"
#include "Base/Geometry.h"
#include "Base/Color.h"

class FANTACY_API FDirect2DContext
{
public:
	static FDirect2DContext* Get();

	

	s32 InitContext();

	void DestroyContext();

	ID2D1HwndRenderTarget* CreateRenderTarget(u64 WindowId);
private:
	FDirect2DContext();
	~FDirect2DContext();
public:
	ID2D1Factory* Direct2DFactory;
	IDWriteFactory* DWriteFactory;
	IWICImagingFactory* WicImagingFactory;
};

class FBitmapCanvas;
class FBitmap;
class FANTACY_API FCanvas
{
public:
	FCanvas();
	~FCanvas();
public:
	bool Init(u64 WindowId);

	void Clear(const FColor& Color);

	virtual void Resize(const FSize& InSize);

	virtual void BeginDraw();

	virtual void EndDraw();

	virtual bool CreateBitmapFromFileName(const FString& InFileName, FBitmap** bitmap);

	virtual void CreateBitmapCanvas(const FSize& InSize, FBitmapCanvas* bitmapCanvas);

	virtual ID2D1SolidColorBrush* CreateSolidColorBrush(const FColor& InColor);

	virtual void DrawBitmap(const FRectU& InRect, FBitmap* bitmap);
public:
	ID2D1HwndRenderTarget* RenderTarget;
};


class FANTACY_API FBitmapCanvas : public FCanvas
{
public:
	FBitmapCanvas();

	~FBitmapCanvas();

	ID2D1Bitmap* GetBitmap();
};

#endif // !__FANTACY_CANVAS_H__
