#include "myLib.h"

void myLib_func(void)
{
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1);

}