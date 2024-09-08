#include "Control.h"
#include "Car.h"

void BTControl(void)
{
	
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart2)
	{
        Car* car = getCarInstance();
       switch (Recievecmd) {
        case '1':
            car->cmd = CMD_ADVANCE;
            break;
        case '2':
            car->cmd = CMD_RETREAT;
            break;
        case '3':
            car->cmd = CMD_TURN_LEFT;
            break;
        case '4':
            car->cmd = CMD_TURN_RIGHT;
            break;
        case '5':
            car->cmd = CMD_START;
            break;
        case '6':
            car->cmd = CMD_STOP;
            break;
        case '7':
            car->cmd = CMD_CIRCLE;
            break;
        case '8':
            car->cmd = CMD_SPEEDUP;
            break;
        case '9':
            car->cmd = CMD_SPEEDCUT;
            break;
    }
			 flag=1;
		Debug("%d",speedPulse);
	}
	UART_Start_Receive_IT(&huart2,&Recievecmd,1);
}
