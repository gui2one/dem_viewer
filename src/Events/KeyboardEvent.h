#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H
#include "Event.h"

class KeyboardEvent : public Event
{
public:
    KeyboardEvent() {}
    virtual ~KeyboardEvent() {}

    EVENT_CATEGORY_TYPE(EventCategoryKeyboard)

private:
};

class KeyPressEvent : public KeyboardEvent
{
public:
    int m_Keycode;
    int m_Scancode;
    uint32_t m_RepeatCount;

public:
    KeyPressEvent(int keycode, int scancode, uint32_t repeat_count)
        : m_Keycode(keycode), m_Scancode(scancode), m_RepeatCount(repeat_count) {}

    EVENT_CLASS_TYPE(KeyPress)
};

class KeyReleaseEvent : public KeyboardEvent
{
public:
    int m_Keycode;
    int m_Scancode;

public:
    KeyReleaseEvent(int keycode, int scancode)
        : m_Keycode(keycode), m_Scancode(scancode) {}

    EVENT_CLASS_TYPE(KeyRelease)
};

#endif /* KEYBOARD_EVENT_H */