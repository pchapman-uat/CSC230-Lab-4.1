#include <M5StickCPlus.h>


float accX = 0.0f;
float accY = 0.0f;
float accZ = 0.0f;

float maxZ = 0.0f;
void setup()
{
	M5.begin();
    M5.Imu.Init();
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(80, 15); 
    M5.Lcd.println("DROP TEST");
}

void loop()
{
	M5.IMU.getAccelData(&accX, &accY, &accZ);
    if(accZ > maxZ) maxZ = accZ;
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(30, 50);
    M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);

    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(30, 80);
    M5.Lcd.printf(" %5.2f", maxZ);

}
