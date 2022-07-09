.set MAGIC, 0x1badb002          # GRUB魔数块
.set FLAGS, (1<<0 | 1<<1)       # GRUB标志块
.set CHECKSUM, -(MAGIC + FLAGS) # 校验块

# 下面的伪指令声明了Multiboot标准中的多引导项头
# 三个块都是32位字段
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
    cli         # 禁用中断
    hlt         # 禁用中断后使用hlt暂停CPU，以后无法再唤醒
    jmp _stop

.section .bss
.space 2*1024*1024
kernel_stack:
