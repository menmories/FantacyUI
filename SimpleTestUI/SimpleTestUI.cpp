#include <string>
#include <tchar.h>
#include <iostream>
#include <FantacyUI.h>
#include <functional>

class CTestWindow : public FWindow
{
public:
    FTabPannel* TabPanel;
    CTestWindow()
        : TabPanel(nullptr)
    {
        uSelectedIndex = 0;
        SetupUI();
    }

    bool OnPrevPageButtonClicked()
    {
        if (uSelectedIndex > 0)
        {
            uSelectedIndex--;
            TabPanel->SelectPage(uSelectedIndex);
        }
        else
        {
            printf("没有前一页了\n");
        }
        return true;
    }

    bool OnNextPageButtonClicked()
    {
        if (uSelectedIndex < (TabPanel->GetPageCount() - 1))
        {
            uSelectedIndex++;
            TabPanel->SelectPage(uSelectedIndex);
        }
        else
        {
            printf("没有下一页了\n");
        }
        return true;
    }

    u32 uSelectedIndex;

    virtual void ConstructUI()
    {
        FPannel* Pannel = new FPannel();
        Pannel->SetRect(FRectU(0, 0, 460, 600));
        Pannel->SetBackgroundColor(FColor(0x999999ff));
        AddWidget(Pannel);

        FButton* TestButton = new FButton();
        TestButton->SetRect(FRectU(10, 10, 80, 28));
        TestButton->SetText(TEXT("上一页"));
        TestButton->OnClicked = std::bind(&CTestWindow::OnPrevPageButtonClicked, this);
        Pannel->AddChild(TestButton);
        SetText(TEXT("这是D2D窗口"));

        TestButton = new FButton();
        TestButton->SetRect(FRectU(100, 10, 80, 28));
        TestButton->SetText(TEXT("下一页"));
        TestButton->OnClicked = std::bind(&CTestWindow::OnNextPageButtonClicked, this);
        Pannel->AddChild(TestButton);
        SetText(TEXT("这是D2D窗口"));

        TabPanel = new FTabPannel();
        TabPanel->SetRect(FRectU(1, 50, 400, 500));
        FPannel* PagePannel = TabPanel->AddPage();
        PagePannel->SetBackgroundColor(FColor(0xff, 0x00, 0x00));
        FButton* PageButton = new FButton();
        PageButton->SetRect(FRectU(10, 10, 120, 28));
        PageButton->SetText(TEXT("我是页面一按钮"));
        PagePannel->AddChild(PageButton);

        PagePannel = TabPanel->AddPage();
        PagePannel->SetBackgroundColor(FColor(0x00, 0xff, 0x00));

        PageButton = new FButton();
        PageButton->SetRect(FRectU(10, 10, 120, 28));
        PageButton->SetText(TEXT("我是页面二按钮"));
        PagePannel->AddChild(PageButton);

        
        PagePannel = TabPanel->AddPage();
        PagePannel->SetBackgroundColor(FColor(0x00, 0x00, 0xff));

        PageButton = new FButton();
        PageButton->SetRect(FRectU(10, 10, 120, 28));
        PageButton->SetText(TEXT("我是页面三按钮"));
        PagePannel->AddChild(PageButton);

        Pannel->AddChild(TabPanel);

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



