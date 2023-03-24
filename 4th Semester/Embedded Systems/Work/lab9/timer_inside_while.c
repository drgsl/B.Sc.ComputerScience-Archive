#include <8051.h>

//LJMP 0006H;
//LJMP 0062H;

int main(){
    P2 = 0x55;
    P3 = 0x55;

    P3_0 = 0;
    P3_1 = 1;

int rotateState = 0;
int moveState = 0;
int rotate = 0;
int move = 0;

    while(1){
        for(int i=0;i<100;i++){
            //sleep
        }
        if(rotateState){
            rotate = 1;
            rotateState = 0;
        }
        else if(!rotateState)
        {
            rotate = 0;
            rotateState = 1;
        }

        if(moveState){
            move = 1;
            moveState = 0;
        }
        else if(!moveState)
        {
            move = 0;
            moveState = 1;
        }
        
        P1 = 0xAA;
        P2 = 0x55;
    }
}