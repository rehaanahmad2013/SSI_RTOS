#include <stdint.h>
#include "FreeRTOS.h"

static void (*input_fn[2])(void* rvParams);
static void* rvParams[2];
static uint32_t curidx = 0;

void setTask(void (*code)(void* inpthis), void* inpthis){
    rvParams[curidx] = inpthis;
    input_fn[curidx] = code;
    curidx++;
}

void startTask() {
    
    for (uint32_t i = 0; i<curidx; i++) {
        input_fn[i](rvParams[i]);
    }
}