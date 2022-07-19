#include "drivers/vga.h"

using namespace myos::common;
using namespace myos::drivers;

VideoGraphicsArray::VideoGraphicsArray() 
    : miscPort(0x32),
      crtcIndexPort(0x3d4),
      crtcDataPort(0x3d5),
      sequencerIndexPort(0x3c4),
      sequencerDataPort(0x3c5),
      graphicsControllerIndexPort(0x3ce),
      graphicsControllerDataPort(0x3cf),
      attributeControllerIndexPort(0x3c0),
      attributeControllerReadPort(0x3c1),
      attributeControllerWritePort(0x3c0),
      attributeControllerResetPort(0x3da) {}

namespace myos 
{
    namespace drivers 
    {
        class VideoGraphicsArray {
        public:
            VideoGraphicsArray();
            ~VideoGraphicsArray();

            bool SupportsModel(common::uint32_t height, common::uint32_t colordepth); 
            bool SetMode(common::uint32_t width, common::uint32_t height, common::uint32_t colordepth);
            void PutPixel(common::uint32_t x, common::uint32_t y, common::uint8_t r, common::uint8_t g, common::uint8_t b);
            void PutPixel(common::uint32_t x, common::uint32_t y, common::uint8_t colorIndex);
        private:
            hardwarecommunication::Port8Bit miscPort;
            hardwarecommunication::Port8Bit crtcIndexPort;
            hardwarecommunication::Port8Bit crtcDataPort;
            hardwarecommunication::Port8Bit sequencerIndexPort;
            hardwarecommunication::Port8Bit sequencerDataPort;
            hardwarecommunication::Port8Bit graphicsControllerIndexPort;
            hardwarecommunication::Port8Bit graphicsControllerDataPort;
            hardwarecommunication::Port8Bit attributeControllerIndexPort;
            hardwarecommunication::Port8Bit attributeControllerReadPort;
            hardwarecommunication::Port8Bit attributeControllerWritePort;
            hardwarecommunication::Port8Bit attributeControllerResetPort;

            void WriteRegisters(common::uint8_t* registers);
            common::uint8_t GetColorIndex(common::uint8_t r, common::uint8_t g, common::uint8_t b);
            common::uint8_t* GetFrameBufferSegment();
        };
    }
}

#endif