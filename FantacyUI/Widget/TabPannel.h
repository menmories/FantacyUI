#ifndef __FANTACY_TABPANNEL_H__
#define __FANTACY_TABPANNEL_H__
#include "Types.h"
#include "Base/Geometry.h"
#include "Pannel.h"
#include <vector>
class FANTACY_API FTabPannel : public FPannel
{
public:
	FTabPannel();
	~FTabPannel();

	virtual FPannel* AddPage();

	virtual void SelectPage(u32 InPageIndex);

	u32 GetPageCount()const;

	virtual void OnPaint(FCanvas* Canvas);

	virtual void OnResize(const FSize& InSize);

protected:
	u32 mSelectedIndex;
};




#endif // !__FANTACY_TABPANNEL_H__

