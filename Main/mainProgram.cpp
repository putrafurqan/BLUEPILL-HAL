#include <mainProgram.h>
#include <../../KRAI_HAL_library/ledKRAI/led.h>
#include <../../KRAI_HAL_library/Ticker/Ticker.h>
#include <../../KRAI_HAL_library/encoderKRAI/encoderKRAI.h>
#include "can.h"

ledKRAI led(LED_GPIO_Port, LED_Pin);

// Define Header
CAN_TxHeaderTypeDef   TxHeader;
uint8_t               TxData[8];
uint32_t              TxMailbox;

CAN_RxHeaderTypeDef   RxHeader;
uint8_t               RxData[8];
int datacheck = 0;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
  {
    Error_Handler();
  }

  datacheck = 1;
  
}

void mainProgram()
{
    led.toggle();

    // Initialize CAN interface
    HAL_CAN_Start(&hcan);

    // Fill CAN Header
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.StdId = 0x103;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.DLC = 2;

    // Fill CAN Data
    TxData[0] = 50;  
    TxData[1] = 0xAA;

    // Enable notification for receiving
    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }


    while (1)
    {

        // // SEND DATA 
        if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
        {
            Error_Handler();

            // if fail --> 1000ms
            led.toggle();
            HAL_Delay(1000);
        }

        led.toggle();
        HAL_Delay(200);

        // if success --> led blink
        // if (datacheck){
        //     led.toggle();
        //     HAL_Delay(200);
        // }

    }
}
