# App Library

This *app* library is based off Texus' *TGUI*, an SFML-based GUI library.

This library is intented to make managing multiple and interacting windows easier.

## Usage

This library exports the dependency `lib_app_dep` via Meson, so that you can add it as dependency in your project.

The header you should include to use this library is `app.hpp`, which defines its entities inside the namespace `app`.

## Application Class

The `Application` class is the class which manages windows. Windows, as specified by the *concept* `UpdatableWindow`, are class types derived from this library's `Window` class, which in turns derives from SFML `RenderWindow` and TGUI `Gui`.

When a Window is closed, it is by default removed from its `Application` parent object.

### Instantiating

To instantiate an `Application` object, you can use its default constructor.

### Adding a Window

To add a `Window` to an `Application` object, you use its `addWindow` member function. You may explicitly provide the type of window you want to add as a template argument, which must inherit from `Window` (the default one is `Window` itself). 

- The first parameter of the function is the name you want the window to have inside the `Application` object.

- The second parameter in a boolean value specifying whether you want the window to be initially shown.

- The following arguments are variadic, and are those that will be passed to the constructor of the specified Window constructor.

### Removing a Window

A Window can be removed both by a `std::shared_ptr` to it and by its name, using the member function overloads `removeWindow()`. Both return false if the window is not found.

### Removing a Window from inside a Window's Update Member function

To flag a Window as to be removed during the next `Application` `update()`, you pass a `std::shared_ptr` to it to `Application` member function `addWindowToRemoveList()`, which returns false if the window is not found.

### Retrieving a Window

To retrieve a Window, you can use the member function `getWindow()`, which returns a `std::shared_ptr` to the window if it's found. Otherwise, it returns nullptr.

### Updating an `Application` object

You can update an application object (and its windows) by calling its virtual `update()` member function and passing it a `std::chrono::duration` of underlying type double representing seconds.

## Window Class

The `Window` class can be used both as a `sf::RenderWindow` and a `tgui::Gui`.

### Instantiating

You can instantiate a `Window` object using its public constructor, which takes some arguments:

- A reference to the parent `Application` object.

- A string pointing to the desired `tgui::Gui` widget file (can be left empty: no file will be loaded). 

- Variadic arguments that are forwarded to the base class `sf::RenderWindow`.

If the GUI file is not found, the constructor throws a `InterfaceFileNotFound` exception.

### Updating 

The `update()` member function of the `Window` class can be overrided, and is automatically called by the window's parent `Application` object. 

### Getting a `tgui::Widget` of a specific type

You can get a widget of a specific type using the member function `getWidget`, which accepts a template argument specifying the desired type of the widget, and a function argument which stands for the widget's name.

The function returns a `std::shared_ptr` to the widget if it's found; otherwise it returns a `nullptr` (`nullptr` is also returned if the widget is found but its dynamic cast to the desired widget type fails).

### Adding ToolTip to Widget

You can add a tooltip to a widget using the member function `setWidgetToolTip()`, which accepts:

- The name of the widget.

- The text (interpreted as TGUI RichText) of the of the tooltip.

- The tooltip text size.

The function returns `false` if the widget is not found.

### Adding Error to a Widget

You can add an error text above a widget using the member function `addErrorToWidget()`:

- The first argument is the name of the widget.

- The second argument is the error rich text.

- The third argument is the error text size.

- The fourth argument is the error text vertical offset from the widget.

The function returns `false` if the widget is not found, and replaces already existing errors already associated with the widget.

### Remove Error from Widget

You remove an error from a Widget using the member function `removeErrorFromWidget()`, which accepts the widget name.

The function returns `false` if the widget is not found, and doesn't do anything if no error is present at the widget.
