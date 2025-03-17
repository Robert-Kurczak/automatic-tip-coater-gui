# Automatic Tip Coater GUI

## Description

Proof of concept for a Graphical User Interface for LCD TFT display, being a part of Automatic Tip Coater project.
GUI will consist of tile-based navigation system, providing a way to set various parameters such as motors speed or heater temperature.
User input will be read via touch panel integrated into the display module.
Display will be controller by the STM32 microcontroller.

## Technologies

### Software:
* C/C++ - Microcontroller software
* CMake - Build system
* STM32CubeMX - Configuring low level peripherals, like registers, clocks or interfaces of STM32 microcontroller
* Touch GFX / LVGL - low level graphics library for creating UI elements
### Hardware:
* LCD TFT Display (parallel RGB / intel 8080)
* Touch screen (I2C / SPI)
* STM32 maincontroller (F4 / F7 / H7)

## Schedule
* [19.03.2025] - Research on display technologies, their interfaces and communication protocols. Selecting the target display module.
* [26.03.2025] - Research on embedded graphics libraries (Touch GFX or LVGL), their hardware requirements (Flash, RAM, Clock), overall responsivnes. Research on UI architectural patterns (Model-View-ViewModel, Model-View-Presenter etc.) Choosing the library, creating example tiled navigation system and running it in a PC simulator.
* [02.04.2025] - Designing UI
* [09.04.2025] - Designing UI
* [16.04.2025] - Implementing designed interface using choosen library nad PC simulator
* [23.04.2025] - Implementing designed interface using choosen library nad PC simulator
* [30.04.2025] - Implementing designed interface using choosen library nad PC simulator
* [07.05.2025] - Choosing proper STM32 MCU based on created GUI requirements (memory and speed). Configuring project to run on choosen microcontroller. Flashing development board with choosen controller (STM Nucleo) with implemented solution.
* [14.05.2025] - Wiring display module with STM development board
* [21.05.2025] - Debugging why the code doesn't work on target platform
* [28.05.2025] - Implementing event system and some dummy handlers for all of the interactions
* [04.06.2025] - Testing
* [11.06.2025] - Testing
