//
// Created by Ukua on 2023/3/1.
//

#include "iic.h"

void WriteSCL(GPIO_PinState state){
    HAL_GPIO_WritePin(SCL_PORT,SCL_PIN,state);
    HAL_Delay(1);
}

void WriteSDA(GPIO_PinState state){
    HAL_GPIO_WritePin(SDA_PORT,SDA_PIN,state);
    HAL_Delay(1);
}

void SendBit(uint8_t bit){
    if(bit){
        WriteSDA(GPIO_PIN_SET);
        WriteSCL(GPIO_PIN_SET);
        WriteSCL(GPIO_PIN_RESET);
    }else{
        WriteSDA(GPIO_PIN_RESET);
        WriteSCL(GPIO_PIN_SET);
        WriteSCL(GPIO_PIN_RESET);
    }
}

void SendAck(GPIO_PinState AckBit)
{
    WriteSDA(AckBit);
    WriteSCL(GPIO_PIN_SET);
    WriteSCL(GPIO_PIN_RESET);
}

GPIO_PinState ReceiveAck()
{
    GPIO_PinState AckBit;
    WriteSDA(GPIO_PIN_SET);
    WriteSCL(GPIO_PIN_SET);
    AckBit = HAL_GPIO_ReadPin(SDA_PORT,SDA_PIN);
    WriteSCL(GPIO_PIN_RESET);
    return AckBit;
}

void SendByte(uint8_t byte){
    for(int i=7;i>=0;i--){
        SendBit(byte & (1<<i));
    }
}

void iic_start(){

    WriteSDA(GPIO_PIN_SET);
    WriteSCL(GPIO_PIN_SET);
    WriteSDA(GPIO_PIN_RESET);

}

