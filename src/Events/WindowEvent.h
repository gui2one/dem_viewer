#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

#include "Event.h"

class WindowEvent : public Event
{
public:
    WindowEvent() {}
    virtual ~WindowEvent(){};

    EVENT_CATEGORY_TYPE(EventCategoryMouse)

private:
};

class WindowResizeEvent : public WindowEvent
{
public:
    int m_Width;
    int m_Height;

public:
    WindowResizeEvent(int width, int height)
        : m_Width(width), m_Height(height)
    {
    }

    EVENT_CLASS_TYPE(WindowResize)
private:
};

class WindowCloseEvent : public WindowEvent
{
public:
    WindowCloseEvent()
    {
    }

    EVENT_CLASS_TYPE(WindowClose)
private:
};

class WindowDropEvent : public WindowEvent
{
public:
    std::vector<std::string> m_dropPaths;

public:
    WindowDropEvent(std::vector<std::string> str_paths)
        : m_dropPaths(str_paths)
    {
    }

    EVENT_CLASS_TYPE(WindowDrop)
private:
};
#endif /* WINDOW_EVENT_H */