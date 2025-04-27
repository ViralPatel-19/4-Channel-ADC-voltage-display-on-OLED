
---

# 4-Channel ADC Voltage Display on OLED

## Overview

This project demonstrates how to read analog voltages from four channels using a microcontroller's Analog-to-Digital Converter (ADC) and display the measured voltages on an OLED screen. The implementation is done in C and is compatible with Infineon's PSoC™ microcontrollers using the ModusToolbox™ development environment.

## Features

- **Multi-Channel ADC Reading**: Reads analog voltages from four separate channels.
- **OLED Display Output**: Displays the measured voltages on a 0.96-inch OLED screen using the SSD1306 driver.
- **Modular Code Structure**: Organized code with separate files for OLED handling and main application logic.
- **Educational Purpose**: Serves as a practical example for understanding multi-channel ADC reading and OLED interfacing in embedded systems.

## Project Structure

```
4-Channel-ADC-voltage-display-on-OLED/
├── main.c             // Main application code
├── ssd1306.c          // OLED display driver implementation
├── ssd1306.h          // OLED display driver header
├── ssd1306_conf.h     // OLED display configuration
├── ssd1306_fonts.c    // Font data for OLED display
├── ssd1306_fonts.h    // Font header for OLED display
├── ssd1306_port.c     // Hardware abstraction layer for OLED
├── ssd1306_port.h     // Header for hardware abstraction
└── README.md          // Project documentation
```

## Requirements

- **Hardware**:
  - Infineon PSoC™ microcontroller development board (e.g., CY8CKIT-062-BLE)
  - 0.96-inch OLED display module with SSD1306 driver
  - Four analog voltage sources (e.g., potentiometers or sensors)
  - USB cable for programming and power

- **Software**:
  - [ModusToolbox™](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/) installed on your development machine
  - Serial terminal application (e.g., PuTTY, Tera Term) for UART communication (optional)

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/ViralPatel-19/4-Channel-ADC-voltage-display-on-OLED.git
```

### 2. Open the Project in ModusToolbox™

- Launch **ModusToolbox™**.
- Click on **"Import Application"**.
- Navigate to the cloned repository and select the project.

### 3. Configure the ADC and I2C Components

- Open the Device Configurator in ModusToolbox™.
- **ADC Configuration**:
  - Add and configure four ADC channels to read the analog voltages.
  - Assign the analog input pins connected to your voltage sources.
- **I2C Configuration**:
  - Add and configure an I2C master component to communicate with the OLED display.
  - Assign the appropriate SDA and SCL pins connected to the OLED.
- Save and generate the configuration.

### 4. Build and Program

- Build the project using the ModusToolbox™ IDE.
- Connect your development board via USB.
- Program the board using the **"Program"** option.

### 5. Observe the OLED Display

- After programming, the OLED display should show the voltages read from the four ADC channels.
- Adjust the input voltages to see real-time updates on the display.

## Understanding the Code

- **main.c**: Initializes the ADC and OLED components, reads analog voltages from the four channels, and updates the OLED display with the measured values.
- **ssd1306.c / ssd1306.h**: Implements functions to control the SSD1306 OLED display, including initialization, clearing the screen, setting cursor positions, and displaying text.
- **ssd1306_conf.h**: Contains configuration settings for the OLED display, such as screen dimensions and I2C address.
- **ssd1306_fonts.c / ssd1306_fonts.h**: Provides font data and definitions used for displaying characters on the OLED.
- **ssd1306_port.c / ssd1306_port.h**: Abstracts the hardware-specific I2C communication functions, allowing the OLED driver to interface with the microcontroller's I2C peripheral.

## Customization

- **Voltage Scaling**: Modify the code to scale the ADC readings to actual voltage values based on your system's reference voltage and ADC resolution.
- **Display Format**: Customize the OLED display layout to show additional information or change the formatting of the voltage readings.
- **Data Logging**: Extend the project to log the voltage readings over time or transmit them via UART for further analysis.

## License

This project is open-source and available for educational and personal development use. Please refer to the `LICENSE` file for more information.

## Acknowledgments

- **Developed by**: Viral Patel
- **Tools Used**: ModusToolbox™, Infineon PSoC™ microcontrollers.

Feel free to contribute to this project by submitting issues or pull requests. Your feedback and improvements are welcome!

--- 
