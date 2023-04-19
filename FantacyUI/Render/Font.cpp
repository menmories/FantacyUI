#include "pch.h"
#include "Render/Font.h"
#include "Canvas.h"

class FDirect2DContext;
FFont::FFont()
    : Obj(nullptr)
{
}

FFont::~FFont()
{
    IDWriteTextFormat* textFormat = (IDWriteTextFormat*)Obj;
    if (textFormat)
    {
        textFormat->Release();
        textFormat = nullptr;
    }
}

void* FFont::GetObj()
{
    return this->Obj;
}

void FFont::SetObj(void* obj)
{
    this->Obj = obj;
}

FFontManager* FFontManager::Get()
{
    static FFontManager* FontManager = new FFontManager();
    return FontManager;
}

FFont* FFontManager::AddNewFont(u32 uID, const FString& FontFamily, float FontSize)
{
    IDWriteTextFormat* TextFormat = nullptr;
    HRESULT hr = FDirect2DContext::Get()->DWriteFactory->CreateTextFormat(FontFamily.c_str(),
        NULL,
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        FontSize,
        TEXT("zh-cn"),
        &TextFormat);
    if (SUCCEEDED(hr))
    {
        FFont* NewFont = new FFont();
        NewFont->SetObj(TextFormat);
        mFonts.insert(std::pair<u32, FFont*>(uID, NewFont));
        return NewFont;
    }
    return nullptr;
}

FFont* FFontManager::CreateNewFont(const FString& FontFamily, float FontSize)
{
    IDWriteTextFormat* TextFormat = nullptr;
    HRESULT hr = FDirect2DContext::Get()->DWriteFactory->CreateTextFormat(FontFamily.c_str(),
        NULL,
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        FontSize,
        TEXT("zh-cn"),
        &TextFormat);
    if (SUCCEEDED(hr))
    {
        FFont* NewFont = new FFont();
        NewFont->SetObj(TextFormat);
        return NewFont;
    }
    return nullptr;
}

u32 FFontManager::GetFontCount() const
{
    return (u32)mFonts.size();
}

void FFontManager::Destroy()
{
    delete this;
}

FFont* FFontManager::GetFont(u32 FontId)
{
    auto iter = mFonts.find(FontId);
    if (iter == mFonts.end())
    {
        return nullptr;
    }
    return iter->second;
}

FFontManager::FFontManager()
{
    //FFont* DefaultFont = CreateNewFont(TEXT("Î¢ÈíÑÅºÚ"), 14.0f);
    AddNewFont(DEFAULT_FONT_ID, TEXT("Î¢ÈíÑÅºÚ"), 14.0f);
}

FFontManager::~FFontManager()
{
    for (auto iter = mFonts.begin(); iter != mFonts.end(); iter++)
    {
        delete iter->second;
    }
}
