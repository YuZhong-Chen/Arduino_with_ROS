#ifndef _BUTTON_H_
#define _BUTTON_H_

class BUTTON {
   public:
    BUTTON();

    void Init(int Pin);
    void UpdateStatus(int Pin);
    void UpdateStatus();

    bool Status;
    int Pin;
};

extern BUTTON Button[3];

#endif