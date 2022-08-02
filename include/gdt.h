#ifndef __GDT_H
#define __GDT_H

#include "common/types.h"

namespace myos {
    class GlobalDescriptorTable {
    public:
        class SegmentDescriptor {
        public:
            // base 段的起始地址    limit 段的寻址最大范围    type 段的类型(访问权限)
            SegmentDescriptor(myos::common::uint32_t base, myos::common::uint32_t limit, myos::common::uint8_t type);
            myos::common::uint32_t Base();
            myos::common::uint32_t Limit();
        private:
            myos::common::uint16_t limit_lo;          // limit字段低位
            myos::common::uint16_t base_lo;           // base字段低位
            myos::common::uint8_t base_hi;            // base字段次高位
            myos::common::uint8_t type;               // type字段和其他标志
            myos::common::uint8_t flags_limit_hi;     // limit字段高位和其他标志
            myos::common::uint8_t base_vhi;           // base字段最高位
        } __attribute__((packed));      // 告诉编译器取消结构在编译过程中的优化对齐

        SegmentDescriptor nullSegmentDescriptor;
        SegmentDescriptor unusedSegmentDescriptor;
        SegmentDescriptor codeSegmentDescriptor;
        SegmentDescriptor dataSegmentDescriptor;

    public:
        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        myos::common::uint16_t CodeSegmentSelector();
        myos::common::uint16_t DataSegmentSelector();
    };
}

#endif