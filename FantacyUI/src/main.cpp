

#include "CApplication.h"
#include "Window/CWindow.h"

#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#define STB_IMAGE_RESIZE_IMPLEMENTATION
//#include "Painter/stb_image.h"
#include "Painter/CPixmap.h" 
#include "Painter/CPainter.h"
#include "Painter/CD3D11Device.h"

class MainWindow : public CWindow
{
public:
	MainWindow::MainWindow()
		//: m_image1(L"F:/Images/ce481325beeb7429095e2ebef1ea5a7a_1034705625688720350.jpg")
	{
		m_pixmap.loadFile("F:/Images/image_naxida.png");
		//m_pixmap.load_file("F:/Images/ce481325beeb7429095e2ebef1ea5a7a_1034705625688720350.jpg");
        //m_pixmap.load_file("F:/Images/psc.jpg");
        //m_pixmap.load_file("F:/Images/girl_flower_dress_876877_1920x1080.jpg");
		
		//int width = m_pixmap.width(), height = m_pixmap.height();
		int width = 1200, height = 720;
		setTitle("Hello");
		resize(width, height);
		s32 screenWidth, screenHeight;
		CApplication::getScreenSize(screenWidth, screenHeight);
		move((screenWidth - width) / 2, (screenHeight - height) / 2);
	}

	MainWindow::~MainWindow()
	{
		//cairo_surface_destroy(m_image1);
	}

	virtual void paint()
	{
		//if (!IsWindowVisible(winId()) || IsIconic(winId())) {
		//	// 窗口不可见或最小化，跳过绘制
		//	PAINTSTRUCT ps;
		//	BeginPaint(winId(), &ps);
		//	EndPaint(winId(), &ps);
		//	return;
		//}

		//

		s32 width, height;
		getSize(width, height);
		CPainter painter(this);
		
        painter.clear(1.0f, 1.0f, 0.0f);
		painter.drawPixmap(m_pixmap, 0, 0, width, height);

		painter.fillRect(10, 10, 150, 32);
		painter.fillRoundedRect(10, 50, 150, 32, 32, 32);
		painter.drawRoundedRect(10, 100, 155, 32, 32, 32, 3.0f);

		painter.drawRect(10, 150, 155, 32, 3.0f);

		painter.drawLine(10, 200, 300, 200, 3.0f);

		painter.setFont(CFont( L"Consolas", 32));
		painter.drawText(L"Hello World", 320, 320);


		//painter.testPaint(&m_pixmap);
		/*painter.beginPaint();
		painter.clear(1.0f, 1.0f, 0.0f);
		painter.drawPixmap(m_pixmap, 0, 0, width, height);
		painter.fillRoundedRect(400, 100, 320, 100, 20);
		painter.setBrush(CBrush(0.02f, 0.8f, 1.0f));
		painter.drawLine(30, 30, 600, 600, 2.0f);
		painter.setBrush(CBrush(1.0f, 0.0f, 0.0f));
		painter.setFont(CFont("Microsoft Yahei", 20));
		painter.drawText("Microsoft Yahei", 420, 530);
		painter.endPaint();*/

		/*m_d3d11Device.clear(1.0f, 0.0f, 0.0f, 1.0f);
        

		m_d3d11Device.swapBuffer();
		ValidateRect(winId(), nullptr);*/



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

	virtual void onCreate()
	{
		/*if (!m_d3d11Device.init(winId()))
		{
			fprintf(stderr, "Failed to initialize Direct3D 11 device.\n");
			return;
		}*/
	}

	virtual void onResize(s32 width, s32 height)
	{
		//m_d3d11Device.resize(width, height);
		
	}

	virtual void onDestroy()
	{
		//m_d3d11Device.release();
		CApplication::quit();
	}
private:
	CPixmap m_pixmap;
	//Gdiplus::Image m_image1;
	//CD3D11Device m_d3d11Device;
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

