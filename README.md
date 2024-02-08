# App Library

This *app* library is based off Texus' *TGUI*, an SFML-based GUI library.

This library is intented to make managing multiple and interacting windows easier.

## Usage

This library exports the dependency `app` via Meson, so that you can add it as dependency in your project.

The header you should include to use this library is `app.hpp`, which defines its entities inside the namespace `app`.

## Application Class

The `Application` class is the class which manages windows. Windows, as specified by the *concept* `UpdatableWindow`, are class types derived from this library's `Window` class, which in turns derives from SFML `RenderWindow` and TGUI `Gui`.

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

