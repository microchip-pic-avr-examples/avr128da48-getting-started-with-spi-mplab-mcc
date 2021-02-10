
[![MCHP](../images/microchip.png)](https://www.microchip.com)

 # Sending Data as Host

This example shows how to configure the device in SPI Host mode, control a client and send dummy data (value 0).

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

## Setup
The AVR128DA48 Curiosity Nano Development Board is used as a test platform.

<br><img src="../images/AVR128DA48_CNANO_instructions.PNG" width="500">

The following configurations must be made for this project:

- System clock is configured at 3.33 MHz
- SPI
  - SPI clock configured at 416.66 kHz
  - SPI in Host mode
  - Data mode 0
  - LSB transmitted first
  - Clock Double enabled
  - SCK - PA6, SS - PA7, MOSI - PA4, MISO - PA5

|Pin                       | Configuration      |
| :---------------------:  | :----------------: |
|         PA4 (MOSI) 	     |   Digital output   |
|         PA5 (MISO) 	     |   Digital input    |
|         PA6 (SCK) 	     |   Digital output   |
|         PA7 (SS) 	       |   Digital output   |

## Operation

1.  Connect the board to the PC.

2.  Open the Sending_Data_as_Host.X project in MPLAB® X IDE.

3.  Set the Sending_Data_as_Host.X project as the main project. Right click the project in the **Projects** tab and click **Set as Main Project**.

<br><img src="../images/Set_as_Main_Project.PNG" height="500">

4.  Clean and build the Sending_Data_as_Host.X project. Right click the **Sending_Data_as_Host.X** project and select **Clean and Build**.

<br><img src="../images/Clean_and_Build.PNG" height="500">

5.  Select **AVR128DA48 Curiosity Nano** in the Connected Hardware Tool section of the project settings:

- Right click the project and click **Properties**;
- Click the arrow under the Connected Hardware Tool;
- Select **AVR128DA48 Curiosity Nano** (click the **SN**), click **Apply** and then click **OK**:

<br><img src="../images/Tool_Selection.PNG" height="400">

6.  Program the project to the board. Right click the project and then click **Make and Program Device**.

<br><img src="../images/Make_and_Program_Device.PNG" height="500">

## Demo

The image below shows the MOSI (PA4), SCK (PA6) and SS (PA7) signals captured by a logic analyzer. Every time the client is selected (SS line low), the device outputs the SCK signal and sends `0x00` through MOSI line.
<br><img src="images/demo.png" width="900">

## Summary

This example showed how to configure the device in SPI Host mode, control a client and send dummy data (value `0x00`).
