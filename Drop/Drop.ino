#include <M5StickCPlus.h>

#define LED_BUILTIN 10

float accX = 0.0f;
float accY = 0.0f;
float accZ = 0.0f;

float maxZ = 0.0f;


bool isDrop = false;
float blinkCount = 0;
void setup()
{
	M5.begin();
    M5.Imu.Init();
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(80, 15); 
    M5.Lcd.println("DROP TEST");

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
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

    M5.update();
    if(m5.BtnA.wasReleased()){
        maxZ = 0.0f;
        isDrop = false;
        M5.Lcd.fillScreen(BLACK);
        digitalWrite(LED_BUILTIN, HIGH);
    }

    if(maxZ >= 5.0f && isDrop == false){
        M5.Lcd.fillScreen(RED);
        isDrop = true;
    }

    if(isDrop) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
    }
}
