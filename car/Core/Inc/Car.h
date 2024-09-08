#ifndef __Car_H__

#include "main.h"


#define DebugMode   1

#define LeftSide 		TIM_CHANNEL_1
#define RightSide   	TIM_CHANNEL_2
#define timHandle       htim4
#define gpioHandle      GPIOA
#define IN1             GPIO_PIN_8
#define IN2             GPIO_PIN_9
#define IN3             GPIO_PIN_10
#define IN4             GPIO_PIN_11

/*以10%的速度增减*/
/*
    CCR=CLK/PSC/ARR=100
*/
#define defaultVal         10

/*  CLK = 72MHz 
    PSC = 720-1
    ARR = 100-1
    CCR = CLK/PSC/ARR = 100
    speed use % as uints ,speed = inputNumber /100*CRR = input% * CRR
 */
#define setLeftSpeed(speed)        __HAL_TIM_SetCompare(&timHandle,LeftSide,formatSpeed(speed,0,100));
#define setRightSpeed(speed)       __HAL_TIM_SetCompare(&timHandle,RightSide,formatSpeed(speed,0,100));

/*转弯差速*/
extern uint16_t speedDiff;
extern uint16_t speedPulse;
extern uint8_t Recievecmd;


typedef enum {
    CMD_START='1',
    CMD_STOP,
    CMD_ADVANCE,
    CMD_RETREAT,
    CMD_TURN_LEFT,
    CMD_TURN_RIGHT,
		CMD_CIRCLE, 
    CMD_SPEEDUP,
    CMD_SPEEDCUT
} CMD;

typedef struct carStruct{
    CMD cmd;                          // 控制小车的命令
    void (*stop)(void);               // 指向 stop 函数的指针
    void (*advance)(void);            // 指向 advance 函数的指针
    void (*retreat)(void);            // 指向 retreat 函数的指针
    void (*turnLeft)(void);           // 指向 turnLeft 函数的指针
    void (*turnRight)(void);          // 指向 turnRight 函数的指针
    void (*control)(CMD);            // 指向control的指针
    void (*speedup)(uint16_t);
    void (*speedcut)(uint16_t);
}Car;

/*工具函数*/
void CarInit(void);
Car* getCarInstance(void);
uint16_t formatSpeed(uint16_t speed,uint16_t min,uint16_t max);
void Debug(const char *format, ...);

/* 小车控制函数*/
void stop(void);
void advance(void);
void retreat(void);
void turnLeft(void);
void turnRight(void);
void control(CMD cmd);
void speedup(uint16_t val);
void speedcut(uint16_t val);


#endif



