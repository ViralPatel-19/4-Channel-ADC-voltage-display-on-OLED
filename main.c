#include "cyhal.h"
#include "cybsp.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306_port.h"
#include "ssd1306.h"
#include "cy_retarget_io.h"



void DisplayVoltageOnOLED(float voltage1,float voltage2,float voltage3,float voltage4)
{
    char buffer[20];
    snprintf(buffer, sizeof(buffer),  "channel-0 %0.1fV", voltage1);
    ssd1306_SetCursor(5, 2); // Set cursor to top-left
    ssd1306_UpdateScreen();
    Cy_SysLib_Delay(100);
    ssd1306_WriteString(buffer,Font_6x8 ,White);
    ssd1306_UpdateScreenp1(); // Update the OLED to show the new data

    char buffer1[20];
    snprintf(buffer1, sizeof(buffer1),  "channel-1 %0.1fV", voltage2);
	ssd1306_SetCursor(5, 10); // Set cursor to top-left
	ssd1306_UpdateScreen();
	Cy_SysLib_Delay(100);
	ssd1306_WriteString(buffer1,Font_6x8 ,White);
	ssd1306_UpdateScreenp2(); // Update the OLED to show the new data

	char buffer2[20];
	snprintf(buffer2, sizeof(buffer2),  "channel-2 %0.1fV", voltage3);
	 ssd1306_SetCursor(5, 20); // Set cursor to top-left
	 ssd1306_UpdateScreen();
	 Cy_SysLib_Delay(100);
	 ssd1306_WriteString(buffer2,Font_6x8 ,White);
	 ssd1306_UpdateScreenp3(); // Update the OLED to show the new data

	 char buffer3[20];
	snprintf(buffer3, sizeof(buffer3),  "channel-3 %0.1fV", voltage4);
	ssd1306_SetCursor(5, 30); // Set cursor to top-left
	ssd1306_UpdateScreen();
	Cy_SysLib_Delay(100);
	ssd1306_WriteString(buffer3,Font_6x8 ,White);
	ssd1306_UpdateScreenp4(); // Update the OLED to show the new data
}


int main(void)
{
	cy_rslt_t result;
	  cy_stc_scb_spi_context_t spiContext;

	result = cybsp_init();
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}
	__enable_irq();

	  result = cy_retarget_io_init_fc(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
				CYBSP_DEBUG_UART_CTS,CYBSP_DEBUG_UART_RTS,CY_RETARGET_IO_BAUDRATE);
		if (result != CY_RSLT_SUCCESS)
		{
			CY_ASSERT(0);
		}


	Cy_GPIO_Pin_Init(CYBSP_D2_PORT, CYBSP_D2_PIN, &CYBSP_D2_config);//RST
	Cy_GPIO_Pin_Init(CYBSP_D3_PORT, CYBSP_D3_PIN, &CYBSP_D3_config);//dc
	Cy_GPIO_Pin_Init(CYBSP_A0_PORT, CYBSP_A0_PIN, &CYBSP_A0_config);//P10_0
	Cy_GPIO_Pin_Init(CYBSP_A1_PORT, CYBSP_A1_PIN, &CYBSP_A1_config);//P10_1
	Cy_GPIO_Pin_Init(CYBSP_A2_PORT, CYBSP_A2_PIN, &CYBSP_A2_config);//P10_2
	Cy_GPIO_Pin_Init(CYBSP_A3_PORT, CYBSP_A3_PIN, &CYBSP_A3_config);//P10_
	Cy_SysAnalog_Init(&pass_0_aref_0_config);
	   	// Initialize AREF
	Cy_SysAnalog_Enable();
	 cy_en_sar_status_t status;
	    status = Cy_SAR_Init(SAR, &pass_0_sar_0_config);
	    if (CY_SAR_SUCCESS == status)
	    {
	        /* Turn on the SAR hardware. */
	        Cy_SAR_Enable(SAR);
	        /* Begin continuous conversions. */

	    }

	Cy_GPIO_Write(CYBSP_SPI_CS_PORT, CYBSP_SPI_CS_PIN,0);

	result = Cy_SCB_SPI_Init(SCB6, &scb_6_config, &spiContext);
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}
	Cy_SCB_SPI_Enable(SCB6);



	ssd1306_Init();
//	ssd1306_Fill(White);
//	ssd1306_UpdateScreen();
//	Cy_SysLib_Delay(100);
	//ssd1306_SetDisplayOn(0);

	            //initial data write on OLED

//	ssd1306_SetCursor(10,10);
//	ssd1306_UpdateScreen();
//	Cy_SysLib_Delay(100);
//	//ssd1306_Fill(Black);
//	ssd1306_WriteString("hii  :) :)", Font_6x8,White);
//	ssd1306_UpdateScreen();
//	Cy_SysLib_Delay(100);
//	ssd1306_Fill(White);
//	ssd1306_UpdateScreen();
//	Cy_SysLib_Delay(100);

	Cy_SAR_StartConvert(SAR,CY_SAR_START_CONVERT_CONTINUOUS);
	for (;;)
	{
		Cy_SAR_IsEndConversion(SAR, CY_SAR_WAIT_FOR_RESULT);
		 uint16_t adcValue1 = Cy_SAR_GetResult16(SAR,0);
		 uint16_t adcValue2 = Cy_SAR_GetResult16(SAR,1);
		 uint16_t adcValue3 = Cy_SAR_GetResult16(SAR,2);
		 uint16_t adcValue4 = Cy_SAR_GetResult16(SAR,3);
		 float voltage1 =  Cy_SAR_CountsTo_Volts(SAR, 0, adcValue1);
		 float voltage2 =  Cy_SAR_CountsTo_Volts(SAR, 1, adcValue2);
		 float voltage3 =  Cy_SAR_CountsTo_Volts(SAR, 2, adcValue3);
		 float voltage4 =  Cy_SAR_CountsTo_Volts(SAR, 3, adcValue4);

		// printf("%0.02f\r\n",voltage);
		 DisplayVoltageOnOLED(voltage1,voltage2,voltage3,voltage4);

		 Cy_SysLib_Delay(1000);

	}
}


