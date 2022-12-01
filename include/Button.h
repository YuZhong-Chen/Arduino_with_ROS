#ifndef _BUTTON_H_
#define _BUTTON_H_

class BUTTON {
   public:
    BUTTON();

    void Init(int Pin);
    void UpdateStatus(int Pin);
    void UpdateStatus();
    bool isEnable();

    int Pin;

   private:
    bool CurrentStatus;
    bool PreviousStatus;
};

extern BUTTON Button[3];

#endif