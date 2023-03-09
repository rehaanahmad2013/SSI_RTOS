#pragma once


template <int stackSize>
class Task {
    private:
        // TaskHandle_t taskHandle;
        // StaticTask_t xTaskBuffer;
        // StackType_t xStack[stackSize];
        uint8_t taskpriority;

    public:
        Task(uint8_t priority, const char *name) {
            taskpriority = priority; 
        }

        // A "virtual" function means it must be implemented by the child class
        virtual void activity()
        {
        };

        void suspend(void){
        }

        void resume(void){
        }
};