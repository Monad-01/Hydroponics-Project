# Smart Hydroponic Monitoring System

## Overview

Welcome to the Smart Hydroponic Monitoring System repository! This project utilizes software and hardware integration to provide real-time insights into hydroponic environments, ensuring optimal conditions for plant growth.

## Features

- **Advanced Sensor Integration**: Utilizes DHT20 and TDS sensors to measure temperature, humidity, and Total Dissolved Solids (TDS) in the nutrient solution.

- **Data Visualization**: Real-time data is elegantly displayed on an LCD screen, offering a visually appealing interface for monitoring temperature, humidity, and TDS levels.

- **Continuous Monitoring**: Regular sensor readings are processed and logged, providing detailed analytics for precise control over nutrient concentration.

## How It Works

The system takes regular readings from the sensors and displays the information on an LCD screen. Additionally, TDS values are logged and printed to the serial monitor every 5 seconds, offering more detailed insights into the nutrient concentration over time.

## Setup Instructions

1. **Hardware Connection**: Connect the DHT20 sensor for temperature and humidity, the TDS sensor for nutrient concentration, and an LCD screen to the Arduino board following the provided schematics.

2. **Code Deployment**: Upload the Arduino sketch (`Hydroponics-Monitoring.ino`) to your Arduino board using the Arduino IDE.

3. **Real-Time Monitoring**: Power up the system, and you should see real-time readings on the LCD screen.

## Repository Structure

- `Hydroponics-Monitoring.ino`: The main Arduino sketch containing the code for the hydroponic monitoring system.

- `libraries/`: Houses essential libraries for DHT20 and LiquidCrystal_I2C.

## Stretch Goals

- **Database Integration**: Upload real-time data to a database

- **API Development**: Create an API to retrieve information from the database

- **Web/Mobile Application**: Develop a user-friendly web or mobile application to monitor garden status globally


Feel free to explore the project, contribute to its enhancement, and leverage it as a testament to your prowess in software development.
 
