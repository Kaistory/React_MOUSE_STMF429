#include <gui/screen1_screen/Screen1View.hpp>
#include "usb_device.h"
#include "usbd_hid.h"
#include "stm32f4xx_hal.h"

// Đối tượng USB HID từ middleware
extern USBD_HandleTypeDef hUsbDeviceHS;

// Vị trí hiện tại của chuột
float currentX = 0;
float currentY = 0;

// Cấu trúc báo cáo HID chuột
typedef struct {
    uint8_t buttons;
    int8_t x;
    int8_t y;
    int8_t wheel;
} MouseHID_Report_t;

// Gửi báo cáo HID với delta tương đối
void SendMouseHIDUSB(float deltaX, float deltaY)
{
    MouseHID_Report_t mouseReport;

    // Giới hạn giá trị delta trong phạm vi -127 đến 127
    if (deltaX > 127) deltaX = 127;
    if (deltaX < -127) deltaX = -127;
    if (deltaY > 127) deltaY = 127;
    if (deltaY < -127) deltaY = -127;

    mouseReport.x = (int8_t)deltaX;
    mouseReport.y = (int8_t)deltaY;
    mouseReport.buttons = 0;
    mouseReport.wheel = 0;

    USBD_HID_SendReport(&hUsbDeviceHS, (uint8_t*)&mouseReport, sizeof(mouseReport));

    HAL_Delay(1); // Đảm bảo host nhận kịp gói tin
}

Screen1View::Screen1View() {}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

// Xử lý sự kiện chạm
void Screen1View::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        // Tỷ lệ từ màn hình cảm ứng 320x240 → PC 1920x1080
        float scaleX = 1920.0f / 320.0f;
        float scaleY = 1080.0f / 240.0f;

        int16_t rawX = evt.getX();
        int16_t rawY = evt.getY();

        float targetX = rawX * scaleX;
        float targetY = rawY * scaleY;

        float deltaX = targetX - currentX;
        float deltaY = targetY - currentY;

        // Gửi từng bước ±127
        while (deltaX != 0 || deltaY != 0)
        {
            float stepX = (deltaX > 127) ? 127 : (deltaX < -127) ? -127 : deltaX;
            float stepY = (deltaY > 127) ? 127 : (deltaY < -127) ? -127 : deltaY;

            SendMouseHIDUSB(stepX, stepY);

            currentX += stepX;
            currentY += stepY;
            deltaX -= stepX;
            deltaY -= stepY;
        }

        // Toggle đèn debug
        HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
        invalidate();
    }
}

void Screen1View::handleTickEvent()
{
    // Dùng nếu cần xử lý theo thời gian
}
