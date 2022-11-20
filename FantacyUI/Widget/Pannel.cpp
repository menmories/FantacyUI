#include "pch.h"
#include "Widget.h"
#include "Render/Canvas.h"
#include "Pannel.h"

FPannel::FPannel()
{
}

void FPannel::AddChild(FWidget* Widget)
{
	Widget->SetParent(this);
	mChilds.push_back(Widget);
}

void FPannel::SetBackgroundColor(const FColor& InColor)
{
	this->BackgroundColor = InColor;
}

FColor FPannel::GetBackgroundColor() const
{
	return this->BackgroundColor;
}

void FPannel::OnPaint(FCanvas* Canvas)
{
	FBitmapCanvas BitmapCanvas;
	FRectU Currect = GetRect();
	Canvas->CreateBitmapCanvas(FSize(Currect.GetWidth(), Currect.GetHeight()), &BitmapCanvas);
	BitmapCanvas.RenderTarget->BeginDraw();
	BitmapCanvas.Clear(BackgroundColor);
	for (auto iter = mChilds.begin(); iter != mChilds.end(); iter++)
	{
		(*iter)->OnPaint(&BitmapCanvas);
	}
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

FWidget* FPannel::FindPointInWidget(const FPoint& InPoint)
{
	if (!FWidget::FindPointInWidget(InPoint))
	{
		return nullptr;
	}
	FPoint NewPoint;
	ConvertMousePoint(InPoint, NewPoint);
	for (auto iter = mChilds.rbegin(); iter != mChilds.rend(); iter++)
	{
		if ((*iter)->FindPointInWidget(NewPoint))
		{
			return *iter;
		}
	}
	return this;
}


