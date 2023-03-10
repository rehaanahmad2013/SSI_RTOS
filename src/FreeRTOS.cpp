#include <stdint.h>
#include "FreeRTOS.h"
#include "InterruptTimer.h"

static void (*input_fn[2])(void* rvParams);
static void* rvParams[2];
static uint32_t curidx = 0;
volatile uint32_t continueBit = 0;
volatile uint32_t currentBit = 0;
void myISR(){
    // digitalWrite(4, HIGH);
    continueBit = 1;
    currentBit += 1;
    digitalWrite(4, currentBit%2);
    // NVIC_DisableIRQ(TC3_IRQn);
    // TC.stopTimer();
}

void setTask(void (*code)(void* inpthis), void* inpthis){
    rvParams[curidx] = inpthis;
    input_fn[curidx] = code;
    curidx++;
}

void startTask() {
    Serial.println("setting timer");
    TC.startTimer(1000000, myISR);
    Serial.println("starting the rtos scheduler");
    while (true) {
        if (continueBit == 1) {
            Serial.println("timer int");
            Serial.println(currentBit);
            continueBit = 0;
            if (currentBit == 5) {
                TC.stopTimer();
                TC.startTimer(100000, myISR);
            }
            // digitalWrite(4, LOW);
        }
    }
    // for (uint32_t i = 0; i<curidx; i++) {
    //     input_fn[i](rvParams[i]);
    // }
}