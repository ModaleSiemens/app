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