#ifndef __FANTACY_BITMAP_H__
#define __FANTACY_BITMAP_H__

class FANTACY_API FBitmap
{
public:
	FBitmap();

	~FBitmap();

	void SetObj(void* InObj);

	void* GetObj();
private:
	void* Obj;
};

#endif // !__FANTACY_BITMAP_H__
