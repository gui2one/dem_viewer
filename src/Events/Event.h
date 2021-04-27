#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <core.h>
#include <pch.h>

#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType GetStaticType() { return EventType::type; }                \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; }

#define EVENT_CATEGORY_TYPE(category) \
    virtual int GetCategoryFlags() const override { return category; }

enum class EventType
{
    None = 0,
    KeyPress,
    KeyRelease,
    MouseMove,
    MousePress,
    MouseRelease,
    MouseScroll,
    WindowResize,
    WindowClose
};

enum EventCategoryFlag
{
    None = 0,
    EventCategoryKeyboard = BIT(0),
    EventCategoryMouse = BIT(1),
    EventCategoryWindow = BIT(2)
};

class Event
{

public:
    // std::function<void(Event&)> m_Callback;
    bool m_Handled = false;

public:
    virtual ~Event() = default;

    virtual EventType GetEventType() const = 0;
    virtual const char *GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;

private:
};

class Dispatcher
{
public:
    Event &m_Event;

public:
    Dispatcher(Event &e)
        : m_Event(e)
    {
    }

    template <typename T, typename F>
    bool dispatch(const F &fn)
    {

        if (m_Event.GetEventType() == T::GetStaticType())
        {

            m_Event.m_Handled |= fn(static_cast<T &>(m_Event));
            return true;
        }
        return false;
    }

private:
};

#endif /* EVENT_H */