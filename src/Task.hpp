#pragma once
#include "FreeRTOS.h"

template <int stackSize>
class Task { // This class is linked to EACH Task#.hpp/cpp file! As it is the parent of all these subclasses
    private:
        // TaskHandle_t taskHandle;
        // StaticTask_t xTaskBuffer;
        // StackType_t xStack[stackSize];
        uint8_t taskpriority;

    public:
        Task(uint8_t priority) {
            taskpriority = priority; 

            setTask(Task::TaskFunctionAdapter, this); // this is the RTOS function that actually takes in a task
        }

        // A "virtual" function means it must be implemented by the child class (Ex. Task1, Task2)
        virtual void activity()
        {
        };

        void suspend(void){
        }

        void resume(void){
        }

        static void TaskFunctionAdapter(void* pvParameters) //pvParameters is "this" --> this function essentially used to pass in "activity"
        {
            Task *task = static_cast<Task *>(pvParameters); // creates a static version of the Task# class just created
            task->activity(); // gets the activity
        }
};