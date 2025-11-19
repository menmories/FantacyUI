

#include "CApplication.h"
#include "Window/CWindow.h"

#include <cairo-features.h>
#include <cairo.h>
#include <cairo-win32.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "Painter/stb_image.h"

class MainWindow : public CWindow
{
public:
	MainWindow::MainWindow()
	{
		setTitle("Hello");
		resize(800, 600);
		s32 screenWidth, screenHeight;
		CApplication::getScreenSize(screenWidth, screenHeight);
		move((screenWidth - 800) / 2, (screenHeight - 600) / 2);

		//FILE* pFile = fopen("F:/Images/image_naxida.png", "rb+");
		//FILE* pFile = fopen("F:/Images/104789550_p0_013410.png", "rb+");
		FILE* pFile = fopen("F:/Images/ce481325beeb7429095e2ebef1ea5a7a_1034705625688720350.jpg", "rb+");
		if (pFile)
		{
			int img_width = 0, img_height = 0, comp = 0;
			stbi_uc* stbi_image = stbi_load_from_file(pFile, &img_width, &img_height, &comp, STBI_rgb_alpha);
			fclose(pFile);
			int stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, img_width);
			// m_image1 = cairo_image_surface_create_for_data(stbi_image, CAIRO_FORMAT_ARGB32, img_width, img_height, stride);
			m_image1 = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, img_width, img_height);
			unsigned char* image_surface_data = cairo_image_surface_get_data(m_image1);
			
			bool bAlphaChannel = false;
			for (int i = 0; i < img_width * img_height; i++)
			{
				image_surface_data[i * 4 + 3] = stbi_image[i * 4 + 3];
				if (image_surface_data[i * 4 + 3] < 255)
				{
					image_surface_data[i * 4] = (BYTE)(DWORD(stbi_image[i * 4 + 2]) * stbi_image[i * 4 + 3] / 255);
					image_surface_data[i * 4 + 1] = (BYTE)(DWORD(stbi_image[i * 4 + 1]) * stbi_image[i * 4 + 3] / 255);
					image_surface_data[i * 4 + 2] = (BYTE)(DWORD(stbi_image[i * 4]) * stbi_image[i * 4 + 3] / 255);
					bAlphaChannel = true;
				}
				else
				{
					image_surface_data[i * 4] = stbi_image[i * 4 + 2];
					image_surface_data[i * 4 + 1] = stbi_image[i * 4 + 1];
					image_surface_data[i * 4 + 2] = stbi_image[i * 4];
				}

				if (*(DWORD*)(&image_surface_data[i * 4]) == 0) {
					image_surface_data[i * 4] = (BYTE)0;
					image_surface_data[i * 4 + 1] = (BYTE)0;
					image_surface_data[i * 4 + 2] = (BYTE)0;
					image_surface_data[i * 4 + 3] = (BYTE)0;
					bAlphaChannel = true;
				}
			}

			cairo_surface_mark_dirty(m_image1);
			stbi_image_free(stbi_image);
		}
		

		//m_image1 = cairo_image_surface_create_from_png("F:/Images/79130197_p0_013918.png");
		//m_image1 = cairo_image_surface_create_from_png("F:/Images/image_naxida.png");
		
		cairo_status_t status = cairo_surface_status(m_image1);
		if (status != CAIRO_STATUS_SUCCESS)
		{
			fprintf(stderr, "load image failed!\n");
			return;
		}
	}

	MainWindow::~MainWindow()
	{
		cairo_surface_destroy(m_image1);
	}

	virtual void paint()
	{
		HDC dc = GetDC(winId());
		cairo_surface_t* surface = cairo_win32_surface_create(dc);
		cairo_t* cr = cairo_create(surface);

		cairo_set_source_rgb(cr, 1.0f, 1.0f, 0.0f);
		cairo_paint(cr);

		s32 width, height;
		getSize(width, height);

		s32 img_width = cairo_image_surface_get_width(m_image1);
		s32 img_height = cairo_image_surface_get_height(m_image1);
		
		// 计算缩放比例
		double scale_x = (double)width / img_width;
		double scale_y = (double)height / img_height;
		double scale = scale_x < scale_y ? scale_x : scale_y; // 选择最小比例以避免失真
		/*cairo_surface_t* surf_target = cairo_image_surface_create_for_data(cairo_image_surface_get_data(m_image1), 
			CAIRO_FORMAT_RGB24, width, height, cairo_image_surface_get_stride(m_image1));*/
		// 设置缩放比例并绘制图像
		cairo_scale(cr, scale_x, scale_y); // 应用缩放
		cairo_set_source_surface(cr, m_image1, 0, 0);
		
		cairo_paint(cr);
		//cairo_surface_destroy(surf_target);

		// 清理Cairo资源
		cairo_destroy(cr);
		cairo_surface_destroy(surface);
		ReleaseDC(winId(), dc);
		ValidateRect(winId(), nullptr);
	}
private:
	cairo_surface_t* m_image1;
};



int main(int argc, char** argv)
{
	CApplication app;
	MainWindow mainWindow;
	mainWindow.show();
	//mainWindow.resize(800, 600);
	/*s32 width = 0, height = 0;
	mainWindow.getSize(width, height);*/
	return app.run();
}

