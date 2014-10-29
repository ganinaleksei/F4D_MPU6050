/*
 * uart.cpp
 *
 *  Created on: 20 okt 2014
 *      Author: ensul1
 */
#include "uart.hpp"

/* UART handler declaration */
UART_HandleTypeDef UartHandle;
//__IO ITStatus UartReady = RESET;

char str[100];

/* Buffer used for transmission */
//uint8_t aTxBuffer[] = " **** UART_TwoBoards_ComPolling ****  **** UART_TwoBoards_ComPolling ****  **** UART_TwoBoards_ComPolling **** ";

/* Buffer used for reception */
//uint8_t aRxBuffer[RXBUFFERSIZE];

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();
  /* Enable USART2 clock */
  USARTx_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;

  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;

  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  /*##-1- Reset peripherals ##################################################*/
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
}


///**
//  * @brief UART MSP Initialization
//  *        This function configures the hardware resources used in this example:
//  *           - Peripheral's clock enable
//  *           - Peripheral's GPIO Configuration
//  *           - DMA configuration for transmission request by peripheral
//  *           - NVIC configuration for DMA interrupt request enable
//  * @param huart: UART handle pointer
//  * @retval None
//  */
//void HAL_UART_MspInit(UART_HandleTypeDef *huart)
//{
//  static DMA_HandleTypeDef hdma_tx;
//  static DMA_HandleTypeDef hdma_rx;
//
//  GPIO_InitTypeDef  GPIO_InitStruct;
//
//  /*##-1- Enable peripherals and GPIO Clocks #################################*/
//  /* Enable GPIO TX/RX clock */
//  USARTx_TX_GPIO_CLK_ENABLE();
//  USARTx_RX_GPIO_CLK_ENABLE();
//  /* Enable USART2 clock */
//  USARTx_CLK_ENABLE();
//  /* Enable DMA1 clock */
//  DMAx_CLK_ENABLE();
//
//  /*##-2- Configure peripheral GPIO ##########################################*/
//  /* UART TX GPIO pin configuration  */
//  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
//  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull      = GPIO_NOPULL;
//  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
//  GPIO_InitStruct.Alternate = USARTx_TX_AF;
//
//  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);
//
//  /* UART RX GPIO pin configuration  */
//  GPIO_InitStruct.Pin = USARTx_RX_PIN;
//  GPIO_InitStruct.Alternate = USARTx_RX_AF;
//
//  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
//
//  /*##-3- Configure the DMA streams ##########################################*/
//  /* Configure the DMA handler for Transmission process */
//  hdma_tx.Instance                 = USARTx_TX_DMA_STREAM;
//
//  hdma_tx.Init.Channel             = USARTx_TX_DMA_CHANNEL;
//  hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
//  hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
//  hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
//  hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//  hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
//  hdma_tx.Init.Mode                = DMA_NORMAL;
//  hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;
//  hdma_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
//  hdma_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
//  hdma_tx.Init.MemBurst            = DMA_MBURST_INC4;
//  hdma_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
//
//  HAL_DMA_Init(&hdma_tx);
//
//  /* Associate the initialized DMA handle to the the UART handle */
//  __HAL_LINKDMA(huart, hdmatx, hdma_tx);
//
//  /* Configure the DMA handler for Transmission process */
//  hdma_rx.Instance                 = USARTx_RX_DMA_STREAM;
//
//  hdma_rx.Init.Channel             = USARTx_RX_DMA_CHANNEL;
//  hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
//  hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
//  hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
//  hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//  hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
//  hdma_rx.Init.Mode                = DMA_NORMAL;
//  hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;
//  hdma_rx.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
//  hdma_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
//  hdma_rx.Init.MemBurst            = DMA_MBURST_INC4;
//  hdma_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
//
//  HAL_DMA_Init(&hdma_rx);
//
//  /* Associate the initialized DMA handle to the the UART handle */
//  __HAL_LINKDMA(huart, hdmarx, hdma_rx);
//
//  /*##-4- Configure the NVIC for DMA #########################################*/
//  /* NVIC configuration for DMA transfer complete interrupt (USART1_TX) */
//  HAL_NVIC_SetPriority(USARTx_DMA_TX_IRQn, 3, 4);
//  HAL_NVIC_EnableIRQ(USARTx_DMA_TX_IRQn);
//
//  /* NVIC configuration for DMA transfer complete interrupt (USART1_RX) */
//  HAL_NVIC_SetPriority(USARTx_DMA_RX_IRQn, 3, 3);
//  HAL_NVIC_EnableIRQ(USARTx_DMA_RX_IRQn);
//}
//
///**
//  * @brief UART MSP De-Initialization
//  *        This function frees the hardware resources used in this example:
//  *          - Disable the Peripheral's clock
//  *          - Revert GPIO, DMA and NVIC configuration to their default state
//  * @param huart: UART handle pointer
//  * @retval None
//  */
//void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
//{
//
//  static DMA_HandleTypeDef hdma_tx;
//  static DMA_HandleTypeDef hdma_rx;
//
//  /*##-1- Reset peripherals ##################################################*/
//  USARTx_FORCE_RESET();
//  USARTx_RELEASE_RESET();
//
//  /*##-2- Disable peripherals and GPIO Clocks #################################*/
//  /* Configure UART Tx as alternate function  */
//  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
//  /* Configure UART Rx as alternate function  */
//  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
//
//  /*##-3- Disable the DMA Streams ############################################*/
//  /* De-Initialize the DMA Stream associate to transmission process */
//  HAL_DMA_DeInit(&hdma_tx);
//  /* De-Initialize the DMA Stream associate to reception process */
//  HAL_DMA_DeInit(&hdma_rx);
//
//  /*##-4- Disable the NVIC for DMA ###########################################*/
//  HAL_NVIC_DisableIRQ(USARTx_DMA_TX_IRQn);
//  HAL_NVIC_DisableIRQ(USARTx_DMA_RX_IRQn);
//}

void UART_Init(void){
/*##-1- Configure the UART peripheral ######################################*/
/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
/* UART1 configured as follow:
    - Word Length = 8 Bits
    - Stop Bit = One Stop bit
    - Parity = None
    - BaudRate = 9600 baud
    - Hardware flow control disabled (RTS and CTS signals) */
UartHandle.Instance        = USARTx;
UartHandle.Init.BaudRate   = 9600;
UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
UartHandle.Init.StopBits   = UART_STOPBITS_1;
UartHandle.Init.Parity     = UART_PARITY_NONE;
UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
UartHandle.Init.Mode       = UART_MODE_TX_RX;

if(HAL_UART_Init(&UartHandle) != HAL_OK)
{
  /* Turn LED5 (RED) on */
  BSP_LED_On(LED5);
  while(1)
  {
  }
}
}

void UART_Float_TX(float f){
//  int c = Float2String(*pData);

  char buf[10]={0};
  //      float f = 3.1415;
  ////      sprintf(buf,"%d.%02u\r\n", (int)f , ((int) (((f)-(int)f) * 10000)));
  UART_TX((uint8_t *)buf, sprintf(buf,"%d.%02u\t", (int)f , ((int) (((f)-(int)f) * 10))));

//  if(HAL_UART_Transmit(&UartHandle, (uint8_t*)str, c, 5000)!= HAL_OK)
//  {
//    /* Turn LED5 (RED) on */
//    BSP_LED_On(LED5);
//    while(1)
//    {
//    }
//  }
}

void UART_TX(uint8_t *pData, uint16_t Size){
//  if(HAL_UART_Transmit_DMA(&UartHandle, pData, Size) != HAL_OK){
//      /* Turn LED5 (RED) on */
//      BSP_LED_On(LED5);
//      while(1)
//      {
//      }
//  }

  if(HAL_UART_Transmit(&UartHandle, pData, Size, 5000)!= HAL_OK)
  {
    /* Turn LED5 (RED) on */
    BSP_LED_On(LED5);
    while(1)
    {
    }
  }
}

int Float2String(float float_val){
  int d1 = float_val;            // Get the integer part (678).
  float f2 = float_val - d1;     // Get fractional part (0.01234567).
  int d2 = trunc (f2 * 10000);   // Turn into integer (123).
  float f3 = f2 * 10000 - d2;   // Get next fractional part (0.4567).
  int d3 = trunc (f3 * 10000);   // Turn into integer (4567).

  return sprintf (str, "Value = %d.%04d%04d\r\n", d1, d2, d3);
}

///**
//  * @brief  Tx Transfer completed callback
//  * @param  UartHandle: UART handle.
//  * @note   This example shows a simple way to report end of DMA Tx transfer, and
//  *         you can add your own implementation.
//  * @retval None
//  */
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
//{
//  /* Set transmission flag: trasfer complete*/
//  UartReady = SET;
//
//  /* Turn LED6 on: Transfer in transmission process is correct */
//  BSP_LED_On(LED6);
//}
//
///**
//  * @brief  Rx Transfer completed callback
//  * @param  UartHandle: UART handle
//  * @note   This example shows a simple way to report end of DMA Rx transfer, and
//  *         you can add your own implementation.
//  * @retval None
//  */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
//{
//  /* Set transmission flag: trasfer complete*/
//  UartReady = SET;
//
//  /* Turn LED4 on: Transfer in reception process is correct */
//  BSP_LED_On(LED4);
//}

/**
  * @brief  UART error callbacks
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
  /* Turn LED3 on: Transfer error in reception/transmission process */
  BSP_LED_On(LED3);
}
