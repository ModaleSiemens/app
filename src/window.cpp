#include "../include/window.hpp"

#include "application.hpp"

using namespace app;

using namespace std::string_literals;

Window::InterfaceFileNotFound::InterfaceFileNotFound(const std::string_view file_path)
    : runtime_error{"TGUI's Gui file at \""s + std::string{file_path} + "\" not found!\n"}
{
}

void Window::update(const Seconds elapsed_seconds)
{
    sf::Event event;

    while(pollEvent(event))
    {
        handleEvent(event);

        if(event.type == sf::Event::Closed)
        {
            application.addWindowToRemoveList(shared_from_this());
        }
    }
}

bool Window::setWidgetToolTip(
    const std::string_view widget_name,
    const std::string_view tooltip_rich_text,
    const size_t           tooltip_text_size 
)
{
    if(
        auto widget {get(std::string{widget_name})};
        widget == nullptr
    )
    {
        return false;
    }
    else 
    {
        auto rich_text_label {
            tgui::RichTextLabel::create(
                std::string{tooltip_rich_text}
            )
        };

        rich_text_label->setTextSize(tooltip_text_size);

        widget->setToolTip(rich_text_label);

        return true;
    }
}

bool Window::addErrorToWidget(
    const std::string_view widget_name,
    const std::string_view error_rich_text,
    const size_t           error_text_size,
    const size_t           error_text_vertical_offset
)
{
    if(
        auto widget {get(std::string{widget_name})};
        widget == nullptr
    )
    {
        return false;
    }
    else 
    {
        const std::string error_name {
            std::string{widget_name} + widget_error_postfix
        };

        std::shared_ptr<tgui::RichTextLabel> error_rich_text_label;

        // If error doesn't exist, create it; otherwise, reuse it
        if(
            auto widget {getWidget<tgui::RichTextLabel>(error_name)};
            widget == nullptr
        )
        {
            error_rich_text_label = tgui::RichTextLabel::create(
                std::string{error_rich_text}
            );

            error_rich_text_label->setTextSize(error_text_size);

            error_rich_text_label->setPosition(
                tgui::bindLeft(widget),
                tgui::bindTop(widget) + error_text_vertical_offset
            );            

            add(error_rich_text_label, error_name);
        }
        else 
        {
            widget->setText(std::string{error_rich_text});
        }

        return true;
    }
}

bool Window::removeErrorFromWidget(const std::string_view widget_name)
{
    return remove(get(std::string{widget_name} + widget_error_postfix));
}
