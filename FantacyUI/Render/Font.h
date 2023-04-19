#ifndef __FANTACY_FONT_H__
#define __FANTACY_FONT_H__
#include <unordered_map>
#include "Base/String.h"

#define DEFAULT_FONT_ID 0

class FANTACY_API FFont
{
public:
	FFont();

	~FFont();

	void* GetObj();

	void SetObj(void* obj);
private:
	void* Obj;
};


class FANTACY_API FFontManager
{
public:
	static FFontManager* Get();

	FFont* AddNewFont(u32 uID, const FString& FontFamily, float FontSize);

	FFont* CreateNewFont(const FString& FontFamily, float FontSize);

	u32 GetFontCount()const;

	void Destroy();

	FFont* GetFont(u32 FontId);
private:
	FFontManager();
	~FFontManager();
private:
	std::unordered_map<u32, FFont*> mFonts;
};

#endif // !__FANTACY_FONT_H__
