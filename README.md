# FantacyUI

基于Direct2D来实现的Gui库,仅支持Windows.

使用方法

新建Visual studio 2022工程(控制台或者是Win32应用程序)
包含FantacyUI的lib文件和头文件所在目录,并引用lib文件
新建一个类，继承自FWindow，并在main函数所在目录中添加如下代码：

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

    /* 在该函数中添加UI控件 */
    virtual void ConstructUI()
    {
        FPannel* Pannel = new FPannel();
        Pannel->SetRect(FRectU(200, 10, 460, 600));
        Pannel->SetBackgroundColor(FColor(0x999999ff));
        AddWidget(Pannel);      //在窗口上添加Widget

        FButton* TestButton = new FButton();
        TestButton->SetRect(FRectU(10, 10, 80, 28));
        TestButton->SetText(TEXT("我是按钮"));
        TestButton->OnClicked = std::bind(&CTestWindow::OnTestButtonClicked, this);
        Pannel->AddChild(TestButton);
        SetText(TEXT("这是D2D窗口"));
    }
};

int main(int argc, char** argv)
{
    FApplication::Init();
    std::unique_ptr<CTestWindow> TestWindow(new CTestWindow());
    TestWindow->Show();
    FApplication::Exec();
}

2023/4/20
完成基本UI绘制和事件逻辑


Widget  UI基础部件，提供了UI基础功能
Pannel  面板，主要用于装载控件的容器
Button  按钮，提供了基本事件处理

所有的初始控件必须在ConstructUI中进行初始化，之后才可在随意操作UI


