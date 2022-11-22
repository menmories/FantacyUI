#ifndef __FANTACY_PANNEL_H__
#define __FANTACY_PANNEL_H__
#include "Types.h"
#include "Base/Geometry.h"
#include "Widget.h"
#include <vector>
class FANTACY_API FPannel : public FWidget
{
public:
	FPannel();

	void AddChild(FWidget* Widget);

	void SetBackgroundColor(const FColor& InColor);

	FColor GetBackgroundColor()const;

	virtual void OnPaint(FCanvas* Canvas);
protected:
	/*FCanvas* StartPannel();

	virtual FWidget* FindPointInWidget(const FPoint& InPoint);
protected:
	/*FCanvas* StartPannel();

	void EndPannel(FCanvas);*/
private:
	std::vector<FWidget*> mChilds;
	FColor BackgroundColor;
};




#endif // !__FANTACY_PANNEL_H__

