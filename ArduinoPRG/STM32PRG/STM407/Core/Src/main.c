/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adf4159.h"
#include "adf5355.h"
#include <DELEYMC.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct Command Command_t;
uint16_t ADR = 7;
uint64_t Ff4OUT = 4200000000;

uint64_t *FU4OUT = {0};
uint32_t *DLTT = {0};
uint32_t *DLTF = {0};
/*----------  AD4159  ----------*/
uint64_t FRQ4159 = 45008;
float DELF4159;
uint32_t DT;
#define BUFFER_SIZE (12)
#define  CMD_PREFIX (0xAA)
#define D4000  (1)
#define D8000  (0)
uint8_t buffer[BUFFER_SIZE] = {0};
uint8_t regsend[BUFFER_SIZE-4] = {0};
uint8_t frrec[BUFFER_SIZE-4] = {0};
int rcv = 0;
int dev = 0;
uint16_t SPILen = 4;
/*----------  ADF5355  ----------*/
uint64_t FRQ5355 = 5000000000;
/*----------   AD991   ----------*/
//typedef struct Command Command_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/*FIXME:@Comand 407*/
struct Command
{
  uint8_t Prefix;
  uint8_t Id;
  uint8_t Comm;
  uint8_t Output[8];
  uint8_t Crc;
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
/*FIXME:@Send (0)*/
void SendData(uint8_t *data);
void Perenos(uint8_t POZ);
void OUT_ON(uint8_t ON);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
//  HAL_TIM_Base_Start_IT(&htim1); // запуск таймера
 /**/
  ADR = GPIOE->IDR;
  ADR = ADR>>11;
  ADR = ADR&0x000F;

 // adf4159_PRESET0();
  adf4159_setupRG();
 // adf4159_out_altvoltage0_frequency(4000000000);
  adf5355_setupRG();
  adf5355_init();
// __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
// __HAL_UART_ENABLE_IT(&huart1, UART_IT_TC);
 // adf5355_setupRG();


  HAL_UARTEx_ReceiveToIdle_IT(&huart1,buffer,BUFFER_SIZE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//NOTE: @0 RECIV UART

//			if( HAL_UART_Receive(&huart1, str, 1, 3) == HAL_OK )
//			{
				 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
				 HAL_Delay(10);

				//HAL_UART_Transmit(&huart1, str, 5, 0xFFFF); //передача байта
				// if( HAL_UART_Receive_IT (&huart1, buffer, 5) != HAL_BUSY )
				// {

        /*==============================================
        =                Transmit block                 =
        ===============================================*/
				// HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
				// HAL_Delay(20);
				// while( HAL_UART_Transmit_IT(&huart1, regsend, 4) == HAL_BUSY );
				// HAL_Delay(20);
				// HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
         // SendData(regsend);
        /*=================   block  ================*/

				// }
					//HAL_Delay(200);

				 if(rcv == 1)// получен байт из UART
    {
      //NOTE: @2 Comm Friq
         if(dev == 9)
            //  if(cmd->Comm == 0)
      {

              	  if((Ff4OUT>=100000000)&(Ff4OUT<2900000000))
      		{
        		FRQ5355 = 6900000000;
        		FRQ4159 = 6900000000 - Ff4OUT;
        		Perenos(D4000);
      		}else if((Ff4OUT>=2900000000)&(Ff4OUT<4000000000))
      		{
        		FRQ4159 = 4000000000;
        		FRQ5355 = Ff4OUT + 4000000000;
        		Perenos(D4000);
      		}else if((Ff4OUT>=4000000000)&(Ff4OUT<=8000000000))
      		{
        		FRQ4159 = Ff4OUT;
        		Perenos(D8000);
      		}else
      		{
        		FRQ5355 = 6900000000;
        		FRQ4159 = 4900000000;
        		Perenos(D4000);
      		}

      		adf5355_out_altvoltage0_frequency(FRQ5355);
      		HAL_Delay(2);
      		adf5355_autoA_sync(1);
      		adf4159_out_altvoltage0_frequency(FRQ4159);
      		adf4159_autoA_sync(1);
      		HAL_Delay(10);

      }

          if (dev == 7)
      {
          OUT_ON(regsend[0]); //по умолча
          //Perenos(regsend[0]);
      }
          if (dev == 8)
      {
          Perenos(regsend[0]);
      }
					 //ADF4159
//NOTE: @0 SEND SPI
                switch (dev)
        {
        case 1: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); break;//ADF4159
        case 2: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); break;//ADF5355
        case 3: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET); break;//AD9911
        case 4: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); break;//PE43705
        default:    break;
        }
                switch (dev)
        {
        case 1: HAL_SPI_Transmit(&hspi1, (uint8_t*)&regsend, SPILen, 1000); break;
        case 2: HAL_SPI_Transmit(&hspi1, (uint8_t*)&regsend, SPILen, 1000); break;
        case 3: HAL_SPI_Transmit(&hspi2, (uint8_t*)&regsend, SPILen, 1000); break;
        case 4: HAL_SPI_Transmit(&hspi3, (uint8_t*)&regsend, SPILen, 1000); break;
        default:    break;
        }
                switch (dev)
        {
        case 1: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); break;
        case 2: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); break;
        case 3: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET); break;
        case 4: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        		OUT_ON(regsend[0]);											break;
        default:    break;
        }


            if(dev==5)
      {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);//IO_UDATE
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_Delay(5);
        HAL_TIM_Base_Start_IT(&htim1); // запуск таймера
      }

            if(dev==6)
      {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);//RESET
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
        HAL_TIM_Base_Stop_IT(&htim1); // стоп таймера
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
      }
            if(dev == 0xA)
      {//NOTE: @0 RAMP
        adf4159_ramp(DELF4159,DT);//deltaf deltat
        adf4159_autoA_sync(1);
        HAL_Delay(10);
      }
            SendData(buffer);
// HAL_SPI_Transmit(&hspi1, &buffer, 10, 1000);
        rcv = 0;
    }

		 /*==============================================
        =                Transmit block                 =
        ===============================================*/
        // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
        // HAL_Delay(20);
        // while( HAL_UART_Transmit_IT(&huart1, regsend, 4) == HAL_BUSY );
        // HAL_Delay(20);
        // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
         // SendData(regsend);
        /*=================   block  ================*/

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 256;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 74;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE5 PE7 PE8 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 PA4 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PC4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PE11 PE12 PE13 PE14 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PD9 PD0 PD1 PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/*FIXME:@Send (1) Fuction*/
void SendData(uint8_t *data)
{
// FL = __REV(RG);
 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
 HAL_Delay(10);
// while( HAL_UART_Transmit_IT(&huart1, data, sizeof(data)) == HAL_BUSY );

 HAL_UART_Transmit(&huart1, data, BUFFER_SIZE,1000);
  // Pull RE Low to enable RX operation
 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
//_delay_us(2);
}
//NOTE: @2 Event UART dev

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  /*----------------------------------------------------*/
	if(rcv == 0)
 { Command_t *cmd = (Command_t *)buffer;

      if(cmd->Prefix == CMD_PREFIX && cmd->Id == ADR)//&&rcv == 0
  {
		frrec[7] = cmd->Output[0];
		frrec[6] = cmd->Output[1];
		frrec[5] = cmd->Output[2];
		frrec[4] = cmd->Output[3];
		frrec[3] = cmd->Output[4];
		frrec[2] = cmd->Output[5];
		frrec[1] = cmd->Output[6];
		frrec[0] = cmd->Output[7];
		FU4OUT = (uint64_t*)frrec;
		Ff4OUT = *FU4OUT;
		regsend[0] = frrec[0];
		regsend[1] = frrec[1];
		regsend[2] = frrec[2];
		regsend[3] = frrec[3];
		regsend[4] = frrec[4];
		regsend[5] = frrec[5];
		regsend[6] = frrec[6];
		regsend[7] = frrec[7];
            switch (cmd->Comm)
    {
    case 0:                 //friq
    	 dev = 0X9; break;
    case 1:
    	DELF4159 = Ff4OUT>>32;
    	DT = Ff4OUT&0xFFFFFFFF;
    	dev = 0xA;
    	break;//band
    case 2:  dev = 0x4;
        regsend[4] = ((regsend[4] >> 4) & 15) | ((regsend[4] & 15) << 4);
        regsend[4] = ((regsend[4] >> 2) & 51) | ((regsend[4] & 51) << 2);
        regsend[4] = ((regsend[4] >> 1) & 85) | ((regsend[4] & 85) << 1);break;//power

    default:    break;
    }
    rcv = 1;//пришли данные
  }
  else
  {

  }
/*----------------------------------------------------------*/


//		regsend[0] = frrec[7];
//		regsend[1] = frrec[6];
//		regsend[2] = frrec[5];
//		regsend[3] = frrec[4];
//		regsend[4] = frrec[3];
//		regsend[5] = frrec[2];
//		regsend[6] = frrec[1];
//		regsend[7] = frrec[0];


//    frrec[7] = buffer[1];
//    frrec[6] = buffer[2];
//    frrec[5] = buffer[3];
//    frrec[4] = buffer[4];
//    frrec[3] = buffer[5];
//    frrec[2] = buffer[6];
//    frrec[1] = buffer[7];
//    frrec[0] = buffer[8];


		//FU4OUT = (uint64_t*)frrec;

//   DLTF = (uint32_t*)(uint8_t*)regsend;
//   DLTT = (uint32_t*)(uint8_t*)regsend+4;
//   DF  = *DLTT;
//		DELF4159 = DF;
//		memcpy(&DELF4159, *DLTF, sizeof(DELF4159));
		//memcpy(&FRQ4159, frrec, sizeof(FRQ4159));

    /*
		Ff4OUT = *FU4OUT;
		DELF4159 = Ff4OUT>>32;
		DT = Ff4OUT&0xFFFFFFFF;
		rcv = 1;//пришли данные */
      // switch (buffer[0])
      // {
      // case 0: dev = 1;   break;
      // case 1: dev = 2;   break;
      // case 2: dev = 3;   break;
      // case 3: dev = 4;   break;
      // default: dev = 0;   break;
      // }
     /* dev = buffer[0];
      SPILen = buffer[9];*/

	  }

	  HAL_UARTEx_ReceiveToIdle_IT(&huart1,buffer, BUFFER_SIZE);//прерыв приема в EN
}
void Perenos(uint8_t POZ)
{
          switch (POZ)
  {
  case 0: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);  break;//на прямую

  case 1: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);    break;

  case 2: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);    break;

  case 3: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);    break;

  default:HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);  break;
  }

}
void OUT_ON(uint8_t ON)
{
  switch (ON)
  {
  case 0: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);    break;//выкл

  case 1: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);  break;

  default:HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);    break;//выкл
  }

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
