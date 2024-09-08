#ifndef __Car_H__

#include "main.h"

#define LeftSide 		TIM_CHANNEL_1
#define RightSide   	TIM_CHANNEL_2
#define timHandle       htim4
#define gpioHandle      GPIOA
#define IN1             GPIO_PIN_8
#define IN2             GPIO_PIN_9
#define IN3             GPIO_PIN_10
#define IN4             GPIO_PIN_11

/*  CLK = 72MHz 
    PSC = 72-1
    ARR = 1000-1
    CRR = CLK/PSC/ARR = 1000
    speed use % as uints ,speed = inputNumber /100*CRR = input% * CRR
 */
#define setLeftSpeed(speed)        __HAL_TIM_SetCompare(&timHandle,LeftSide,10*speed);
#define setRightSpeed(speed)       __HAL_TIM_SetCompare(&timHandle,RightSide,10*speed);

extern uint16_t speedDiff;
extern uint16_t speedPulse;
extern uint8_t Recievecmd;


typedef enum {
    CMD_START,
    CMD_STOP,
    CMD_ADVANCE,
    CMD_RETREAT,
    CMD_TURN_LEFT,
    CMD_TURN_RIGHT,
		CMD_CIRCLE
} CMD;

typedef struct carStruct{
    CMD cmd;                          // 控制小车的命令
    void (*stop)(void);               // 指向 stop 函数的指针
    void (*advance)(void);            // 指向 advance 函数的指针
    void (*retreat)(void);            // 指向 retreat 函数的指针
    void (*turnLeft)(void);           // 指向 turnLeft 函数的指针
    void (*turnRight)(void);          // 指向 turnRight 函数的指针
    void (*control)(CMD);            //只想control的指针
}Car;


 
Car* getCarInstance(void);
void CarInit(void);

/* 小车控制函数*/
void stop(void);
void advance(void);
void retreat(void);
void turnLeft(void);
void turnRight(void);
void control(CMD cmd);



#endif



