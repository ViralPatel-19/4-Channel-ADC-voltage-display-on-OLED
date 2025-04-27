
#include "ssd1306_port.h"
//#include "cyhal.h"


cy_rslt_t rslt;

void deselectOLEDDisplay(void)
{
	//cyhal_gpio_write(P12_5,true);//dc pin
	Cy_GPIO_Write(CYBSP_D3_PORT, CYBSP_D3_PIN,1);
}

void selectOLEDDisplay(void)
{
	//cyhal_gpio_write(P12_5,false);//DC pin
	Cy_GPIO_Write(CYBSP_D3_PORT, CYBSP_D3_PIN,0);
}
void ssd1306_Reset(void)
{
	deselectOLEDDisplay();

	// Reset the OLED
	// HAL_GPIO_WritePin((GPIO_TypeDef*)SSD1306_Reset_Port, SSD1306_Reset_Pin, GPIO_PIN_RESET);
	  Cy_GPIO_Write(CYBSP_D2_PORT, CYBSP_D2_PIN, 0); // Pull RST low
	   Cy_SysLib_Delay(100);                          // Wait 100 ms
	   Cy_GPIO_Write(CYBSP_D2_PORT, CYBSP_D2_PIN, 1); // Pull RST high
	   Cy_SysLib_Delay(100);
}

void ssd1306_WriteCommand(uint8_t byte)
{
	selectOLEDDisplay();


	//cyhal_spi_send(&mSPI,byte);
	printf("%x\r\n",byte);
	Cy_SCB_SPI_Write(SCB6, byte);

	while (!Cy_SCB_SPI_IsTxComplete(SCB6))
	{}
	// De-select ssd1306
	deselectOLEDDisplay();
}

void ssd1306_WriteData(uint8_t* buffer, size_t buff_size)
{
	//selectOLEDDisplay();
	deselectOLEDDisplay();
	// Set ssd1306 in data mode
	/// HAL_GPIO_WritePin(SSD1306_DC_Port, SSD1306_DC_Pin, GPIO_PIN_SET); // data
	// rslt = cyhal_gpio_init(P7_0, CYHAL_GPIO_DIR_BIDIRECTIONAL, CYHAL_GPIO_DRIVE_PULLUP, true);
	//  cyhal_gpio_write(P7_0,true);
	// Write data to ssd1306
	// HAL_SPI_Transmit(&SSD1306_SPI_PORT, buffer, buff_size, HAL_MAX_DELAY);
	//cyhal_spi_transfer(&mSPI,buffer , buff_size, NULL, 0, 0);

	Cy_SCB_WriteArrayBlocking(SCB6, buffer, buff_size);
	while (!Cy_SCB_SPI_IsTxComplete(SCB6))
	{}
	// cyhal_spi_slave_write(&sSPI, buffer,&buff_size, 100);
	//cyhal_spi_send(&mSPI,buffer[buff_size]);
	//HAL_SPI_Transmit_DMA(&SSD1306_SPI_PORT, (uint8_t *)buffer, buff_size);
	// De-select ssd1306
	deselectOLEDDisplay();
}




