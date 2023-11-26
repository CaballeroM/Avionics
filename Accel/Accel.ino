#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

//Accel Calib
const double offsetX = 0;
const double offsetY = 0;
const double offsetZ = 0;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  AccelSetup();

  delay(100);
}

void AccelSetup() {
  Serial.println("---- MPU6050 Setting Up ----");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  Serial.println("Accelerometer range set to: +-16G");

  mpu.setGyroRange(MPU6050_RANGE_500_DEG); //TODO Check if more needed
  Serial.println("Gyro range set to: +- 500 deg/s");

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); //TODO ???
  Serial.println("Filter bandwidth set to: 21 Hz");
  Serial.print("Accel Calibration X: ");
  Serial.print(offsetX);
  Serial.print(", Y: ");
  Serial.print(offsetY);
  Serial.print(", Z: ");
  Serial.println(offsetZ);
  Serial.println("---- MPU6050 Setup Complete ----");  
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Accel X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rot X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Accel Temp: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
  delay(500);
}