#pragma once

#include "types.hpp"
#include "window.hpp"

#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>
#include <memory>

namespace app
{
    // Updatable window Concept (T must be derived from app::Window)
    template <typename T>
    concept UpdatableWindow = std::is_base_of_v<app::Window, T>;

    class Application
    {
        public:
            class WindowAlreadyExists : public std::logic_error
            {
                public:
                    explicit WindowAlreadyExists(const std::string_view window_name);
            };        

            using WindowPtr = std::shared_ptr<Window>;
            using WindowsMap = std::unordered_map<std::string, WindowPtr>;

            Application() = default;

            virtual ~Application() = default;

            // Makes no sense to copy an Application object
            Application(const Application&)            = delete;
            Application& operator=(const Application&) = delete;

            virtual void update(const Seconds elapsed_seconds);
            
            template <UpdatableWindow WindowType = Window, typename... WindowArgs>
            void addWindow(
                const std::string_view window_name,
                bool show_window,
                WindowArgs&&... window_args
            );

            // Returns false if window is not found
            bool removeWindow(const std::string_view window_name);

            // Returns false if window is not found
            bool removeWindow(const std::shared_ptr<Window> window_pointer);

            // Intended to be called inside Window update member function
            // Returns false if window ptr is not found
            bool addWindowToRemoveList(const WindowPtr window_pointer);

            // Returns nullptr if window is not found
            WindowPtr getWindow(const std::string_view window_name);

        private:
            void updateWindows(const Seconds elapsed_seconds);
            void clearWindows();
            void displayWindows();
            void removeWindows();

            WindowsMap windows;
            std::vector<WindowPtr> windows_to_remove;
    };

    // Member function definitions

    template <UpdatableWindow WindowType, typename... WindowArgs>
    void Application::addWindow(
        const std::string_view window_name,
        bool show_window,
        WindowArgs&&... window_args
    )
    {
        if(windows.contains(std::string{window_name}))
        {
            throw WindowAlreadyExists{window_name};
        }
        else 
        {
            // Forward window_args to std::make_sharedclea
            windows[std::string{window_name}] = std::make_shared<WindowType>(
                *this,
                std::forward<WindowArgs>(window_args)...
            );

            windows[std::string{window_name}]->setVisible(show_window);
        }
    }
}