/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "../../../PROJECT/wrappers/inc/OSwrappers.hpp"
#include <OSwrappers.hpp>
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId usbTaskHandle;
osThreadId logServerTaskHandle;
osThreadId UartServerHandle;
osThreadId MainAppHandle;
osThreadId MainControllerHandle;
osMessageQId myQueue01Handle;
osMutexId osMutexPatternHandle;
osSemaphoreId osSemaphorePatternHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartUsbTask(void const * argument);
void StartLogServer(void const * argument);
void startUartServer(void const * argument);
void StartMainApp(void const * argument);
void StartMainController(void const * argument);

extern void MX_USB_HOST_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of osMutexPattern */
  osMutexDef(osMutexPattern);
  osMutexPatternHandle = osMutexCreate(osMutex(osMutexPattern));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of osSemaphorePattern */
  osSemaphoreDef(osSemaphorePattern);
  osSemaphorePatternHandle = osSemaphoreCreate(osSemaphore(osSemaphorePattern), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of myQueue01 */
  osMessageQDef(myQueue01, 16, uint16_t);
  myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of usbTask */
  osThreadDef(usbTask, StartUsbTask, osPriorityAboveNormal, 0, 2048);
  usbTaskHandle = osThreadCreate(osThread(usbTask), NULL);

  /* definition and creation of logServerTask */
  osThreadDef(logServerTask, StartLogServer, osPriorityLow, 0, 128);
  logServerTaskHandle = osThreadCreate(osThread(logServerTask), NULL);

  /* definition and creation of UartServer */
  osThreadDef(UartServer, startUartServer, osPriorityAboveNormal, 0, 512);
  UartServerHandle = osThreadCreate(osThread(UartServer), NULL);

  /* definition and creation of MainApp */
  osThreadDef(MainApp, StartMainApp, osPriorityNormal, 0, 512);
  MainAppHandle = osThreadCreate(osThread(MainApp), NULL);

  /* definition and creation of MainController */
  osThreadDef(MainController, StartMainController, osPriorityBelowNormal, 0, 512);
  MainControllerHandle = osThreadCreate(osThread(MainController), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartUsbTask */
/**
  * @brief  Function implementing the usbTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartUsbTask */
void StartUsbTask(void const * argument)
{
  /* init code for USB_HOST */
  MX_USB_HOST_Init();
  /* USER CODE BEGIN StartUsbTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartUsbTask */
}

/* USER CODE BEGIN Header_StartLogServer */
/**
* @brief Function implementing the logServerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLogServer */
void StartLogServer(void const * argument)
{
  /* USER CODE BEGIN StartLogServer */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLogServer */
}

/* USER CODE BEGIN Header_startUartServer */
/**
* @brief Function implementing the UartServer thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startUartServer */
void startUartServer(void const * argument)
{
  /* USER CODE BEGIN startUartServer */
  osStartUartServer();
  /* Infinite loop */

  /* USER CODE END startUartServer */
}

/* USER CODE BEGIN Header_StartMainApp */
/**
* @brief Function implementing the mainApp thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMainApp */
void StartMainApp(void const * argument)
{
  /* USER CODE BEGIN StartMainApp */
  osStartApp();
  /* Infinite loop */

  /* USER CODE END StartMainApp */
}

/* USER CODE BEGIN Header_StartMainController */
/**
* @brief Function implementing the MainController thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMainController */
void StartMainController(void const * argument)
{
  /* USER CODE BEGIN StartMainController */
  osStartMainController();
  /* Infinite loop */

  /* USER CODE END StartMainController */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
