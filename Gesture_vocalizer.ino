#include <SoftwareSerial.h>
#include <Wire.h>

#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;
bool gestureInProgress = false;
int dt = 0;

// Index finger flex sensor pin
#define INDEX_FLEX_PIN A0
#define MIDDLE_FLEX_PIN A1
#define RING_FLEX_PIN A2
#define LITTLE_FLEX_PIN A3

// Flex sensor threshold
#define INDEX_THRESHOLD 810
#define MIDDLE_THRESHOLD 780
#define RING_THRESHOLD 850
#define LITTLE_THRESHOLD 880

SoftwareSerial BTSerial(10, 11); // RX | TX
void setup() {
  // Start I2C communication
 // Wire.begin(A4, A5);

  // Initialize MPU6050 accelerometer
  mpu.initialize();
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
  mpu.setDLPFMode(MPU6050_DLPF_BW_20);

  // Start serial communication
  Serial.begin(9600);
  BTSerial.begin(9600);  
}

void loop() {
  // Read accelerometer data
  

  // Read index finger flex sensor value
  int index_flex = analogRead(INDEX_FLEX_PIN);
  int middle_flex = analogRead(MIDDLE_FLEX_PIN);
  int ring_flex = analogRead(RING_FLEX_PIN);
  int little_flex = analogRead(LITTLE_FLEX_PIN);  
  
  // Check if index finger is bent to threshold
  if (index_flex >= INDEX_THRESHOLD && middle_flex < MIDDLE_THRESHOLD && ring_flex < RING_THRESHOLD && little_flex < LITTLE_THRESHOLD) {
    // Output "I smell fire" message
    Serial.println("It's a Cat");
    BTSerial.println("It's a Cat");    
  }
  if (middle_flex >= MIDDLE_THRESHOLD && index_flex < INDEX_THRESHOLD && ring_flex < RING_THRESHOLD && little_flex < LITTLE_THRESHOLD) {
    // Output "I smell fire" message
    Serial.println("Please Help me");
    BTSerial.println("Please Help me");    
  }
  if (ring_flex >= RING_THRESHOLD && middle_flex < MIDDLE_THRESHOLD && index_flex < INDEX_THRESHOLD && little_flex < LITTLE_THRESHOLD) {
    // Output "I smell fire" message
    Serial.println("Can I have a glass of water please");
    BTSerial.println("Can I have a glass of water please");    
  }
  if (little_flex >= LITTLE_THRESHOLD && middle_flex < MIDDLE_THRESHOLD && ring_flex < RING_THRESHOLD && index_flex < INDEX_THRESHOLD) {
    // Output "I smell fire" message
    Serial.println("Can I use the washroom");
    BTSerial.println("Can I use the washroom");    
  }    
  if (middle_flex >= MIDDLE_THRESHOLD && index_flex >= INDEX_THRESHOLD && ring_flex < RING_THRESHOLD && little_flex < LITTLE_THRESHOLD) {
    // Output "I smell fire" message
    Serial.println("It's fantastic");
    BTSerial.println("It's fantastic");    
  }
  
  if (middle_flex >= MIDDLE_THRESHOLD && index_flex >= INDEX_THRESHOLD && ring_flex >= RING_THRESHOLD && little_flex >= LITTLE_THRESHOLD) {
    // Output "I smell fire" message
    if (!gestureInProgress && ax>0) {
    gestureInProgress = true ;
  }
  else  if (gestureInProgress && ax<0) {
      Serial.println("Yes");
      BTSerial.println("Yes");       
      gestureInProgress = false;
    }
  }
  if (middle_flex < MIDDLE_THRESHOLD && index_flex < INDEX_THRESHOLD && ring_flex < RING_THRESHOLD && little_flex < LITTLE_THRESHOLD) {
    // Output "I smell fire" message
    if (!gestureInProgress && ay>0 && ax>15000) {
    gestureInProgress = true ;
  }
  else  if (gestureInProgress && ay>0 && ax>15000) {
      Serial.println("Hello");
      BTSerial.println("Hello");       
      gestureInProgress = false;
    }
  }
  
  if (middle_flex < MIDDLE_THRESHOLD && index_flex < INDEX_THRESHOLD && ring_flex < RING_THRESHOLD && little_flex < LITTLE_THRESHOLD) {
    // Output "I smell fire" message
    if (!gestureInProgress && az>0 && ax>12000) {
    gestureInProgress = true ;
  }
  else  if (gestureInProgress && az>0 && ax<10000) {
      Serial.println("thank u");
      BTSerial.println("Thank u");       
      gestureInProgress = false;
    }
  }
  if (little_flex >= LITTLE_THRESHOLD && ring_flex >= RING_THRESHOLD && middle_flex < MIDDLE_THRESHOLD && index_flex < INDEX_THRESHOLD) {
    // Output "I smell fire" message
    Serial.println("Peace");
    BTSerial.println("Peace");    
  }  
  if (middle_flex >= MIDDLE_THRESHOLD && ring_flex >= RING_THRESHOLD && index_flex < INDEX_THRESHOLD && little_flex < LITTLE_THRESHOLD) {
    // Output "I smell fire" message
    Serial.println("I love you");
    BTSerial.println("I love you");    
  }
   if (middle_flex >= MIDDLE_THRESHOLD && ring_flex >= RING_THRESHOLD && index_flex < INDEX_THRESHOLD && little_flex >= LITTLE_THRESHOLD) {
    // Output "I smell fire" message
    Serial.println("I am hungry");
    BTSerial.println("I am hungry");    
  }  
  if (index_flex >= INDEX_THRESHOLD && little_flex >= LITTLE_THRESHOLD && ring_flex >= RING_THRESHOLD && middle_flex < MIDDLE_THRESHOLD) {
    // Output "I smell fire" message
    Serial.println("Please leave me alone");
    BTSerial.println("Please leave me alone");    
  }   
   if (index_flex >= INDEX_THRESHOLD && little_flex < LITTLE_THRESHOLD && ring_flex >= RING_THRESHOLD && middle_flex >= MIDDLE_THRESHOLD) {
    // Output "I smell fire" message
    Serial.println("I want to go to the washroom");
    BTSerial.println("I want to go to the washroom");    
  }     
  // Output accelerometer data and flex sensor value
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  
  Serial.print("Accel X: ");
  Serial.print(ax);
  Serial.print("\tAccel Y: ");
  Serial.print(ay);
  Serial.print("\tAccel Z: ");
  Serial.print(az);
  Serial.print("\tIndex Flex: ");
  Serial.print(index_flex);
  Serial.print("\tMiddle Flex: ");
  Serial.print(middle_flex);
  Serial.print("\tRing Flex: ");
  Serial.print(ring_flex);
  Serial.print("\tLittle Flex: ");
  Serial.print(little_flex); 
  Serial.println("");
  

  BTSerial.println("");
  // Wait a short period before repeating
  
  delay(2000);
}