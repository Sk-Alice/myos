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
          b(b),
          Focussable(true) {}

Widget::~Widget() {}

void Widget::GetFocus(Widget* widget) 
{
  if (parent != nullptr) parent->GetFocus(widget);
}

void ModelToScrean(int32_t& x, int32_t& y)
{
  if (parent != nullptr) parent->ModelToScrean(x, y);
  x += this->x;
  y += this->y;
}

void Widget::Draw(GraphicsContext* gc)
{
  int X = 0, Y = 0;
  ModelToScrean(X, Y);
  gc->FillRectangle(X. Y, w, h, r, g, b);
}

void Widget::OnMouseDown(int32_t x, int32_t y)
{
  if (Focussable) GetFocus(this);
}

void Widget::OnMouseUp(int32_t x, int32_t y) {}

void Widget::OnMouseMove(int32_t x, int32_t y, int32_t nx, int32_t ny) {}

void Widget::OnkeyUp(char c) {}

void Widget::OnKeyDown(char c) {}

void Widget::ContainsCoordinate(int32_t x, int32_t y)
{
  return this->x <= x && this->y <= y && this->x + this->w > x && this->y + this->h > y;
}

CompositeWidget::CompositeWidget(Widget* parent, int32_t x, int32_t y,
        int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b)
        : Widget(parent, x, y, w, h, r, g, b), numClidren(0), focussedChild(0) {}

void CompositeWidget::GetFocus(Widget* widget)
{
  focussedChild = widget;
  if (parent != nullptr) parent->GetFocus(this);
}

void CompositeWidget::Draw(GraphicsContext* gc)
{
  Widget::Draw(gc);
  for (uint32_t i = numClidren - 1; ~i; i--) {
    children[i]->Draw(gc);
  }
}

void CompositeWidget::OnMouseDown(int32_t x, int32_t y)
{
  for (uint32_t i = 0; i < numClidren; i++) {
    if (children[i]->ContainsCoordinate(x - this->x, y - this->y)) {
      children[i]->OnMouseDown(x - this->x, y - this->y);
      break;
    }
  }
}

void CompositeWidget::OnMouseup(int32_t x, int32_t y)
{
  for (uint32_t i = 0; i < numClidren; i++) {
    if (children[i]->ContainsCoordinate(x - this->x, y - this->y)) {
      children[i]->OnMouseUp(x - this->x, y - this->y);
      break;
    }
  }
}

void CompositeWidget::OnMouseMove(int32_t x, int32_t y, int32_t nx, int32_t ny)
{
  int32_t firstChild = -1;
  for (int32_t i = 0; i < numClidren; i++) {
    if (children[i]->ContainsCoordinate(x - this->x, y - this->y)) {
      children[i]->OnMouseMove(x - this->x, y - this->y, nx - this->x, ny - this->y);
      firstChild = i;
      break;
    }
  }

  for (int32_t i = 0; i < numClidren; i++) {
    if (children[i]->ContainsCoordinate(nx - this->x, ny - this->y)) {
      if (firstChild != i) {
        children[i]->OnMouseMove(x - this->x, y - this->y, nx - this->x, ny - this->y);
        firstChild = i;
        break;
      }
    }
  }
}

void CompositeWidget::OnKeyDown(char c) 
{
  if (focussedChild != nullptr) {
    focussedChild->OnKeyDown(c);
  }
}

void CompositeWidget::OnKeyUp(char c) 
{
  if (focussedChild != nullptr) {
    focussedChild->OnKeyUp(c);
  }
}