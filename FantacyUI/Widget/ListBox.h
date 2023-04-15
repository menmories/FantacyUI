#ifndef __FANTACY_LISTBOX_H__
#define __FANTACY_LISTBOX_H__
#include "Types.h"
#include "Base/Geometry.h"
#include "Pannel.h"
#include "Button.h"
#include <vector>

class FANTACY_API FListBoxItem : public FPannel
{
public:
	FListBoxItem();
	~FListBoxItem();
};


class FANTACY_API FListBox : public FPannel
{
public:
	FListBox();
	~FListBox();

	virtual void AddItem(FWidget* Item);

	u64 GetItemCount()const;

	virtual void OnPaint(FCanvas* Canvas);
protected:
	u32		mItemHeight;
	FColor	mItemNormalColor;
	FColor	mItemHotColor;
	FColor	mItemSelectedColor;
	FMargin mMargin;
	FMargin mPadding;
};




#endif // !__FANTACY_LISTBOX_H__

