// Inclue the M5StickCPlus library, this is required for the Stick to work
#include <M5StickCPlus.h>

// Define the pin to use as the LED
#define LED_BUILTIN 10

// Define the current acceleration values
float accX = 0.0f;
float accY = 0.0f;
float accZ = 0.0f;

// Define the maximum acceleration value
float maxZ = 0.0f;

// Boolean to store if the drop has been detected
bool isDrop = false;

void setup()
{
    // Initialize the Stick
    // This function must be called before any other M5StickCPlus functions
	M5.begin();
    // Initialize the IMU
    // This function must be called before any other IMU functions
    M5.Imu.Init();
    // Rotate the screen
    M5.Lcd.setRotation(3);
    // Fill the screen with black
    M5.Lcd.fillScreen(BLACK);
    // set the text size to 1
    M5.Lcd.setTextSize(1);
    // Set the cursor location
    M5.Lcd.setCursor(80, 15); 
    // Print the text
    M5.Lcd.println("DROP TEST");

    // Set the pin to use as the LED
    pinMode(LED_BUILTIN, OUTPUT);
    // Set the LED to HIGH 
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
    // Get the acceleration values, and save it to the variables
	M5.IMU.getAccelData(&accX, &accY, &accZ);
    // Update the maximum acceleration value
    if(accZ > maxZ) maxZ = accZ;
    // Print the acceleration values
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(30, 50);
    M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
    // Print the maximum acceleration value
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(30, 80);
    M5.Lcd.printf(" %5.2f", maxZ);
    // Update is needed to detect button presses
    M5.update();
    // If the A button is pressed...
    if(m5.BtnA.wasReleased()){
        // Reset the maximum acceleration value
        maxZ = 0.0f;
        // Reset the isDrop variable
        isDrop = false;
        // Fill the screen with black
        M5.Lcd.fillScreen(BLACK);
        // Write to the LED
        digitalWrite(LED_BUILTIN, HIGH);
    }
    // If the maximum acceleration value is greater than 5.0, and the isDrop variable is false...
    if(maxZ >= 5.0f && isDrop == false){
        // Fill the screen with red
        M5.Lcd.fillScreen(RED);
        // Set the isDrop variable to true
        isDrop = true;
    }
    // If the isDrop variable is true...
    if(isDrop) {
        // Write to the LED
        // Resulting in the LED flashing every 200ms
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
    }
}
