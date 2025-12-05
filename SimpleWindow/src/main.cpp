#include <stdio.h>
#include <CApplication.h>
#include <Window/CWindow.h>

#include "Core/FaString.h"
#include <locale>

#include <Widgets/CText.h>
#include <Widgets/CImageRect.h>

class MainWindow : public CWindow
{
public:
    MainWindow()
    {
        m_pixmap.loadFile("../../Images/12dd.jpg");
        int width = 1920, height = 1080;
        setTitle("Hello World");
        resize((s32)(m_pixmap.width() / 1.5f), (s32)(m_pixmap.height() / 1.5f));
        centerScreen();
        setWindowStyle(WindowStyle::FramelessWindow);

        CWidget* rootWidget = new CWidget();
        setRoot(rootWidget);

        CImageRect* imageRect = new CImageRect(rootWidget);
        imageRect->move(200, 10);
        imageRect->resize((s32)(m_pixmap.width() / 2.0f), (s32)(m_pixmap.height() / 2.0f));
        imageRect->setImage("../../Images/12dd.jpg");

        CText* text1 = new CText("Hello", rootWidget);
        //text1->setTextColor
        CFont font;
        font.setFontSize(24);
        text1->setFont(font);
        text1->setTextColor(CColor(1.0f, 0.0f, 0.0f));
        text1->move(30, 30);
        text1->resize(100, 30);
        
    }

    virtual void paint()
    {
        CWindow::paint();
        /*int width = 1200, height = 720;
        getSize(width, height);
        CPainter painter(this);
        painter.clear(0.01f, 0.7f, 1.0f);
        painter.drawPixmap(m_pixmap, 0, 0, width, height);
        painter.fillRoundedRect(700, 200, 420, 320, 20, 20);*/
    }


private:
    CPixmap m_pixmap;
};

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");
    /*FaString str(L"Hello World!\n");
    
    wprintf(L"%s\n", str.Str());

    str = FaString(L"hdsakjsd");
    wprintf(L"%s\n", str.Str());

    str = FaString("inet_11111111111111111111111111111");
    wprintf(L"%s\n", str.Str());

    str = "12345";
    wprintf(L"%s\n", str.Str());
    str.FromUtf8(u8"你好呀");

    str += "4444";

    wprintf(L"%s\n", str.Str());*/

    CApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.run();
}

