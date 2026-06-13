#include <stdio.h>
#include <XMApplication.h>
#include <Window/XMWindow.h>
#include <Core/XMPainter.h>


class MainWindow : public XMWindow
{
public:
	MainWindow()
	{
		setTitle("XMUI Test");
		s32 screenWidth, screenHeight;
		XMApplication::getScreenSize(screenWidth, screenHeight);
		resize((s32)(screenWidth * 0.75f), (s32)(screenHeight * 0.7f));
		//resize(1920, 1080);
	}

	~MainWindow()
	{
	}

	virtual void onCreate() override
	{
		XMWindow::onCreate();
		if (!m_image1.loadFromFile("E:\\GitHub\\FantacyUI\\images\\12dd.jpg"))
		{
			fprintf(stderr, "load image failed!\n");
			return;
		}
	}

	virtual void onPaint(class XMPainter* painter)
	{
		s32 width, height;
		getSize(width, height);
		painter->drawImage(m_image1, 0, 0, width, height);

		XMFont font("微软雅黑", 14);
		XMBrush brush(XMColor(255, 0, 0));
		painter->fillRect(XMRect(30, 30, 130, 130), brush);

		XMString text;
		text.FromUtf8("你好，我是王大锤");
		painter->drawText(text, XMRect(30, 600, 230, 650), brush, font);

		XMPen pen;
		painter->drawRect(XMRect(300, 600, 400, 700), brush, pen);

		//fprintf(stdout, "width=%d,height=%d\n", width, height);
		//painter->drawImage(m_image1, 0, 0, m_image1.width(), m_image1.height());
	}

private:
	XMImage m_image1;
};

int main(int argc, char** argv)
{
	XMApplication app(argc, argv);
	XMApplication::enableHighDPIScaling();


	MainWindow mainWindow;
	mainWindow.centerScreen();
	mainWindow.show();

	mainWindow.setTitle("fsddfd");

    return app.run();
}

