# RISC_V-SECURITY_ALARM_SYSTEM


In this project, we have designed Laser Light Security System Using RISCV with Alarm with the application of Laser Diode Module KY-008. The project idea revolves around creating a security system. Whenever any object will obstruct the LASER ray the buzzer alarm will start ringing.

This project can be implemented anywhere, not only buildings or premises but many precious things like jewelry, diamonds, precious antique items in the museum, etc many other things are also secured using such an invisible LASER beam. Many people secure their home, office, shops, warehouses, etc with the LASER beam security system.


# C Code 

```

int laserPin;
int sensorPin;
int buttonPin;
int buzzerPin;

int laserThreshold=100;

int alarmState = 0; // Define alarmState as a bit of P1

unsigned int startTime = 0;
unsigned int sensorValue = 0;

void main() {
    laserPin = 0;  // Configure laserPin as output
    buzzerPin = 0; // Configure buzzerPin as output

    buttonPin = 1; // Enable the pull-up resistor for buttonPin
    alarmState = 0; // Initialize alarmState as 0

    while (1) {
        switch (alarmState) {
            case 0:
                if (startTime == 0) {
                    startTime = 1; // Start the 1-second timer
                    laserPin = 1;
                } else if (startTime < 1000) {
                    // Increment the timer
                    startTime++;
                } else {
                    sensorValue = sensorPin; // Read the sensor (assuming it's an analog sensor)
                    // You may need to use an ADC to read the analog sensor value

                    if (sensorValue > laserThreshold) {
                        alarmState = 1;
                    }
                    laserPin = 0;
                    startTime = 0; // Reset the timer
                }
                break;
            
            case 1:
                // Activate the buzzer (you may need to implement a function to generate tone)
                // ...
                if (!buttonPin) {
                    alarmState = 0;
                    // Turn off the buzzer (you may need to implement a function to stop the tone)
                    // ...
                }
                break;
        }
    }
}
```
