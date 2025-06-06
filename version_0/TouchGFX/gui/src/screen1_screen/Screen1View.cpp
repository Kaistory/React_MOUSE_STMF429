#include <gui/screen1_screen/Screen1View.hpp>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "texts/TextKeysAndLanguages.hpp"
int16_t x_touch;
int16_t y_touch;
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
    if (evt.getType() == ClickEvent::PRESSED)
    {
        // Lấy tọa độ khi nhấn xuống
    	x_touch = evt.getX();
    	y_touch = evt.getY();
    	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
        // Xử lý tọa độ ở đây
        // Ví dụ: hiển thị trên debug hoặc lưu vào biến
    }
    else if (evt.getType() == ClickEvent::RELEASED)
    {
        // Lấy tọa độ khi thả ra
    	x_touch = evt.getX();
    	y_touch = evt.getY();
    }

    // Gọi hàm cha để đảm bảo các widget khác vẫn hoạt động
    Screen1View::handleClickEvent(evt);
}
void Screen1View::handleTickEvent()
{
	uint8_t nb = 1;
    Unicode::snprintf(TextBeginBuffer, TEXTBEGIN_SIZE, "%d",  nb);
    TextBegin.setWildcard(TextBeginBuffer);
	TextBegin.invalidate();
    Screen1ViewBase::handleTickEvent();
}
