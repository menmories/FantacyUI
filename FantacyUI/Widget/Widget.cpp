#include "pch.h"
#include "Widget.h"
#include "Render/Canvas.h"

FWidget::FWidget()
	: mRect(0, 0, 128, 128)
	, mParent(nullptr)
{
}

FWidget* FWidget::GetParent()
{
	return mParent;
}

void FWidget::SetParent(FWidget* InParent)
{
	this->mParent = InParent;
}

void FWidget::SetRect(const FRectU& InRect)
{
	mRect = InRect;
}

FRectU FWidget::GetRect() const
{
	return mRect;
}

void FWidget::OnPaint(FCanvas* Canvas)
{
	//FBitmapCanvas BitmapCanvas;
	//Canvas->CreateBitmapCanvas(FSize(mRect.GetWidth(), mRect.GetHeight()), &BitmapCanvas);
	//
	//if (!mSolidColorBrush)
	//{
	//	Canvas->RenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.6f, 0.1f), &mSolidColorBrush);
	//	BitmapCanvas.RenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.0f, 0.1f), &mSolidColorBrush);
	//}
	//BitmapCanvas.RenderTarget->BeginDraw();
	//BitmapCanvas.RenderTarget->Clear(D2D1::ColorF(0.0f, 1.0f, 1.0f));
	//s32 width = BitmapCanvas.RenderTarget->GetPixelSize().width;
	//s32 height = BitmapCanvas.RenderTarget->GetPixelSize().height;
	//width = BitmapCanvas.RenderTarget->GetSize().width;
	//height = BitmapCanvas.RenderTarget->GetSize().height;
	///*BitmapCanvas.BitmapRenderTarget->FillRectangle(D2D1::RectF(0, 0, mRect.GetWidth(), mRect.GetHeight()),
	//	mSolidColorBrush);*/
	//BitmapCanvas.RenderTarget->FillRectangle(D2D1::RectF(0, 0, 20, 20),
	//	mSolidColorBrush);
	//BitmapCanvas.RenderTarget->FillRectangle(D2D1::RectF(mRect.GetWidth() / 2, 0, mRect.GetWidth(), mRect.GetHeight() / 2),
	//	mSolidColorBrush);

	//ID2D1Bitmap* bitmap = nullptr;
	//((ID2D1BitmapRenderTarget*)BitmapCanvas.RenderTarget)->GetBitmap(&bitmap);
	//if (bitmap)
	//{
	//	Canvas->RenderTarget->DrawBitmap(bitmap, 
	//		D2D1::RectF(mRect.Left, mRect.Top, mRect.Right, mRect.Bottom),
	//		1.0,
	//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	//}
	//BitmapCanvas.RenderTarget->EndDraw();
	//mSolidColorBrush->Release();
	//mSolidColorBrush = nullptr;
}

void FWidget::SetMouseEnter(bool InEnter)
{
	this->bMouseEnter = InEnter;
}

bool FWidget::GetMouseEnter() const
{
	return this->bMouseEnter;
}

void FWidget::SetFocus(bool InFocus)
{
	this->bFocus = InFocus;
}

bool FWidget::GetFocus() const
{
	return this->bFocus;
}

void FWidget::OnMouseButtonDown(u32 MouseButton)
{
}

void FWidget::OnMouseButtonUp(u32 MouseButton)
{
}

void FWidget::OnMouseEnter()
{
}

void FWidget::OnMouseLeave()
{
}

FWidget* FWidget::FindPointInWidget(const FPoint& InPoint)
{
	if (mRect.PtInRect(InPoint.X, InPoint.Y))
	{
		return this;
	}
	return nullptr;
}

bool FWidget::PtInRegion(const FPoint& InPoint)
{
	return mRect.PtInRect(InPoint.X, InPoint.Y);
}

void FWidget::ConvertMousePoint(const FPoint& MousePoint, FPoint& OutPoint)
{
	OutPoint.X = MousePoint.X - mRect.Left;
	OutPoint.Y = MousePoint.Y - mRect.Top;
}
