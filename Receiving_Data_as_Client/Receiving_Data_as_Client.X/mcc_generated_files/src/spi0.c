/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/


#include "../include/spi0.h"

void SPI0_DefaultISR();

typedef struct spi0_descriptor_s {
    spi0_transfer_status_t    status;
    uint8_t *                           data;
    uint8_t                             size;
    spi0_transfer_type_t      type;
    spi0_interrupt_callback_t   interrupt_cb;
    spi0_transfer_done_cb_t   transfer_complete_cb;
} spi0_descriptor_t;

spi0_configuration_t spi0_configurations[] = {
    { 0x41, 0x0 }
};

static spi0_descriptor_t spi0_desc;

uint8_t SPI0_Initialize()
{
    //DORD enabled; MASTER disabled; CLK2X disabled; PRESC DIV4; ENABLE enabled; 
    SPI0.CTRLA = 0x41;

    //BUFEN disabled; BUFWR disabled; SSD disabled; MODE 0; 
    SPI0.CTRLB = 0x00;

    //RXCIE disabled; TXCIE disabled; DREIE disabled; SSIE disabled; IE enabled; 
    SPI0.INTCTRL = 0x01;

    spi0_desc.status = SPI0_FREE;
    spi0_desc.interrupt_cb     = SPI0_DefaultISR;

    //RXCIF disabled; IF disabled; TXCIF disabled; WRCOL disabled; DREIF disabled; SSIF disabled; BUFOVF disabled; 
    SPI0.INTFLAGS = 0x00;

    return 0;
}

void SPI0_Enable()
{
    SPI0.CTRLA |= SPI_ENABLE_bm;
}

void SPI0_Disable()
{
    SPI0.CTRLA &= ~SPI_ENABLE_bm;
}

bool SPI0_OpenConfiguration(uint8_t spiUniqueConfiguration){
    return SPI0_Open(spi0_configurations[spiUniqueConfiguration]);
}

bool SPI0_Open(spi0_configuration_t spiUniqueConfiguration)

{
    if (spi0_desc.status == SPI0_FREE) {
        spi0_desc.status = SPI0_IDLE;
        SPI0.CTRLA                = spiUniqueConfiguration.CTRLAvalue;
        SPI0.CTRLB                = spiUniqueConfiguration.CTRLBvalue;
        return true;
    } else {
        return false;
    }
}

void SPI0_Close(void)
{
    spi0_desc.status = SPI0_FREE;
}

/*
  Callback function is typically used to:
  In master mode: Release SS after transfer as finished.
  In slave mode: Implement SPI protocol, setting up next transfer
                 after the previous one (i.e. data transfer phase
                 after control/command phase).
*/
void SPI0_RegisterCallback(spi0_interrupt_callback_t f)
{
    spi0_desc.interrupt_cb = f;
}

/*
  Callback function is typically used to:
  In master mode: Release SS after transfer as finished.
  In slave mode: Implement SPI protocol, setting up next transfer
                 after the previous one (i.e. data transfer phase
                 after control/command phase).
*/

void SPI0_RegisterTransferDoneCallback(spi0_transfer_done_cb_t f)
{
    spi0_desc.transfer_complete_cb = f;
}

ISR(SPI0_INT_vect){
    if (spi0_desc.interrupt_cb != NULL) {
            spi0_desc.interrupt_cb();
        }
}

void SPI0_DefaultISR()
{
    /* SPI0_desc.data points to array element
       to write the received data to. The data to be transmitted
       is in the next array element.
    */
    uint8_t rdata = SPI0.DATA;
    uint8_t wdata = 0;

    SPI0.INTFLAGS = SPI_RXCIF_bm;

    if (spi0_desc.type != SPI0_WRITE) {
        *spi0_desc.data = rdata;
    }

    spi0_desc.data++;

    if (spi0_desc.type != SPI0_READ)
        wdata = *spi0_desc.data;

    spi0_desc.size--;
    // if more bytes to be transferred
    if (spi0_desc.size != 0) {
        // more data to send, send a byte
        SPI0.DATA = wdata;
    }

    // if last byte has been transferred, update status
    // and optionally call callback
    else {
        spi0_desc.status = SPI0_DONE;
        if (spi0_desc.transfer_complete_cb != NULL) {
            spi0_desc.transfer_complete_cb();
        }        
    }
}

bool SPI0_StatusFree()
{
    return (spi0_desc.status == SPI0_FREE);
}

bool SPI0_StatusIdle()
{
    return (spi0_desc.status == SPI0_IDLE);
}

bool SPI0_StatusBusy()
{
    return (spi0_desc.status == SPI0_BUSY);
}

bool SPI0_StatusDone()
{
    return (spi0_desc.status == SPI0_DONE);
}

uint8_t SPI0_ExchangeByte(uint8_t data)
{
    spi0_desc.data = (uint8_t*)&data;
    spi0_desc.size = 1;
    spi0_desc.type = SPI0_READ;
    spi0_desc.status = SPI0_BUSY;

    SPI0.DATA = *spi0_desc.data;
    while (spi0_desc.status == SPI0_BUSY);
    return data;
}

void SPI0_ExchangeBlock(void *block, size_t size)
{
    spi0_desc.data   = (uint8_t *)block;
    spi0_desc.size   = size;
    spi0_desc.type   = SPI0_EXCHANGE;
    spi0_desc.status = SPI0_BUSY;

    SPI0.DATA = *spi0_desc.data;
}

void SPI0_WriteBlock(void *block, size_t size)
{
    spi0_desc.data   = (uint8_t *)block;
    spi0_desc.size   = size;
    spi0_desc.type   = SPI0_WRITE;
    spi0_desc.status = SPI0_BUSY;

    SPI0.DATA = *spi0_desc.data;
}

void SPI0_ReadBlock(void *block, size_t size)
{
    spi0_desc.data   = (uint8_t *)block;
    spi0_desc.size   = size;
    spi0_desc.type   = SPI0_READ;
    spi0_desc.status = SPI0_BUSY;

    SPI0.DATA = 0;
}

void SPI0_WriteByte(uint8_t data)
{
    SPI0.DATA = data;
}

uint8_t SPI0_ReadByte()
{   
    return SPI0.DATA;

}