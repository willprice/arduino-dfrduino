# DFRduino
An Arduino library for controlling the DFRduino Romeo controller.

## Install
Place the DFRduino folder into the `libraries` folder inside your Arduino
installation.

## Usage
Sample sketch:
```
#include <DFRduino.h>
// Servo.h is required for DFRduino 
#include <Servo.h>


DFRduino robot;

void setup() {
    resetHeadPosition();
}

void loop() {
    nod();
}

void nod() {
    lookUp();
    lookDown();
}
void resetHeadPosition() {
    // Unfortunately my servo does not have an adjust pin.
    // 130 degrees is looking perpendicularly to the floor
    robot.setVerticalHeadPosition(130);
    robot.setVerticalHeadPosition(90);
}
void lookUp() {
    robot.setVerticalHeadPosition(50);
    waitForServoToReadPosition();
}

void lookDown() {
    robot.setVerticalHeadPosition(130);
    waitForServoToReadPosition();
}

void waitForServoToReadPosition() {
    delay(700);
}
```

### Documentation
See [willprice.org](http://willprice.org/notes/dfduino/doc)
or generate it yourself with `doxygen Doxygen` and point your web broswer
towards the index file in `html` or get the 
