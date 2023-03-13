#include <stdint.h>
#include "FreeRTOS.h"
#include "InterruptTimer.h"
#include "os.h"

static void (*input_fn[2])(void* rvParams);
static void* rvParams[2];

static uint32_t curidx = 0;
volatile uint32_t continueBit = 0;
volatile uint32_t currentBit = 0;

volatile uint32_t toggle1 = 0;
volatile uint32_t toggle2 = 0;
volatile uint32_t toggle3 = 0;

static void task1_handler(void);
static void task2_handler(void);
static void task3_handler(void);

void HardFault_Handler(void)
{
	while(1);
}

void setTask(void (*code)(void* inpthis), void* inpthis){ // inpthis -> the specific class object created (ex. Task1). Refers to the 2000 bytes declared when initializing Task# (ex. class Task1 : public Task<2000>)
    rvParams[curidx] = inpthis;
    input_fn[curidx] = code; // code -> the entire TaskFunctionAdapter itself. By accessing this input_fn[idx], you can basically call the task activity defined in each Task#.cpp
    curidx++;
}

void startTask() {
	static os_stack_t stack1[128];
	static os_stack_t stack2[128];
	static os_stack_t stack3[128];

	os_init();

	os_task_init(&task1_handler, stack1, 128);
	os_task_init(&task2_handler, stack2, 128);
	os_task_init(&task3_handler, stack3, 128);
	
	/* Context switch every second: */
	os_start(SystemCoreClock); // the main part of context switching!

	/* The program should never reach there: */
	while (1);
}


static void task1_handler(void) // these task handlers are currnetly implemented to have a working version
{
	while (1) {
		__disable_irq();
		digitalWrite(1, toggle1);
        toggle1 = (toggle1+1)%2;
		__enable_irq();
		delay(100);
	}
}

static void task2_handler(void)
{
	while (1) {
		__disable_irq();
		digitalWrite(2, toggle2);
        toggle2 = (toggle2+1)%2;
		__enable_irq();
		delay(100);
	}
}

static void task3_handler(void)
{
	while (1) {
		__disable_irq();
		digitalWrite(3, toggle3);
        toggle3 = (toggle3+1)%2;
		__enable_irq();
		delay(100);
	}
}