#include "Painter/CPixmap.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "Painter/stb_image.h"

void rgbaToArgb(u8* rgba, size_t pixelCount) {
    assert(rgba);
    // 遍历每个像素并转换格式
    for (size_t i = 0; i < pixelCount; i++) {
        // 计算当前像素在数组中的起始索引
        size_t index = i * 4;

        // 提取RGBA分量
        u8 r = rgba[index];     // 红色分量
        u8 g = rgba[index + 1]; // 绿色分量
        u8 b = rgba[index + 2]; // 蓝色分量
        u8 a = rgba[index + 3]; // Alpha分量

        // 按ARGB顺序存储到输出数组
        rgba[index] = b;     // Alpha分量
        rgba[index + 1] = g; // 红色分量
        rgba[index + 2] = r; // 绿色分量
        rgba[index + 3] = a; // 蓝色分量
    }
}

CPixmap::CPixmap()
	: m_data(nullptr)
	, m_width(0)
	, m_height(0)
	, m_comp(0)
{
}

CPixmap::~CPixmap()
{
}

bool CPixmap::load_file(const char* fileName)
{
	FILE* pFile = fopen(fileName, "rb+");
	if (!pFile)
	{
		return false;
	}
	stbi_uc* stbi_image = stbi_load_from_file(pFile, &m_width, &m_height, &m_comp, STBI_rgb_alpha);
	fclose(pFile);


    rgbaToArgb(stbi_image, m_width * m_height);
    //m_data = stbi_image;

	m_data = CreateBitmap(m_width, m_height, 1, 32, stbi_image);
	free(stbi_image);
	return true;
}


