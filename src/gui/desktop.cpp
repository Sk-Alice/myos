#include "gui/desktop.h"

using namespace myos;
using namespace myos::common;
using namespace myos::gui;

Desktop::Desktop(int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b)
    : CompositeWidget(0, 0, 0, w, h, r, g, b),
      MouseEventHandler() 
{
    MouseX = w / 2, MouseY = h / 2;
}

Desktop::~Desktop() {}

void Desktop::Draw(GraphicsContext* gc)
{
    CompositeWidget::Draw(gc);

    for (int i = 0; i < 4; i++) {
        gc->PutPiexl(MouseX - i, MouseY, 0xff, 0xff);
        gc->PutPiexl(MouseX + i, MouseY, 0xff, 0xff);
        gc->PutPiexl(MouseX, MouseY - i, 0xff, 0xff);
        gc->PutPiexl(MouseX, MouseY + i, 0xff, 0xff);
    }
}

void Desktop::OnMouseDown(uint8_t button)
{
    CompositeWidget::OnMouseDown(MouseX, MouseY, button);
}

void Desktop::OnMouseUp(uint8_t button)
{
    CompositeWidget::OnMouseUp(MouseX, MouseY, button);
}