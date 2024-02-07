#include "../include/application.hpp"

using namespace app;

using namespace std::string_literals;

Application::WindowAlreadyExists::WindowAlreadyExists(const std::string_view window_name)
:
    logic_error{"Window \""s + std::string{window_name} + "\" already exists!\n"}
{
}

void Application::update(const Seconds elapsed_seconds)
{
    clearWindows();
    updateWindows(elapsed_seconds);
    displayWindows();
    removeWindows();
}

void Application::clearWindows()
{
    for(auto& [window_name, window] : windows)
    {
        window->clear();
    }
}

void Application::displayWindows()
{
    for(auto& [window_name, window] : windows)
    {
        // Draw is also a member function of sf::RenderWindow
        // must be resolved explicitly
        window->Gui::draw();
        window->display();
    }
}

void Application::updateWindows(const Seconds elapsed_seconds)
{
    for(auto& [window_name, window] : windows)
    {
        window->update(elapsed_seconds);
    }
}

bool Application::removeWindow(const std::string_view window_name)
{
    if(!windows.contains(std::string{window_name}))
    {
        return false;
    }
    else 
    {
        windows.erase(std::string{window_name});

        return true;
    }
}

bool Application::removeWindow(const std::shared_ptr<Window> window_pointer)
{
    const auto window_it {
        std::find_if(
            windows.cbegin(),
            windows.cend(),
            [window_pointer](const auto pair)
            {
                return pair.second == window_pointer;
            }
        )
    };

    if(window_it == windows.end())
    {
        return false;
    }
    else 
    {
        windows.erase(window_it);

        return true;
    }
}

Application::WindowPtr Application::getWindow(const std::string_view window_name)
{
    if(!windows.contains(std::string{window_name}))
    {
        return nullptr;
    }
    else 
    {
        return windows[std::string{window_name}];
    }
}

bool Application::addWindowToRemoveList(const WindowPtr window_ptr)
{
    const auto window_it {
        std::find_if(
            windows.cbegin(),
            windows.cend(),
            [window_ptr](const auto pair)
            {
                return pair.second == window_ptr;
            }
        )
    };

    if(window_it == windows.cend())
    {
        return false;
    }
    else 
    {
        windows_to_remove.push_back(window_ptr);

        return true;
    }
}

void Application::removeWindows()
{
    for(const auto& window_ptr : windows_to_remove)
    {
        removeWindow(window_ptr);
    }

    windows_to_remove.clear();
}
