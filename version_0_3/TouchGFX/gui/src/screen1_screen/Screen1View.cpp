#include <gui/screen1_screen/Screen1View.hpp>
extern void SendMouseHID(int16_t x, int16_t y);
Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleClickEvent(const ClickEvent& evt)
{
    if(evt.getType() == ClickEvent::PRESSED) {
        // Add touch point for animation
        AddTouchPoint(evt.getX(), evt.getY());

        // Send mouse HID event
        SendMouseHID(evt.getX(), evt.getY()); // Left click

        invalidate();
    } else if(evt.getType() == ClickEvent::RELEASED) {
        // Send mouse release
        SendMouseHID(0, 0);
    }
}
