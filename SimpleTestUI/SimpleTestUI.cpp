#include <string>
#include <tchar.h>
#include <iostream>
#include <FantacyUI.h>
#include <functional>

class CTestWindow : public FWindow
{
public:
    CTestWindow()
    {
        SetupUI();
    }

    bool OnTestButtonClicked()
    {
        printf("Hello\n");
        return true;
    }

    bool OnJiuMingBtnClicked() 
    {
        printf("救命啊\n");
        return true;
    }

    virtual void ConstructUI()
    {
        FPannel* Pannel = new FPannel();
        Pannel->SetRect(FRectU(200, 10, 460, 600));
        Pannel->SetBackgroundColor(FColor(0x999999ff));
        AddWidget(Pannel);

        FButton* TestButton = new FButton();
        TestButton->SetRect(FRectU(10, 10, 80, 28));
        TestButton->SetText(TEXT("我是按钮"));
        TestButton->OnClicked = std::bind(&CTestWindow::OnTestButtonClicked, this);
        Pannel->AddChild(TestButton);
        SetText(TEXT("这是D2D窗口"));

        TestButton = new FButton();
        TestButton->SetRect(FRectU(10, 70, 80, 28));
        TestButton->SetText(TEXT("我是按钮"));
        TestButton->OnClicked = std::bind(&CTestWindow::OnJiuMingBtnClicked, this);
        Pannel->AddChild(TestButton);
        SetText(TEXT("这是D2D窗口"));

        ///*FWidget* Widget = new FWidget();
        //AddWidget(Widget);

        //Widget = new FWidget();
        //Widget->SetRect(FRectU(200, 200, 128, 128));
        //AddWidget(Widget);*/
        //FPannel* Pannel = new FPannel();
        //Pannel->SetRect(FRectU(200, 10, 460, 600));
        //Pannel->SetBackgroundColor(FColor(0x999999ff));
        //AddWidget(Pannel);

        ///*FLabel* Label = new FLabel();
        //Label->SetText(TEXT("你好呀"));
        //Label->SetRect(FRectU(10, 10, 128, 128));
        //Pannel->AddChild(Label);*/

        ///*FButton* TestButton = new FButton();
        //TestButton->SetRect(FRectU(10, 10, 80, 28));
        //TestButton->SetText(TEXT("我是按钮"));
        //Pannel->AddChild(TestButton);

        //TestButton = new FButton();
        //TestButton->SetRect(FRectU(10, 50, 80, 28));
        //TestButton->SetText(TEXT("我是按钮"));
        //Pannel->AddChild(TestButton);*/

        //u32 YPos = 10;
        //u32 XPos = 10;
        //for (int i = 0; i < 5; i++)
        //{
        //    for (int j = 0; j < 10; j++)
        //    {
        //        FButton* TestButton = new FButton();
        //        TestButton->SetRect(FRectU(XPos, YPos, 80, 28));
        //        TestButton->SetText(TEXT("我是按钮"));
        //        TestButton->OnClicked = std::bind(&CTestWindow::OnTestButtonClicked, this);
        //        Pannel->AddChild(TestButton);
        //        YPos += 35;
        //    }

        //    XPos += 90;
        //    YPos = 10;
        //}
        //SetText(TEXT("这是D2D窗口"));
    }
};

int main()
{
    FApplication::Init();
    std::unique_ptr<CTestWindow> TestWindow(new CTestWindow());
    TestWindow->Show();
    FApplication::Exec();
}



