#include "gui/widget.h"

using namespace myos::common;
using namespace myos::gui;

Widget::Widget(Widget* parent, int32_t x, int32_t y,
        int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b)
        : parent(parent),
          x(x),
          y(y),
          w(w),
          h(h),
          r(r),
          g(g),
          b(b) {}

Widget::~Widget() {}

void Widget::GetFocus(Widget* widget) 
{
    if (parent != nullptr) parent->GetFocus(widget);
}