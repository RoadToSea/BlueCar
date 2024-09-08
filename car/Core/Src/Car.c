#include "Car.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

uint16_t speedDiff=0;
uint16_t speedPulse=0;
uint8_t Recievecmd=CMD_STOP;
uint16_t defaultVal = 10;


static Car* car;

static void carFactory(void)
{
    if(car==NULL)
    { 
      car = (Car*)malloc(sizeof(Car));
      car->cmd = CMD_STOP;
      car->advance=advance;
      car->retreat=retreat;
      car->turnLeft=turnLeft;
      car->turnRight=turnRight; 
      car->control= control;
      car->speedup=speedup;
      car->speedcut = speedcut;
    }
}

Car *getCarInstance(void)
{
    carFactory();
    return car;
}

void CarInit(void)
{
	speedPulse = 20;
	speedDiff = 20;
  HAL_TIM_Base_Start(&timHandle);
	HAL_TIM_PWM_Start(&timHandle,LeftSide);
	HAL_TIM_PWM_Start(&timHandle,RightSide );
	
	setLeftSpeed(speedPulse);
	setRightSpeed(speedPulse);
	
	HAL_UART_Init(&huart2);
	UART_Start_Receive_IT(&huart2,&Recievecmd,1);
  Debug("car init OK");
}

uint16_t formatSpeed(uint16_t speed,uint16_t min,uint16_t max)
{
  if(speed>max)
    speed=max;
  else if(speed<min)
    speed= min;
  return speed;
}

void stop(void)
{
//  uint16_t decrease = speedPulse/20;
//  for(int i=0;i<20;i++)
//  {
//    setLeftSpeed(speedPulse-decrease*i);
//    setRightSpeed(speedPulse-decrease*i);
//    HAL_Delay(10);
//  }
  HAL_GPIO_WritePin(gpioHandle,IN1,0);
	HAL_GPIO_WritePin(gpioHandle,IN2,0);
	HAL_GPIO_WritePin(gpioHandle,IN3,0);
	HAL_GPIO_WritePin(gpioHandle,IN4,0);  
  setLeftSpeed(speedPulse);
  setRightSpeed(speedPulse);
}

void advance(void)
{
//  uint16_t increase = speedPulse/20;
//  for(int i=0;i<20;i++)
//  {
//    setLeftSpeed(increase*i);
//    setRightSpeed(increase*i);
//    HAL_Delay(10);
//  }
  HAL_GPIO_WritePin(gpioHandle,IN1,1);
	HAL_GPIO_WritePin(gpioHandle,IN2,0);
	HAL_GPIO_WritePin(gpioHandle,IN3,1);
	HAL_GPIO_WritePin(gpioHandle,IN4,0); 
  setLeftSpeed(speedPulse);
  setRightSpeed(speedPulse);
}

void retreat(void)
{
  HAL_GPIO_WritePin(gpioHandle,IN1,0);
	HAL_GPIO_WritePin(gpioHandle,IN2,1);
	HAL_GPIO_WritePin(gpioHandle,IN3,0);
	HAL_GPIO_WritePin(gpioHandle,IN4,1); 
	setLeftSpeed(speedPulse);
  setRightSpeed(speedPulse);
}

void turnLeft(void)
{
  setLeftSpeed(speedPulse);
  setRightSpeed(speedPulse+speedDiff);
}

void turnRight(void)
{
  setRightSpeed(speedPulse);
  setLeftSpeed(speedPulse+speedDiff);
}

void circle(void)
{
	HAL_GPIO_WritePin(gpioHandle,IN1,1);
	HAL_GPIO_WritePin(gpioHandle,IN2,0);
	HAL_GPIO_WritePin(gpioHandle,IN3,0);
	HAL_GPIO_WritePin(gpioHandle,IN4,1); 
}

void speedup(uint16_t val)
{
	speedPulse+=val;
  setLeftSpeed(speedPulse);
  setRightSpeed(speedPulse);
}

void speedcut(uint16_t val)
{
	speedPulse-=val;
  setLeftSpeed(speedPulse);
  setRightSpeed(speedPulse);
}


void control(CMD cmd)
{
  switch (cmd)
  {
  case CMD_START:
    CarInit();
    break;
  case CMD_STOP:
    stop();
    break;
  case CMD_ADVANCE:
    advance();
    break;
  case CMD_RETREAT:
    retreat();
    break;
  case CMD_TURN_LEFT:
    turnLeft();
    break;
  case CMD_TURN_RIGHT:
    turnRight();
    break;
	case CMD_CIRCLE:
		circle();
    break;
  case CMD_SPEEDUP:
    speedup(defaultVal);
    break;
  case CMD_SPEEDCUT:
    speedcut(defaultVal);
    break;
	
  }
	flag=0;	
}


void Debug(const char *format, ...)
{
  #ifdef DebugMode
    va_list args;                   // 定义一个 va_list 类型的变量，用于存储可变参数
    va_start(args, format);         // 初始化 va_list，将其指向 format 参数后的第一个可变参数
    vprintf(format, args);          // 使用 vprintf 函数将参数输出到标准输出，格式同 printf
    va_end(args);                   // 结束 va_list 的处理
  #endif
}