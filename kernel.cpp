#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "keyboard.h"
#include "mouse.h"
#include "driver.h"

void printf(const char* str) {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x = 0, y = 0;
    for (int i = 0; str[i]; i++) {
        switch (str[i]) {
        case '\n':
            y++;
            x = 0;
            break;

        default:
            VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xff00) | str[i];
            x++;
            break;
        }

        if (x >= 80) {
            x = 0;
            y++;
        }

        if (y >= 25) {
            for (y = 0; y < 25; y++) {
                for ( x = 0; x < 80; x++) {
                    VideoMemory[i] = (VideoMemory[i] & 0xff00) | ' ';
                }
            }
            x = 0, y = 0;
        }
    }
}

void printHex(uint8_t key) {
    char* foo = (char*)"00";
    char* hex = (char*)"0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0x0f];
    foo[1] = hex[key & 0x0f];
    printf((const char*)foo);
}

class PrintKeyboardEventHandler : public KeyboardEventHandler {
public:
    void OnKeyDown(char c) {
        char* foo = " ";
        foo[0] = c;
        printf(foo);
    }
};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors() {
    for (constructor* i = &start_ctors; i!= &end_ctors; i++) {
        (*i)();
    }
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber) {
    printf("Hello World!\n");
    printf("cc");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(0x20, &gdt);

    DriverManager drvManager;
    PrintKeyboardEventHandler kbhandler;

    KeyBoardDriver keyboard(&interrupts, &kbhandler);
    drvManager.AddDriver(&keyboard);

    MouseDriver mouse(&interrupts);
    drvManager.AddDriver(&mouse);

    drvManager.ActivateAll();

    interrupts.Activate();
    while(1);
}