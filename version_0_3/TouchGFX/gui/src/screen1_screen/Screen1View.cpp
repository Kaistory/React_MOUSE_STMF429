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
        float scaleX = 1920.0f * 2 / 320.0f;
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
        currentCircle = 0;
		circle4.moveTo(evt.getX() - 20, evt.getY() - 20);
		circle4.invalidate();
		circle3.moveTo(evt.getX() - 20, evt.getY() - 20);
		circle3.invalidate();
		circle2.moveTo(evt.getX() - 20, evt.getY() - 20);
		circle2.invalidate();
		circle1.moveTo(evt.getX() - 20, evt.getY() - 20);
		circle1.invalidate();
        // Toggle đèn debug
        HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
        invalidate();
    }
}

void Screen1View::handleTickEvent()
{
	tickCounter++;

	    if (tickCounter >= TICKS_PER_SECOND) // Mỗi giây
	    {
	        tickCounter = 0;
	        	switch(currentCircle)
	        	{
	        		case 0:
	        			circle4.setVisible(true);
	        			circle4.invalidate();
	        			break;
	        		case 1:
	        			circle4.setVisible(false);
	        			circle4.invalidate();
	        			circle3.setVisible(true);
	        			circle3.invalidate();
	        			break;
	        		case 2:
	        			circle3.setVisible(false);
	        			circle3.invalidate();
	        			circle2.setVisible(true);
	        			circle2.invalidate();
	        			break;
	        		case 3:
	        			circle2.setVisible(false);
	        			circle2.invalidate();
	        			circle1.setVisible(true);
	        			circle1.invalidate();
	        			break;
	        		case 4:
	        			circle1.setVisible(false);
						circle1.invalidate();
	        	}
	        currentCircle++;
	    }
}
