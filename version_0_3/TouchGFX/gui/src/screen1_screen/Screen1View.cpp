#include <gui/screen1_screen/Screen1View.hpp>
#include "usb_device.h"
#include "usbd_hid.h"
#include "stm32f4xx_hal.h"
extern USBD_HandleTypeDef hUsbDeviceHS;
int16_t curentX = 0;
int16_t curentY = 0;
// Mouse HID Report Structure
typedef struct {
    uint8_t buttons;
    int8_t x;
    int8_t y;
    int8_t wheel;
} MouseHID_Report_t;

void SendMouseHIDUSB(int16_t x, int16_t y)
{
    MouseHID_Report_t mouseReport;

    // Convert screen coordinates to relative mouse movement
    // Scale down the movement for smoother control
    mouseReport.x = (int8_t)(x);
    mouseReport.y = (int8_t)(y);
    mouseReport.buttons = 0;
    mouseReport.wheel = 0;

    // Send HID report
    USBD_HID_SendReport(&hUsbDeviceHS, (uint8_t*)&mouseReport, sizeof(mouseReport));
}

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

        // Send mouse HID event
    	if(curentX != evt.getX() || curentY != evt.getY() )
    		{
    				SendMouseHIDUSB(evt.getX(),evt.getY()); // Left click
    			curentX = evt.getX();
    			curentY = evt.getY();
    		}
    	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
        invalidate();
    } else if(evt.getType() == ClickEvent::RELEASED) {
        // Send mouse release

//        SendMouseHID(0, 0);
    }
}
void Screen1View::handleTickEvent(){
//	SendMouseHIDUSB(5,5);
}
