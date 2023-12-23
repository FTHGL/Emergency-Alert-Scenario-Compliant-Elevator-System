/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

#include "liquidcrystal_i2c.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */


uint16_t button_0_St=0;
uint16_t button_1_St=0; 
uint16_t button_2_St=0;

uint16_t hall_0_St = 0;
uint16_t hall_1_St = 0;
uint16_t hall_2_St = 0;

uint16_t adc_Val ;
uint16_t tilt;



uint8_t ctrlSt;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void upStairs(void){
	
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,250);

		
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

}
void downStairs(void){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,250);

	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);	

}
void stop(void){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

}

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
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HD44780_Init(2);
	HAL_Delay(2000);

	stop();
	HAL_Delay(500);

	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		button_0_St = HAL_GPIO_ReadPin(button_0_GPIO_Port,button_0_Pin);
		button_1_St = HAL_GPIO_ReadPin(button_1_GPIO_Port,button_1_Pin);
		button_2_St = HAL_GPIO_ReadPin(button_2_GPIO_Port,button_2_Pin);
		
		hall_0_St = HAL_GPIO_ReadPin(hall_0_GPIO_Port,hall_0_Pin);
		hall_1_St = HAL_GPIO_ReadPin(hall_1_GPIO_Port,hall_1_Pin);
		hall_2_St = HAL_GPIO_ReadPin(hall_2_GPIO_Port,hall_2_Pin);
		
		//tilt = HAL_GPIO_ReadPin(tilt_sensor_GPIO_Port,tilt_sensor_Pin);
		
		
		HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,HAL_MAX_DELAY);
    adc_Val = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    HAL_Delay(500);
		
		if(adc_Val<1700){
		
		}
		else{
			
			HD44780_Clear();
			HD44780_SetCursor(7,0);
			HD44780_PrintStr("ACIL");
			HD44780_SetCursor(7,1);
			HD44780_PrintStr("DURUM");
			HAL_Delay(3000);
			
			HD44780_Clear();
			HD44780_SetCursor(1,0);
			HD44780_PrintStr("TAHLIYE KATINA");
			HD44780_SetCursor(3,1);
			HD44780_PrintStr("GIDILIYOR");
			HAL_Delay(2000);
			
			hall_0_St = HAL_GPIO_ReadPin(hall_0_GPIO_Port,hall_0_Pin);
				
				if(hall_0_St==1){

					HAL_Delay(2000);

					HD44780_Clear();
					HD44780_SetCursor(0,0);
					HD44780_PrintStr("0 -|");
					HAL_Delay(2000);
					stop();
					continue;
				
					
				}else{
					downStairs();
					continue;
				}
			
		
		}
		
		
		
		
		if(hall_0_St==1){
			
		
			stop();
			HD44780_Clear();
			HD44780_SetCursor(0,0);
			HD44780_PrintStr("0. kat");
			HAL_Delay(2000);
			
			if (button_0_St){
				//0 
				
				HD44780_Clear();
				HD44780_SetCursor(0,0);
				HD44780_PrintStr("0. kattasiniz");
				HAL_Delay(2000);
				stop();
				
				
			}else if(button_1_St){
				//0 -> 1
				
				HD44780_Clear();
				HD44780_SetCursor(0,0);
				HD44780_PrintStr("0 -> 1");

				hall_1_St = HAL_GPIO_ReadPin(hall_1_GPIO_Port,hall_1_Pin);
				
				if(hall_1_St==1){

					HAL_Delay(2000);

					HD44780_Clear();
					HD44780_SetCursor(0,0);
					HD44780_PrintStr("1 -|");
					HAL_Delay(2000);
					continue;

				}else{
					upStairs();

					continue;
				}
				
			}else if(button_2_St){
				//0 -> 2
				
				HD44780_Clear();
				HD44780_SetCursor(0,0);
				HD44780_PrintStr("0 -> 2");
				HAL_Delay(2000);
				
				hall_2_St = HAL_GPIO_ReadPin(hall_2_GPIO_Port,hall_2_Pin);
				
				if(hall_2_St==1){

					HD44780_Clear();
					HD44780_SetCursor(0,0);
					HD44780_PrintStr("2 -|");
					HAL_Delay(2000);
					
				}else{
					upStairs();
					continue;
				}
			}else{
			continue;}
		
		}
		
		else if(hall_1_St==1){
		

			stop();
			HD44780_Clear();
			HD44780_SetCursor(0,0);
			HD44780_PrintStr("1. kat");
			HAL_Delay(2000);
			
			if (button_0_St){
				//1 -> 0
				
				HD44780_Clear();
				HD44780_SetCursor(0,0);
				HD44780_PrintStr("1 -> 0");
				HAL_Delay(2000);
				
				hall_0_St = HAL_GPIO_ReadPin(hall_0_GPIO_Port,hall_0_Pin);
				
				if(hall_0_St==1){

					HAL_Delay(2000);

					HD44780_Clear();
					HD44780_SetCursor(0,0);
					HD44780_PrintStr("0 -|");
					HAL_Delay(2000);
					continue;
				
					
				}else{
					downStairs();
					continue;
				}
			}else if(button_1_St){
				//1
				
				
				HAL_Delay(500);
				HD44780_Clear();
				HD44780_SetCursor(0,0);
				HD44780_PrintStr("1. kattasiniz");
				HAL_Delay(2000);
				
			}else if(button_2_St){
				//1 -> 2
				
				HD44780_Clear();
				HD44780_SetCursor(0,0);
				HD44780_PrintStr("1 -> 2");
				HAL_Delay(2000);
				
				hall_2_St = HAL_GPIO_ReadPin(hall_2_GPIO_Port,hall_2_Pin);
				
				if(hall_2_St==1){

					HAL_Delay(2000);

					HD44780_Clear();
					HD44780_SetCursor(0,0);
					HD44780_PrintStr("2 -|");
					HAL_Delay(2000);
					continue;
				
					
				}else{
					upStairs();
					continue;
				}
			}else{
			continue;}

		}
		else if(hall_2_St==1){

			stop();
			HD44780_Clear();
			HD44780_SetCursor(0,0);
			HD44780_PrintStr("2. kat");
			HAL_Delay(2000);
			
			if (button_0_St){
				//2 -> 0
				
				HD44780_Clear();
				HD44780_SetCursor(0,0);
				HD44780_PrintStr("2 -> 0");
				HAL_Delay(2000);
				
				hall_0_St = HAL_GPIO_ReadPin(hall_0_GPIO_Port,hall_0_Pin);
				
				if(hall_0_St==1){

					HAL_Delay(2000);

					HD44780_Clear();
					HD44780_SetCursor(0,0);
					HD44780_PrintStr("0 -|");
					HAL_Delay(2000);
					continue;
				
					
				}else{
					downStairs();
					continue;
				}
			}else if(button_1_St){
				//2 -> 1
				HD44780_Clear();
				HD44780_SetCursor(0,0);
				HD44780_PrintStr("2 -> 1");
				HAL_Delay(2000);
				
				hall_1_St = HAL_GPIO_ReadPin(hall_1_GPIO_Port,hall_1_Pin);
				
				if(hall_1_St==1){

					HAL_Delay(2000);

					HD44780_Clear();
					HD44780_SetCursor(0,0);
					HD44780_PrintStr("1 -|");
					HAL_Delay(2000);
					continue;
				
					
				}else{
					downStairs();
					continue;
				}
			}else if(button_2_St){
				//2
				
				HD44780_Clear();
				HD44780_SetCursor(0,0);
				HD44780_PrintStr("2. kattasiniz");
				HAL_Delay(2000);
			}else{
			continue;}
		
		}
		else{
		continue;
		}
		
		
		
		
		
		
		
		
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 127;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 625;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, dc_motor_O1_Pin|dc_motor_O2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : dc_motor_O1_Pin dc_motor_O2_Pin */
  GPIO_InitStruct.Pin = dc_motor_O1_Pin|dc_motor_O2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : button_0_Pin button_1_Pin button_2_Pin hall_0_Pin */
  GPIO_InitStruct.Pin = button_0_Pin|button_1_Pin|button_2_Pin|hall_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : hall_1_Pin hall_2_Pin tilt_sensor_Pin */
  GPIO_InitStruct.Pin = hall_1_Pin|hall_2_Pin|tilt_sensor_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
