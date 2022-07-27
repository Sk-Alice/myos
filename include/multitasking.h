#ifndef __MYOS__MULTITASKING_H
#define __MYOS__MULTITASKING_H

#include "common/types.h"
#include "gdt.h"

namespace myos {
    struct CPUState {
        common::uint32_t eax, ebx, ecx, edx, esi, edi, ebp;

        common::uint32_t error, eip, cs, eflags, esp, ss;
    } __attribute__((packed));

    class Task {
        friend class TaskManager;
    public:
        Task(GlobalDescriptorTable* gdt, void entrypoint());
        ~Task();
    private:
        common::uint8_t stack[40096];
        CPUState* cpustate;
    };

    class TaskManager {
    public:
        TaskManager();
        ~TaskManager();
        bool AddTask(Task* task);
        CPUState* Schedule(CPUState* cpustate);
    private:
        Task* tasks[256];
        int numTasks;
        int currentTask;
    };
}

#endif