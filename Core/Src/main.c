/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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
#include "irda.h"
#include "stdio.h"
#include "string.h"
#include "7seg.h"
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
TIM_HandleTypeDef htim10;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
unsigned char LED_Value;
int tim6_count;
int SevenSegmentValue = 25;
unsigned char LED_Value;
unsigned char LED_Values_spot_bumper[] = {0x81, 0x42, 0x24, 0x18, 0x24, 0x42};
int current_index = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM10_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern int command_ok;
extern unsigned char irda_cmd[4];
void DisplayLEDs(int mode)
{
  if (mode == 1)
  {
    LED_Value = (LED_Value >> 1) | (LED_Value << 7);
  }
  else if (mode == 2)
  {
    LED_Value = (LED_Value << 1) | (LED_Value >> 7);
  }
  else if (mode == 3)
  {
    LED_Value = ~LED_Value;
  }
  else if (mode == 4)
  {
    //    	LED_Value = (LED_Value << 1) | (LED_Value >> 1);
    //    	if (LED_Value == 0x18){
    LED_Value = LED_Values_spot_bumper[current_index];
    current_index++;
    if (current_index >= 6)
    {
      current_index = 0;
    }
  }

  if (LED_Value & 0x80)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

  if (LED_Value & 0x40)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

  if (LED_Value & 0x20)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

  if (LED_Value & 0x10)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

  if (LED_Value & 0x8)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);

  if (LED_Value & 0x4)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  if (LED_Value & 0x2)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  if (LED_Value & 0x1)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
}
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
  MX_TIM10_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim10);
  Set7SegDisplayValue(SevenSegmentValue);
  command_ok = 0;
  tim6_count = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  LED_Value = 1;

  while (1)
  {
    /* USER CODE END WHILE */
    Run7SegDisplay();
    /* USER CODE BEGIN 3 */
    //	  HAL_Delay(500);
    //	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    //	  HAL_Delay(500);
    //	 	 DisplayLEDs(1);
    HAL_Delay(5);
    if (command_ok)
    {

      char buf[256];
      IrDecode();
      int decimal_value = irda_cmd[2];
      Set7SegDisplayValue(decimal_value);
      Run7SegDisplay();
      //	  		  for (int i=0;i <=100;i++){
      //	  			  if (decimal_value==i){
      //	  				 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
      //	  				 HAL_Delay(500);
      //	  				 for (int j=0; j <i/3;j++){
      //	  					HAL_Delay(500);
      //	  					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
      //	  					HAL_Delay(500);
      //	  				 }

      //	  				LED_Value=0xff;
      //	  					  	for (int i=0; i<=8;i++){
      //	  					  			  DisplayLEDs(3);
      //	  					  	HAL_Delay(100);
      //	  					  	}

      //	  			  }
      //	  		  }
      //	  		  if (decimal_value == 66){
      //	  			  LED_Value=1;
      //	  			  for (int i=0; i<=15;i++){
      //	  			  DisplayLEDs(1);
      //	  			  HAL_Delay(100);
      //	  			  }
      //	  		  }
      //			  if (decimal_value == 67){
      //		  			  LED_Value=1;
      //		  			  for (int i=0; i<=15;i++){
      //		  			  DisplayLEDs(1);
      //		  			  HAL_Delay(100);
      //		  			  }
      //		  		  }
      //			  if (decimal_value == 68){
      //		  			  LED_Value=1;
      //		  			  for (int i=0; i<=15;i++){
      //		  			  DisplayLEDs(1);
      //		  			  HAL_Delay(100);
      //		  			  }
      //		  		  }
      if (decimal_value == 69)
      {
        LED_Value = 1;
        for (int i = 0; i <= 15; i++)
        {
          DisplayLEDs(1);
          HAL_Delay(100);
        }
        LED_Value = 0;
        DisplayLEDs(1);
        Set7SegDisplayValue(decimal_value);
        Run7SegDisplay();
      }
      //			  if (decimal_value == 70){
      //		  			  LED_Value=1;
      //		  			  for (int i=0; i<=15;i++){
      //		  			  DisplayLEDs(1);
      //		  			  HAL_Delay(100);
      //		  			  }
      //		  		  }
      if (decimal_value == 70)
      {
        LED_Value = 1;
        for (int i = 0; i <= 14; i++)
        {
          DisplayLEDs(2);
          HAL_Delay(100);
          Set7SegDisplayValue(decimal_value);
          Run7SegDisplay();
        }
        LED_Value = 0;
        DisplayLEDs(1);
      }
      if (decimal_value == 71)
      {
        Set7SegDisplayValue(decimal_value);
        Run7SegDisplay();
        LED_Value = 0xff;
        for (int i = 0; i <= 4; i++)
        {
          DisplayLEDs(3);
          HAL_Delay(100);
        }
        LED_Value = 0;
        DisplayLEDs(1);
      }
      if (decimal_value == 68 || decimal_value == 67)
      {
        Set7SegDisplayValue(decimal_value);
        Run7SegDisplay();
        LED_Value = 0x81;
        for (int i = 0; i <= 12; i++)
        {
          DisplayLEDs(4);
          HAL_Delay(100);
        }
        LED_Value = 0;
        DisplayLEDs(1);
      }

      if (decimal_value == 28)
      {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
      }
      sprintf(buf, "%02x%02x%02x%02x\n", irda_cmd[0], irda_cmd[1], irda_cmd[2], irda_cmd[3]);
      // Assuming irda_cmd is an array of strings (char* irda_cmd[])

      HAL_UART_Transmit(&huart1, (const uint8_t *)buf, strlen(buf), 2);
      command_ok = 0;
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

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 13;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief TIM10 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 83;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 99;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6
                           PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15
                           PB3 PB4 PB5 PB6
                           PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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

#ifdef USE_FULL_ASSERT
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
