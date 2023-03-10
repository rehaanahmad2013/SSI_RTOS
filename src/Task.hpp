#pragma once
#include "FreeRTOS.h"

template <int stackSize>
class Task {
    private:
        // TaskHandle_t taskHandle;
        // StaticTask_t xTaskBuffer;
        // StackType_t xStack[stackSize];
        uint8_t taskpriority;

    public:
        Task(uint8_t priority) {
            taskpriority = priority; 

            setTask(Task::TaskFunctionAdapter, this);
        }

        // A "virtual" function means it must be implemented by the child class
        virtual void activity()
        {
        };

        void suspend(void){
        }

        void resume(void){
        }

        static void TaskFunctionAdapter(void* pvParameters)
        {
            Task *task = static_cast<Task *>(pvParameters);
            task->activity();
        }
};