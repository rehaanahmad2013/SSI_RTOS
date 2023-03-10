#include <stdint.h>

void setTask(void (*code)(void* args), void* rvParams);
// void setTask(void (*code)(void));
void startTask();