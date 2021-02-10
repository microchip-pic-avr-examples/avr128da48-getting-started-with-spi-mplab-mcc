[![MCHP](images/microchip.png)](https://www.microchip.com)

# Getting Started with Serial Peripheral Interface (SPI) Examples (MPLAB® X)

This repository contains examples of MCC generated source code for Serial Peripheral Interface (SPI) as described in [TB3215-Getting Started with Serial Peripheral Interface (SPI)](https://ww1.microchip.com/downloads/en/AppNotes/TB3215-Getting-Started-with-SPI-90003215A.pdf) document from Microchip. The repository contains three MPLAB X projects inside:

* [<strong>Sending Data as Host:</strong>](Sending_Data_as_Host) This example demonstrates how to configure the device in SPI Host mode and send dummy data (value 0) (for more details, see [<strong>Sending Data as Host</strong>](Sending_Data_as_Host)).
* [<strong>Receiving Data as Client:</strong>](Receiving_Data_as_Client) This example illustrates how to configure the device in SPI Client mode and how to receive data from an SPI host device, using the SPI interrupt (for more details, [<strong>see Receiving Data as Client</strong>](Receiving_Data_as_Client)).
* [<strong>Changing Data Transfer Type:</strong>](Changing_Data_Transfer_Type) This example demonstrates how to configure the device in SPI Host mode and send data with respect to the clock polarity and the clock phase, in data mode 3 (for more details, [<strong>see Changing Data Transfer Type</strong>](Changing_Data_Transfer_Type)).

## Related Documentation
More details and code examples on the AVR128DA48 can be found at the following links:
- [TB3215-Getting Started with Serial Peripheral Interface (SPI)](https://ww1.microchip.com/downloads/en/AppNotes/TB3215-Getting-Started-with-SPI-90003215A.pdf)
- [AVR128DA48 Product Page](https://www.microchip.com/wwwproducts/en/AVR128DA48)
- [AVR128DA48 Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=avr128da48)
- [AVR128DA48 Project Examples in START](https://start.atmel.com/#examples/AVR128DA48CuriosityNano)

## Software Used
- MPLAB® X IDE 5.40 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.30 or a newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- MPLAB® Code Configurator (MCC) 4.0.1 or newer [(microchip.com/mplab/mplab-code-configurator)](https://www.microchip.com/mplab/mplab-code-configurator)
- MPLAB® Code Configurator (MCC) Device Libraries 8-bit AVR MCUs 2.5.0 or newer [(microchip.com/mplab/mplab-code-configurator)](https://www.microchip.com/mplab/mplab-code-configurator)
- AVR-Dx 1.4.75 or newer Device Pack

## Hardware Used
- AVR128DA48 Curiosity Nano [(DM164151)](https://www.microchip.com/Developmenttools/ProductDetails/DM164151)
