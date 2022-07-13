#ifndef __KEY_BOARD_H
#define __KEY_BOARD_H

#include "types.h"
#include "interrupts.h"
#include "port.h"
#include "driver.h"

class KeyboardEventHandler {
public:
    KeyboardEventHandler();

    virtual void OnKeyDown(char);
    virtual void OnKeyUp(char);
};

class KeyBoardDriver : public InterruptHandler, public Driver {
public:
    KeyBoardDriver(InterruptManager* manager, KeyboardEventHandler* handler);
    ~KeyBoardDriver();
    virtual uint32_t HandleInterrupt(uint32_t esp);
    virtual void Activate();
private:
    Port8Bit dataport;
    Port8Bit commandport;

    KeyboardEventHandler* handler;
};

#endif