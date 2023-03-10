#ifndef SAMD51_ISR_Timer_h
#define SAMD51_ISR_Timer_h

class TC_Timer {
  public:
    void startTimer(unsigned long period, void (*f)());
    void stopTimer();
    void restartTimer(unsigned long period);
    void setPeriod(unsigned long period);
};

extern TC_Timer TC;

#endif