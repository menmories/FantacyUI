#include <string>
#include <tchar.h>
#include <iostream>
#include <FantacyUI.h>

class CTestWindow : public FWindow
{
public:
    CTestWindow()
    {
        SetupUI();
    }

    virtual void ConstructUI()
    {
        /*FWidget* Widget = new FWidget();
        AddWidget(Widget);

        Widget = new FWidget();
        Widget->SetRect(FRectU(200, 200, 128, 128));
        AddWidget(Widget);*/
        FPannel* Pannel = new FPannel();
        Pannel->SetRect(FRectU(200, 10, 400, 600));
        Pannel->SetBackgroundColor(FColor(0x999999ff));
        AddWidget(Pannel);

        FLabel* Label = new FLabel();
        Label->SetText(TEXT("你好呀"));
        Label->SetRect(FRectU(10, 10, 128, 128));
        Pannel->AddChild(Label);

        FButton* TestButton = new FButton();
        TestButton->SetRect(FRectU(10, 100, 80, 28));
        TestButton->SetText(TEXT("我是按钮"));
        Pannel->AddChild(TestButton);
    }
};

int main()
{
    FApplication::Init();
    std::unique_ptr<CTestWindow> TestWindow(new CTestWindow());
    TestWindow->Show();
    FApplication::Exec();
}



