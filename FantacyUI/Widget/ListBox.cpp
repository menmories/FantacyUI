#include "pch.h"
#include "Render/Canvas.h"
#include "ListBox.h"

FListBoxItem::FListBoxItem()
{
}

FListBoxItem::~FListBoxItem()
{
}

FListBox::FListBox()
	: mItemHeight(20)
{
}

FListBox::~FListBox()
{
}

void FListBox::AddItem(FWidget* Item)
{
	FRectU rect;
	rect.Left = this->mRect.Left + mPadding.Left;
	u32 count = this->GetItemCount();
	rect.Top = (count * mItemHeight) + (count * mPadding.Top);
	rect.Bottom = rect.Top + mItemHeight;
	rect.Right = mRect.GetWidth() - (mPadding.Left + mPadding.Right);
	Item->SetRect(rect);
	mChilds.push_back(Item);
}

u64 FListBox::GetItemCount() const
{
	return mChilds.size();
}

void FListBox::OnPaint(FCanvas* Canvas)
{
}


