/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5StickC-Plus sample source code
*                          配套  M5StickC-Plus 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/m5stickc_plus
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/m5stickc_plus
*
* Describe: IMU.
* Date: 2021/9/14
*******************************************************************************
*/
#include <M5StickCPlus.h>

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float maxX = 0.0f;
float maxY = 0.0f;
float maxZ = 0.0f;

/* After M5StickC Plus is started or reset
  the program in the setUp () function will be run, and this part will only be
  run once. 在 M5StickC Plus
  启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin();             // Init M5StickC Plus.  初始化 M5StickC Plus
    M5.Imu.Init();          // Init IMU.  初始化IMU
    M5.Lcd.setRotation(3);  // Rotate the screen. 将屏幕旋转
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(80, 15);  // set the cursor location.  设置光标位置
    M5.Lcd.println("IMU TEST");
    M5.Lcd.setCursor(30, 30);
    M5.Lcd.println("  X       Y       Z");
    // PC Begin
    // Display the text for the Max Acceleration 
    M5.Lcd.setCursor(10, 80);
    M5.Lcd.println("Max Acc:");
    // PC Stop
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    // PC Begin
    // Set max value for X, Y, Z, if the value is greater than the current value
    if(accX > maxX) maxX = accX;
    if(accY > maxY) maxY = accY;
    if(accZ > maxZ) maxZ = accZ;
    // PC Stop
    

    M5.Lcd.setCursor(30, 50);
    M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);


    // PC Begin
    // Using an format string to display the value of maxX, maxY, maxZ
    M5.Lcd.setCursor(30, 80);
    M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", maxX, maxY, maxZ);

    // When the button A is pressed, clear the value of maxX, maxY, maxZ
    M5.update();
    if(M5.BtnA.wasReleased()){
      maxX = 0.0f;
      maxY = 0.0f;
      maxZ = 0.0f;
    }
    // PC Stop
    delay(100);
}
