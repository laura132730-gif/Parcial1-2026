/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// Mapa de 7 segmentos para Cátodo Común (A, B, C, D, E, F, G)
// 1 = Segmento ENCENDIDO, 0 = Segmento APAGADO
const uint8_t digitos_7seg[10] = {
    0b00111111, // 0 -> A, B, C, D, E, F
    0b00000110, // 1 -> B, C
    0b01011011, // 2 -> A, B, D, E, G
    0b01001111, // 3 -> A, B, C, D, G
    0b01100110, // 4 -> B, C, F, G
    0b01101101, // 5 -> A, C, D, F, G
    0b01111101, // 6 -> A, C, D, E, F, G
    0b00000111, // 7 -> A, B, C
    0b01111111, // 8 -> A, B, C, D, E, F, G
    0b01101111  // 9 -> A, B, C, D, F, G
};

uint8_t contador = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void Display_SecuenciaHola(uint16_t retardo);
void Display_Conteo0a9(uint16_t retardo);
void Display_ConteoPrimos(uint16_t retardo);
void Display_EfectoCulebrita(uint8_t vueltas, uint16_t retardo);

void Display_Apagar(void);

void Luces_Apagar(void);
void Luces_AutoFantastico(uint8_t pasadas, uint16_t retardo);
void Luces_Parpadeo(uint8_t veces, uint16_t retardo);
void Luces_Alternado(uint8_t ciclos, uint16_t retardo);
void Luces_MarquesinaSecuencial(uint8_t vueltas, uint16_t retardo);

void Buzzer_Tono(uint16_t frecuencia, uint16_t duracion_ms);
void Buzzer_MelodiaMario(void);
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
  /* USER CODE BEGIN 2 */
    // Proceso 7: Luces alternadas
    Luces_Alternado(5, 300);
    HAL_Delay(1000);

    // Proceso 8: Marquesina secuencial
    Luces_MarquesinaSecuencial(3, 300);
    HAL_Delay(1000);
  /* USER CODE END 2 */

 /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      //===== PROCEDIMIENTOS DE 7 SEGMENTOS (4 llamadas) =====
     
      // 1. Display: HOLA
      Display_SecuenciaHola(700);
      Display_Apagar();
      HAL_Delay(1000);

      // 2. Display: Conteo 0 a 9
      Display_Conteo0a9(1000);
      Display_Apagar();
      HAL_Delay(1000);

      // 3. Display: Primos (1ª Ejecución)
      Display_ConteoPrimos(700);
      Display_Apagar();
      HAL_Delay(1000);

      // 4. Display: Culebrita -> [PARÁMETROS: 4 vueltas, 100ms]
      Display_EfectoCulebrita(4, 100);
      Display_Apagar();
      HAL_Delay(1000);

      //===== PROCEDIMIENTOS LUCES LED (2 llamadas) =====

      // 5. LEDS: Auto Fantástico -> [PARÁMETROS: 2 pasadas, 100ms]
      Luces_AutoFantastico(2, 100);
      HAL_Delay(1500);

      // 6. LEDS: Auto Fantástico REPETIDO -> [PARÁMETROS: 4 pasadas, 50ms - Más rápido]
      Luces_AutoFantastico(4, 50);
      HAL_Delay(2000);

    // Reproducir la melodía de Mario
      Buzzer_MelodiaMario();
      HAL_Delay(2000);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DP_A_Pin|DP_B_Pin|DP_C_Pin|DP_D_Pin
                          |DP_E_Pin|DP_F_Pin|DP_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_1_Pin|LED_2_Pin|LED_3_Pin|LED_4_Pin
                          |BUZZ_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DP_A_Pin DP_B_Pin DP_C_Pin DP_D_Pin
                           DP_E_Pin DP_F_Pin DP_G_Pin */
  GPIO_InitStruct.Pin = DP_A_Pin|DP_B_Pin|DP_C_Pin|DP_D_Pin
                          |DP_E_Pin|DP_F_Pin|DP_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_1_Pin LED_2_Pin LED_3_Pin LED_4_Pin
                           BUZZ_Pin */
  GPIO_InitStruct.Pin = LED_1_Pin|LED_2_Pin|LED_3_Pin|LED_4_Pin
                          |BUZZ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// Procedimiento 1: Muestra 'H' -> 'O' -> 'L' -> 'A'
void Display_SecuenciaHola(uint16_t retardo) {
    uint8_t hola[4] = {
        0b01110110, // H
        0b00111111, // O
        0b00111000, // L
        0b01110111  // A
    };
    
    for (int k = 0; k < 4; k++) {
        uint8_t patron = hola[k];
        HAL_GPIO_WritePin(GPIOA, DP_A_Pin, (patron & (1 << 0)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_B_Pin, (patron & (1 << 1)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_C_Pin, (patron & (1 << 2)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_D_Pin, (patron & (1 << 3)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_E_Pin, (patron & (1 << 4)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_F_Pin, (patron & (1 << 5)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_G_Pin, (patron & (1 << 6)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_Delay(retardo);
    }
}

// Procedimiento 2: Conteo incremental de 0 a 9
void Display_Conteo0a9(uint16_t retardo) {
    for (uint8_t i = 0; i <= 9; i++) {
        uint8_t patron = digitos_7seg[i];
        
        HAL_GPIO_WritePin(GPIOA, DP_A_Pin, (patron & (1 << 0)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_B_Pin, (patron & (1 << 1)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_C_Pin, (patron & (1 << 2)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_D_Pin, (patron & (1 << 3)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_E_Pin, (patron & (1 << 4)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_F_Pin, (patron & (1 << 5)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_G_Pin, (patron & (1 << 6)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_Delay(retardo);
    }
}

// Procedimiento 3: Muestra solo números primos (2, 3, 5, 7)
void Display_ConteoPrimos(uint16_t retardo) {
    uint8_t primos[4] = {2, 3, 5, 7};
    
    for (int i = 0; i < 4; i++) {
        uint8_t patron = digitos_7seg[primos[i]];
        
        HAL_GPIO_WritePin(GPIOA, DP_A_Pin, (patron & (1 << 0)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_B_Pin, (patron & (1 << 1)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_C_Pin, (patron & (1 << 2)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_D_Pin, (patron & (1 << 3)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_E_Pin, (patron & (1 << 4)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_F_Pin, (patron & (1 << 5)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, DP_G_Pin, (patron & (1 << 6)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_Delay(retardo);
    }
}

// Procedimiento 4 (Con Parámetros): Culebrita fluida con cuerpo de 2 segmentos
void Display_EfectoCulebrita(uint8_t vueltas, uint16_t retardo) {
    // Secuencia de pines formando el recorrido en "8" o infinito: A -> B -> G -> E -> D -> C -> G -> F
    uint16_t secuencia_pines[8] = {
        DP_A_Pin, DP_B_Pin, DP_G_Pin, DP_E_Pin,
        DP_D_Pin, DP_C_Pin, DP_G_Pin, DP_F_Pin
    };

    // Apagar todos los segmentos antes de iniciar
    HAL_GPIO_WritePin(GPIOA, DP_A_Pin|DP_B_Pin|DP_C_Pin|DP_D_Pin|DP_E_Pin|DP_F_Pin|DP_G_Pin, GPIO_PIN_RESET);

    for (uint8_t v = 0; v < vueltas; v++) {
        for (int i = 0; i < 8; i++) {
            // Segmento actual (Cabeza de la serpiente)
            uint16_t cabeza = secuencia_pines[i];
            
            // Segmento anterior (Cola de la serpiente)
            uint16_t cola = secuencia_pines[(i == 0) ? 7 : (i - 1)];

            // 1. Encender la cabeza (mantiene la cola prendida para dar fluidez)
            HAL_GPIO_WritePin(GPIOA, cabeza, GPIO_PIN_SET);
            HAL_Delay(retardo);

            // 2. Apagar la cola para que avance
            HAL_GPIO_WritePin(GPIOA, cola, GPIO_PIN_RESET);
        }
    }

    // Apagar el display al finalizar el efecto
    HAL_GPIO_WritePin(GPIOA, DP_A_Pin|DP_B_Pin|DP_C_Pin|DP_D_Pin|DP_E_Pin|DP_F_Pin|DP_G_Pin, GPIO_PIN_RESET);
}

// Procedimiento Auxiliar: Apaga absolutamente todos los segmentos del display
void Display_Apagar(void) {
    HAL_GPIO_WritePin(GPIOA, DP_A_Pin | DP_B_Pin | DP_C_Pin | DP_D_Pin | 
                             DP_E_Pin | DP_F_Pin | DP_G_Pin, GPIO_PIN_RESET);
}

// Procedimiento Auxiliar: Apaga los 4 LEDs
void Luces_Apagar(void) {
    HAL_GPIO_WritePin(GPIOB, LED_1_Pin | LED_2_Pin | LED_3_Pin | LED_4_Pin, GPIO_PIN_RESET);
}

// Procedimiento 5 (Con Parámetros): Secuencia de ida y vuelta (Auto Fantástico)
void Luces_AutoFantastico(uint8_t pasadas, uint16_t retardo) {
    uint16_t leds[4] = {LED_1_Pin, LED_2_Pin, LED_3_Pin, LED_4_Pin};

    Luces_Apagar();

    for (uint8_t p = 0; p < pasadas; p++) {
        // Ida: LED 1 -> LED 4
        for (int8_t i = 0; i < 4; i++) {
            HAL_GPIO_WritePin(GPIOB, leds[i], GPIO_PIN_SET);
            HAL_Delay(retardo);
            HAL_GPIO_WritePin(GPIOB, leds[i], GPIO_PIN_RESET);
        }

        // Vuelta: LED 3 -> LED 2
        for (int8_t i = 2; i >= 1; i--) {
            HAL_GPIO_WritePin(GPIOB, leds[i], GPIO_PIN_SET);
            HAL_Delay(retardo);
            HAL_GPIO_WritePin(GPIOB, leds[i], GPIO_PIN_RESET);
        }
    }
    
    Luces_Apagar();
}
// Procedimiento 6: Parpadeo simultáneo de los 4 LEDs
void Luces_Parpadeo(uint8_t veces, uint16_t retardo) {
    for (uint8_t i = 0; i < veces; i++) {
        HAL_GPIO_WritePin(GPIOB, LED_1_Pin | LED_2_Pin | LED_3_Pin | LED_4_Pin, GPIO_PIN_SET);
        HAL_Delay(retardo);
        HAL_GPIO_WritePin(GPIOB, LED_1_Pin | LED_2_Pin | LED_3_Pin | LED_4_Pin, GPIO_PIN_RESET);
        HAL_Delay(retardo);
    }
    
    Luces_Apagar();
}

// Procedimiento 7 (Fuera del while - Con Parámetros): Alternado entre impares (LED 1 y 3) y pares (LED 2 y 4)
void Luces_Alternado(uint8_t ciclos, uint16_t retardo)
{
    for (uint8_t c = 0; c < ciclos; c++)
    {
        HAL_GPIO_WritePin(GPIOB, LED_1_Pin | LED_3_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, LED_2_Pin | LED_4_Pin, GPIO_PIN_RESET);
        HAL_Delay(retardo);

        Luces_Apagar();
        HAL_Delay(retardo / 2);

        HAL_GPIO_WritePin(GPIOB, LED_2_Pin | LED_4_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, LED_1_Pin | LED_3_Pin, GPIO_PIN_RESET);
        HAL_Delay(retardo);

        Luces_Apagar();
        HAL_Delay(retardo / 2);
    }

    Luces_Apagar();
}

// Procedimiento 8 (Fuera del while - Con Parámetros): Llenado progresivo de los 4 LEDs de izquierda a derecha
void Luces_MarquesinaSecuencial(uint8_t vueltas, uint16_t retardo)
{
    uint16_t leds[4] = {
        LED_1_Pin,
        LED_2_Pin,
        LED_3_Pin,
        LED_4_Pin
    };

    for (uint8_t v = 0; v < vueltas; v++)
    {
        Luces_Apagar();

        for (int i = 0; i < 4; i++)
        {
            HAL_GPIO_WritePin(GPIOB, leds[i], GPIO_PIN_SET);
            HAL_Delay(retardo);
        }

        HAL_Delay(retardo);
        Luces_Apagar();
        HAL_Delay(retardo);
    }

    Luces_Apagar();
}

// Genera una frecuencia en el pin BUZZ
void Buzzer_Tono(uint16_t frecuencia, uint16_t duracion_ms) {
    if (frecuencia == 0) {
        HAL_Delay(duracion_ms);
        return;
    }
    
    // Calcular el periodo en microsegundos (1,000,000 / frecuencia)
    uint32_t periodo_us = 1000000 / frecuencia;
    uint32_t medio_periodo = periodo_us / 2;
    
    // Calcular cuántos ciclos se ejecutan durante la duración deseada
    uint32_t ciclos = ((uint32_t)frecuencia * duracion_ms) / 1000;
    
    for (uint32_t i = 0; i < ciclos; i++) {
        HAL_GPIO_WritePin(GPIOB, BUZZ_Pin, GPIO_PIN_SET);
        for(volatile int d = 0; d < medio_periodo * 8; d++) { __NOP(); } 
        
        HAL_GPIO_WritePin(GPIOB, BUZZ_Pin, GPIO_PIN_RESET);
        for(volatile int d = 0; d < medio_periodo * 8; d++) { __NOP(); }
    }
}

// Procedimiento de la Melodía de Mario
void Buzzer_MelodiaMario(void) {
    uint16_t melodia[] = {
        NOTE_E4, NOTE_E4, 0, NOTE_E4, 0, NOTE_C4, NOTE_E4, 0, NOTE_G4, 0, NOTE_C4
    };

    uint16_t duraciones[] = {
        150, 150, 100, 150, 100, 150, 150, 100, 300, 300, 300
    };

    uint8_t total_notas = sizeof(melodia) / sizeof(melodia[0]);

    for (uint8_t i = 0; i < total_notas; i++) {
        Buzzer_Tono(melodia[i], duraciones[i]);
        HAL_Delay(40); // Pausa breve entre notas
    }

    HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_RESET);
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