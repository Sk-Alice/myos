#ifndef __MYOS_HARDWARECOMMUNICATION__PCI_H
#define __MYOS_HARDWARECOMMUNICATION__PCI_H

#include "hardwarecommunication/port.h"
#include "common/types.h"
#include "hardwarecommunication/interrupts.h"
#include "drivers/driver.h"

namespace myos 
{
    namespace hardwarecommunication 
    {
        class PeripheralComponentInterconnectDeviceDescriptor {
        public:
            PeripheralComponentInterconnectDeviceDescriptor();
            ~PeripheralComponentInterconnectDeviceDescriptor();

            myos::common::uint32_t portBase;
            myos::common::uint32_t interrupt;

            myos::common::uint8_t bus;
            myos::common::uint8_t device;
            myos::common::uint8_t function;

            myos::common::uint16_t device_id;
            myos::common::uint16_t vendor_id;

            myos::common::uint8_t class_id;
            myos::common::uint8_t subclass_id;
            myos::common::uint8_t interface_id;
            myos::common::uint8_t revision;
        };

        class PeripheralComponentInterconnectController {
        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();

            myos::common::uint32_t Read(myos::common::uint8_t bus,
                    myos::common::uint8_t device,
                    myos::common::uint8_t function,
                    myos::common::uint8_t registerOffset);

            void Write(myos::common::uint8_t bus,
                    myos::common::uint8_t device,
                    myos::common::uint8_t function,
                    myos::common::uint8_t registerOffset,
                    myos::common::uint32_t value);
            
            bool DeviceHasFuncions(myos::common::uint8_t bus, myos::common::uint8_t device);
            void SelectDrivers(myos::drivers::DriverManager* driverManager);
        
            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(myos::common::uint8_t bus,
                    myos::common::uint8_t device,
                    myos::common::uint8_t function);
        private:
            Port32Bit dataPort;
            Port32Bit commandPort;
        };
    }
}

#endif