Test Case 1: Verify LCD Initialisation
[Making sure the Initialisation of the LCD is done correctly and displays the default interface (values of the sensor and its limits)]

#Arrange 
Power from the system
Connect devices eg. LCD, buttons

#Act
Observe the LCD when system starts

#Assert
LCD displays the default text
No random characters appear

Test Case 2: Verify Sensor Redaing displays
[Confirm the ADC correctly reads the current sensor value and updates it on the LCD]

#Arrange
Connect the temprature sensor to an ADC input
Set a known input such as 20 degrees C

#Act
Observe the LCD and its results

#Assert
LCD displays the swet temprature 20 degrees C (+- 1)

Test Case 3: Verify Button Function for High Limit
[Verify that pressing the "high limit" button increases the limit value]

#Arrange
Current High limit = 30 degrees 

#Act
Press High limit button twice

#Assert
High Limit displayed changes to 32 degrees

Test Case 4: Verify Button Function for Low Limit
[Verify that pressing the "Low limit" button decreases the limit value]

#Arrange
Current Low limit = 15 degrees 

#Act
Press Low limit button twice

#Assert
Low Limit displayed changes to 13 degrees

Test Case 5: Limits cahnge persistance
[Verify that the low limit and high limits remain after power interruptions and sensor updates] 

#Arrange
Set low limit = 20 degrees, set high limit = 30 degrees
Power cycle the system

#Act
Reboot and observe the LCD

#Assert
Same limits still displayed

Test Case 6: Verify Alert above high limit
[Confirm the LED and Buzzer activate when limit is surpassed]

#Arrange
Set high limit = 30 degrees
Simulate temprature 35 degrees 

#Act
Observe buzzer and LED

#Assert
LED ansd Buzzer turn on

Test Case 7: Verify Alert below low limit
[Confirm the LED and Buzzer activate when limit is surpassed]

#Arrange
Set low limit = 20 degrees
Simulate temprature 15 degrees 

#Act
Observe buzzer and LED

#Assert
LED ansd Buzzer turn on

Test Case 8: Verify deactivation of Alertion within Limits
[Ensures alert clears automatically when temprature is within limits]

#Arrange
Low limit = 20 degrees, High Limit = 30
Sensor set initially at 35

#Act
Reduce the temprature to 25 degrees

#Assert
LED and buzzer turn off
LCD displays normally

Test Case 9: Button Debouncing Handling
[Verify limit buttons do not register multiple increments or decrements]

#Arrange
High limit =  30 degrees

#Act
Press "High limit" button briefly once

#Assert
High limit only increments by +1 

Test Case 10: HMI Response Time
[Check the delay between a sensor change and LCD update]

#Arrange
Low limit = 20 degrees, High limit = 30 degrees
Change sensor input from 25 to 35 degrees

#Act
Measure time difference between input change and Alert activation

#Assert
Response time should be below a second