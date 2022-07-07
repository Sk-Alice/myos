#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
    : nullSegmentDescriptor(0, 0, 0),
    unusedSegmentDescriptor(0, 0, 0),
    codeSegmentDescriptor(0, 64 * 1024 * 1024, 0x9a),
    dataSegmentDescriptor(0, 64 * 1024 * 1024, 0x92) {
    uint32_t i[2];
    i[1] = (uint32_t)this;
    i[0] = sizeof(GlobalDescriptorTable) << 16;
    // c++ 使用汇编  asm
    asm volatile("lgdt (%0)": :"p"((uint8_t*)i) + 2)
}

GlobalDescriptorTable::~GlobalDescriptorTable() {}

uint16_t GlobalDescriptorTable::DataSegmentDescriptor() {
    return (uint8_t*)&dataSegmentDescriptor - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentDescriptor() {
    return (uint8_t*)&codeSegmentDescriptor - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type) {
    uint8_t* target = (uint8_t*)this;

    if(limit < 65536) {
        target[6] = 0x80;
    }
}

