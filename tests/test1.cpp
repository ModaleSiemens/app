#include "../include/app.hpp"

class PopUp : public app::Window
{
    public:
        PopUp(app::Application& app, const std::string_view interface_path);

        virtual ~PopUp() = default;

        //virtual void update(const app::Seconds elapsed_seconds) override;
};

PopUp::PopUp(app::Application& app, const std::string_view interface_path)
:
    Window{app, interface_path, sf::VideoMode(200, 75), "Alert!", sf::Style::Close}
{
}

class MyApp : public app::Application
{
    public:
        using Application::Application;

        virtual ~MyApp() = default;

        virtual void update(const app::Seconds elapsed_seconds) override;
};

void MyApp::update(const app::Seconds elapsed_seconds)
{
    Application::update(elapsed_seconds);
}

int main()
{
    using namespace app;

    using namespace std::chrono_literals;

    MyApp app;

    app.addWindow("main_window", true, "../../tests/assets/test1_main.txt", sf::VideoMode(800, 600), "Main Window!");
    app.addWindow<PopUp>("popup_1", false, "../../tests/assets/popup1.txt");

    app.getWindow("main_window")->getWidget<tgui::Slider>("slider")->onValueChange(
        [&]()
        {
            if(app.getWindow("popup_1") == nullptr)
            {
                app.addWindow<PopUp>("popup_1", false, "../../tests/assets/popup1.txt");
            }

            app.getWindow("popup_1")->setVisible(true);
        }
    );

    while(true)
    {
        app.update(0.5s);
    }

    return 0;
}