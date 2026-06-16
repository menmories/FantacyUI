#include <stdio.h>
#include <XMApplication.h>
#include <Window/XMWindow.h>
#include <Core/XMPainter.h>

#include <thread>

class MainWindow : public XMWindow
{
public:
	MainWindow()
		: m_bQuit(false)
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

	void threadFunc()
	{
		while (!this->m_bQuit)
		{
			static int count = 0;
			XMApplication::sendEvent(1, nullptr, [](int type, void* args)
			{
				printf("Hello block event, count=%d\n", count);
			});
			Sleep(1000);
			count++;
		}
	}

	virtual void onCreate() override
	{
		if (!m_image1.loadFromFile("../../images/12dd.jpg"))
		{
			fprintf(stderr, "load image failed!\n");
			return;
		}

		m_thread_ = std::thread(&MainWindow::threadFunc, this);
		m_thread_.detach();
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

	virtual void onMouseButtonDown(const MouseButton& btn, bool bDown) override
	{
		if (btn == MouseButton::MouseButton_Left)
		{
			if (bDown)
			{
				XMApplication::sendEvent(1, nullptr, [](int type, void* args)
				{
					printf("Hello block event\n");
				});
			}
		}
	}

	void onDestroy() override
	{
		m_bQuit = 1;
	}
private:
	XMImage m_image1;
	std::thread m_thread_;
	volatile bool m_bQuit;
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

