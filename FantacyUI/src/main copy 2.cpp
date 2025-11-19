

#include "CApplication.h"
#include "Window/CWindow.h"

#include <cairo-features.h>
#include <cairo.h>
#include <cairo-win32.h>

#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#define STB_IMAGE_RESIZE_IMPLEMENTATION
//#include "Painter/stb_image.h"
#include "Painter/CPixmap.h" 
#include "Painter/CPainter.h"

class MainWindow : public CWindow
{
public:
	MainWindow::MainWindow()
	{
		int width = 1200, height = 800;
		setTitle("Hello");
		resize(width, height);
		s32 screenWidth, screenHeight;
		CApplication::getScreenSize(screenWidth, screenHeight);
		move((screenWidth - width) / 2, (screenHeight - height) / 2);
		m_pixmap.load_file("F:/Images/image_naxida.png");
		
	}

	MainWindow::~MainWindow()
	{
		//cairo_surface_destroy(m_image1);
	}

	virtual void paint()
	{
		s32 width, height;
		getSize(width, height);
		CPainter painter(this);
		painter.beginPaint();
		painter.clear(1.0f, 1.0f, 1.0f);
		painter.drawPixmap(m_pixmap, 0, 0, width, height);
		painter.fillRoundedRect(400, 100, 320, 100, 20);

		painter.endPaint();

		//HDC dc = GetDC(winId());
		//cairo_surface_t* surface = cairo_win32_surface_create(dc);
		//cairo_t* cr = cairo_create(surface);

		//cairo_set_source_rgb(cr, 1.0f, 1.0f, 0.0f);
		//cairo_paint(cr);

		//s32 width, height;
		//getSize(width, height);

		//cairo_surface_t* m_image1 = (cairo_surface_t*)m_pixmap.data();
		//
		///*s32 img_width = cairo_image_surface_get_width(m_image1);
		//s32 img_height = cairo_image_surface_get_height(m_image1);*/
		//
		//// 计算缩放比例
		//double scale_x = (double)width / m_pixmap.width();
		//double scale_y = (double)height / m_pixmap.height();
		//double scale = scale_x < scale_y ? scale_x : scale_y; // 选择最小比例以避免失真
		///*cairo_surface_t* surf_target = cairo_image_surface_create_for_data(cairo_image_surface_get_data(m_image1), 
		//	CAIRO_FORMAT_RGB24, width, height, cairo_image_surface_get_stride(m_image1));*/
		//cairo_save(cr);
		//// 设置缩放比例并绘制图像
		//cairo_scale(cr, scale_x, scale_y); // 应用缩放
		//cairo_set_source_surface(cr, m_image1, 0, 0);
		//
		//cairo_paint(cr);
		////cairo_surface_destroy(surf_target);
  //      cairo_restore(cr);

		//// 清理Cairo资源
		//cairo_destroy(cr);
		//cairo_surface_destroy(surface);
		//ReleaseDC(winId(), dc);
		//ValidateRect(winId(), nullptr);
	}
private:
	CPixmap m_pixmap;
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

