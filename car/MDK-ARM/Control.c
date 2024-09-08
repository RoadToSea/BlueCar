#include "Control.h"
#include "Car.h"

void BTControl(void)
{
	
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart2)
	{
		printf("%d",Recievecmd);
	}
	UART_Start_Receive_IT(&huart2,&Recievecmd,1);
}
