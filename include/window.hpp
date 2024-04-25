#pragma once

#include "../../tgui/include/TGUI/TGUI.hpp"
#include "../../tgui/include/TGUI/Backend/SFML-Graphics.hpp"

#include "types.hpp"

#include <string_view>
#include <filesystem>
#include <stdexcept>

namespace app
{
    class Window : public sf::RenderWindow, public tgui::Gui, public std::enable_shared_from_this<Window>
    {
        public:
            class InterfaceFileNotFound : public std::runtime_error
            {
                public:
                    explicit InterfaceFileNotFound(const std::string_view file_path);
            };

            /*
            class WidgetErrorAlreadyExists : public std::logic_error
            {
                public:
                    explicit WidgetErrorAlreadyExists(const std::string_view widget_name);
            };

            class WidgetNotFound : public std::logic_error
            {
                public:
                    explicit WidgetNotFound(const std::string_view widget_name);
            };
            */

            Window() = default;

            template <typename... SFMLWindowArgs>
            Window(
                Application& application,
                const std::string_view interface_file_path,
                SFMLWindowArgs&&... sfml_window_args
            );

            virtual ~Window() = default;

            virtual void update(const Seconds elapsed_seconds);

            // Returns nullptr if widget is not found or if 
            // widget pointer dynamic cast fails
            template <typename WidgetType = tgui::Widget>
            std::shared_ptr<WidgetType> getWidget(const std::string_view widget_name);

            // Returns false if widget is not found
            bool setWidgetToolTip(
                const std::string_view widget_name,
                const std::string_view tooltip_rich_text,
                const size_t           tooltip_text_size = 20
            );

            // Returns false if widget is not found
            // Replaces already existing error
            bool addErrorToWidget(
                const std::string_view widget_name,
                const std::string_view error_rich_text,
                const size_t           error_text_size,
                const size_t           error_text_vertical_offset = 30
            );

            // Returns false if widget is not found 
            // Doesn't do anything no error is found
            bool removeErrorFromWidget(const std::string_view widget_name);

        private:
            Application& application;

            const std::string widget_error_postfix {"_APP_ERROR"};
    };

    // Member function definitions

    template <typename WidgetType>
    std::shared_ptr<WidgetType> Window::getWidget(const std::string_view widget_name)
    {
        return std::dynamic_pointer_cast<WidgetType>(get(std::string{widget_name}));
    }

    template <typename... SFMLWindowArgs>
    Window::Window(
        Application& application,
        const std::string_view interface_file_path,
        SFMLWindowArgs&&... sfml_window_args
    )
    :
        RenderWindow{std::forward<SFMLWindowArgs>(sfml_window_args)...},
        application{application}
    {
        setWindow(*this);
        
        if(interface_file_path != "")
        {
            if(!std::filesystem::exists(std::string{interface_file_path}))
            {
                throw InterfaceFileNotFound{interface_file_path};
            }
            else 
            {
                loadWidgetsFromFile(std::string{interface_file_path});
            }
        }
    }
}
