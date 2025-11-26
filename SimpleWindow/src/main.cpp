#include <stdio.h>
#include <CApplication.h>
#include <Window/CWindow.h>

#include "Core/FaString.h"
#include <locale>


class MainWindow : public CWindow
{
public:
    MainWindow()
    {
        int width = 1920, height = 1080;
        setTitle("Hello World");
        resize(1200, 720);
        centerScreen();
        m_pixmap.load_file("../../Images/12dd.jpg");     
    }

    virtual void paint()
    {
        int width = 1200, height = 720;
        getSize(width, height);
        CPainter painter(this);
        painter.clear(0.01f, 0.7f, 1.0f);
        painter.drawPixmap(m_pixmap, 0, 0, width, height);
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

