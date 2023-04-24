#include "pch.h"
#include "Widget.h"
#include "Render/Canvas.h"
#include "TabPannel.h"

FTabPannel::FTabPannel()
	: mSelectedIndex(0)
{
}

FTabPannel::~FTabPannel()
{
}

FPannel* FTabPannel::AddPage()
{
	FPannel* Pannel = new FPannel();
	Pannel->SetRect(mRect);
	Pannel->SetBackgroundColor(BackgroundColor);
	mChilds.push_back(Pannel);
	return Pannel;
}

void FTabPannel::SelectPage(u32 InPageIndex)
{
	u32 childSize = (u32)mChilds.size();
	assert(InPageIndex < (childSize));
	mSelectedIndex = InPageIndex;
}

u32 FTabPannel::GetPageCount() const
{
	return (u32)mChilds.size();
}

void FTabPannel::OnPaint(FCanvas* Canvas)
{
	FBitmapCanvas BitmapCanvas;
	FRectU Currect = GetRect();
	Canvas->CreateBitmapCanvas(FSize(Currect.GetWidth(), Currect.GetHeight()), &BitmapCanvas);
	BitmapCanvas.RenderTarget->BeginDraw();
	//BitmapCanvas.Clear(BackgroundColor);
	//Paint childs
	FWidget* Widget = mChilds[mSelectedIndex];
	Widget->OnPaint(&BitmapCanvas);
	ID2D1Bitmap* bitmap = nullptr;
	((ID2D1BitmapRenderTarget*)BitmapCanvas.RenderTarget)->GetBitmap(&bitmap);
	if (bitmap)
	{
		Canvas->RenderTarget->DrawBitmap(bitmap,
			D2D1::RectF(Currect.Left, Currect.Top, Currect.Right, Currect.Bottom),
			1.0,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	}
	BitmapCanvas.RenderTarget->EndDraw();
}

void FTabPannel::OnResize(const FSize& InSize)
{
	for (auto iter = mChilds.begin(); iter != mChilds.end(); iter++)
	{
		(*iter)->SetSize(InSize);
	}
}
