.set MAGIC, 0x1badb002          # GRUB魔术块
.set FLAGS, (1<<0 | 1<<1)       # GRUB标志块
.set CHECKSUM, -(MAGIC + FLAGS) # 校验块

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern _kernelMain             # 导入kernelMain
.extern _callConstructors
.global loader

loader:
    mov $kernel_stack, %esp

    call _callConstructors
    push %eax
    push %ebx
    call _kernelMain

_stop:
    cli
    hlt
    jmp _stop

.section .bss
.space 2*1024*1024
kernel_stack:
