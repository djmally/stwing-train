#include "mbed.h"
#include "stdint.h"
#include "Motor.h"

//Motors
Motor MotorL(p21, p6, p5); //Pin assignments are PWM, forward, reverse; CW is forward, CCW is reverse; controls left motor
Motor MotorR(p22, p8, p7); //Pin assignments are PWM, forward, reverse; CCW is forward, CW is reverse; controls right motor

//Misc Values
float LSpeed = 0.0; //speed of left motor
float RSpeed = 0.0; //speed of right motor

uint16_t room_num[] = {1, 0, 0, 0, 0, 0};

bool stopped = true;

//Line tracking photoresistor
AnalogIn photocellLL(p15); //Photocell on pin 15, can be read as a [0.0-1.0] float with read() or as an unsigned, hex short [0x0-0xFFFF] with read_u16()
AnalogIn photocellLC(p16); //""
AnalogIn photocellCC(p17); //""
AnalogIn photocellRC(p18); //""
AnalogIn photocellRR(p19); //""
AnalogIn photocellCheck(p20); //""

//Forward declaration of functions
bool stop();

void forwardDrive();

void reverseDrive();

void turnLeft();

void turnRight();

uint16_t* getPhotocellData();

uint16_t getPhotocellMax();
