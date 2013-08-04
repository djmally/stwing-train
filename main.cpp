#include "kiki.h"


bool stop(){ //Stop
    MotorL.speed(0.0f);
    MotorR.speed(0.0f);
    return stopped = true;
}

void forwardDrive(){ //Drive forward
    MotorL.speed(-1.0f); //CW
    MotorR.speed(1.0f); //CCW
}

void reverseDrive(){ //Drive reverse
    MotorL.speed(1.0f); //CCW
    MotorR.speed(-1.0f); //CW
}

void turnLeft(){ //Turn left
    MotorL.speed(0.0f);
    MotorR.speed(-1.0f); //CCW
}

void turnRight(){ //Turn right
    MotorL.speed(1.0f); //CW
    MotorR.speed(0.0f);
}

uint16_t* getPhotocellData(){
    uint16_t resistances[] = {photocellLL.read_u16(), photocellLC.read_u16(), photocellCC.read_u16(), photocellRC.read_u16(), photocellRR.read_u16()};
    uint16_t* resistances_ptr = resistances;
    return resistances_ptr;
}

uint16_t getPhotocellMax(){
    uint16_t* resistances_ptr = getPhotocellData();
    uint16_t max_res = 0;
    uint16_t dir = 0;
    for(int i = 0; i < 5; i += 1){ //Iterate through the photocell data and determine where the line is
        if(*resistances_ptr > max_res){
            max_res = *resistances_ptr;
            dir = i; //Index in the array of the "strongest" direction
        }
   }
   return dir;
}

uint16_t getCheckData(){
    return photocellCheck.read_u16();
}

void setRoomNum(uint16_t input_room[6]){
    for(int i = 0; i < 6; i += 1){
        room_num[i] = input_room[i];
    }
}

bool checkRoomNum(){
    uint16_t checkData = getCheckData();
    if(!checkData){
        return false; //If the check bit is not high, there's no room
    } else{
        uint16_t* resistances_ptr = getPhotocellData();
        for(int i = 0; i < 5; i += 1){
            if(*resistances_ptr != room_num[i+1]){
                return false;
            }
            resistances_ptr += 1;
        }    
    }
    return true;
}

int main() {
    while(stopped == true){
        stop();
        /*if(buttonPin == 1){ //currently undefined
            stopped = false;
        }
        else if(LSpeed == 0.0 && RSpeed == 0.0){
            stopped = true;
        }
        else{
            stopped = true;
        }*/
    }
    
    while(stopped == false){
        uint16_t dir = getPhotocellMax(); //Poll the photocells LIGHT COLOUR == LOW RESISTANCE (can be verified with KIKI_Device_test and a simple voltage divider)
        uint16_t check_bit = getCheckData(); //Poll the 6th check photocell
        switch(dir){
            case(0): //Line is on the far left
                while(dir < 2){
                    dir = getPhotocellMax();
                    turnLeft();
                }
                break;
            case(1): //Left center
                while(dir < 2){
                    dir = getPhotocellMax();
                    turnLeft();
                }
                break;
            case(2): //Center
                forwardDrive();
                break;
            case(3): //Right center
                while(dir > 2){
                    dir = getPhotocellMax();
                    turnRight();
                }
                break;
            case(4): //Far right
                while(dir > 2){
                    dir = getPhotocellMax();
                    turnRight();
                }
                break;
            default:
                stop();
                break;
        }
    }  
    return 0;
}
