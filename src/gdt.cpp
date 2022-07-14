#include "gdt.h"

using namespace myos;
using namespace myos::common;

GlobalDescriptorTable::GlobalDescriptorTable()
    : nullSegmentDescriptor(0, 0, 0),
    unusedSegmentDescriptor(0, 0, 0),
    codeSegmentDescriptor(0, 64 * 1024 * 1024, 0x9a),
    dataSegmentDescriptor(0, 64 * 1024 * 1024, 0x92) {
    uint32_t i[2];
    i[1] = (uint32_t)this;
    i[0] = sizeof(GlobalDescriptorTable) << 16;
    // c++ 使用汇编  asm
    asm volatile("lgdt (%0)": :"p"(((uint8_t*)i) + 2));
}

GlobalDescriptorTable::~GlobalDescriptorTable() {}

uint16_t GlobalDescriptorTable::DataSegmentSelector() {
    return ((uint8_t*)&dataSegmentDescriptor - (uint8_t*)this) << 3;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector() {
    return ((uint8_t*)&codeSegmentDescriptor - (uint8_t*)this) << 3;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type) {
    // 获取描述符首地址
    uint8_t* target = (uint8_t*)this;
    // 判断是否需要使用页作为最小单位
    // 如果段的字节数不足1048576，则最小单位是字节，否则为页
    if (limit < 1048576) {
        // 寻找到flags_limit_hi字段
        // 将最小单位设置为字节
        // 使用32位段
        target[6] = 0x40;
    } else {
        // 如果最后4KB不足则需要缺失一页
        // 将limit转化为4KB的页面数
        if ((limit & 0xfff) != 0xfff) {
            limit = (limit >> 12) - 1;
        } else {
            limit = limit >> 12;
        }
        // 将最小单位设置为页
        target[6] = 0xC0;
    }

    // 此时limit是20位的
    // limit字段低8位取limit的后8位
    target[0] = limit & 0xff;
    // limit字段低16位的后8位
    target[1] = (limit >> 8) & 0xff;
    // limit字段高位
    target[6] |= (limit >> 16) & 0xf;

    // base字段低16位的前8位
    target[2] = base & 0xff;
    // base字段低16位的后8位
    target[3] = (base >> 8) & 0xff;
    // base字段的次高位
    target[4] = (base >> 16) & 0xff;
    // base字段的最高位
    target[7] = (base >> 24) & 0xff;

    // type字段
    target[5] = type;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base() {
    // 获取当前对象的首地址
    uint8_t* target = (uint8_t*)this;
    // 从最高位开始获取，并进行左移
    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];
    return result;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit() {
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[6] & 0xf;
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if ((target[6] & 0xC0) != 0xC0) {
        result = (result << 12) | 0xfff;
    }
    return result;
}
