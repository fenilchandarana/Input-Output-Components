#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"

void setup()
{
  Config_Init();
  LCD_Init();
  LCD_SetBacklight(1000);  // Max backlight (0–1000)

  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);  // width, height, rotation, bg color
  Paint_Clear(WHITE);
  Paint_SetRotate(0);  // Try 0, 1, 2, or 3 if orientation is wrong

  // ✅ Display test text
  Paint_DrawString_EN(30, 40, "Hello World!", &Font24, BLUE, WHITE);
}

void loop() {
}
