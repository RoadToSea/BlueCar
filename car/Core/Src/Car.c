#include "Car.h"
#include <stdlib.h>
#include <stdio.h>

uint16_t speedDiff=0;
uint16_t speedPulse=0;
uint8_t Recievecmd=CMD_STOP;
static Car* car;

static void carFactory(void)
{
    if(car==NULL)
    { 
      car = (Car*)malloc(sizeof(Car));
      car->advance=advance;
      car->retreat=retreat;
      car->turnLeft=turnLeft;
      car->turnRight=turnRight; 
    }
}

Car *getCarInstance(void)
{
    carFactory();
    return car;
}

void CarInit(void)
{
	speedPulse = 500;
  HAL_TIM_Base_Start(&timHandle);
	HAL_TIM_PWM_Start(&timHandle,LeftSide);
	HAL_TIM_PWM_Start(&timHandle,RightSide );
	
	setLeftSpeed(speedPulse);
	setRightSpeed(speedPulse);
	
	HAL_UART_Init(&huart2);
	UART_Start_Receive_IT(&huart2,&Recievecmd,1);
  printf("car init OK");
}

void stop(void)
{
  HAL_GPIO_WritePin(gpioHandle,IN1,0);
	HAL_GPIO_WritePin(gpioHandle,IN2,0);
	HAL_GPIO_WritePin(gpioHandle,IN3,0);
	HAL_GPIO_WritePin(gpioHandle,IN4,0);
}

void advance(void)
{
  HAL_GPIO_WritePin(gpioHandle,IN1,1);
	HAL_GPIO_WritePin(gpioHandle,IN2,0);
	HAL_GPIO_WritePin(gpioHandle,IN3,1);
	HAL_GPIO_WritePin(gpioHandle,IN4,0); 
}

void retreat(void)
{
  HAL_GPIO_WritePin(gpioHandle,IN1,0);
	HAL_GPIO_WritePin(gpioHandle,IN2,1);
	HAL_GPIO_WritePin(gpioHandle,IN3,0);
	HAL_GPIO_WritePin(gpioHandle,IN4,1); 
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

