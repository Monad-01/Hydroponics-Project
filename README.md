# Smart Hydroponic Monitoring System

## Overview

Welcome to the Smart Hydroponic Monitoring System repository! This project provides real-time insights into hydroponic environments for optimal plant growth.

## Features

- **Sensor Integration**: DHT20 and TDS sensors measure temperature, humidity, and Total Dissolved Solids (TDS) in the nutrient solution.
- **Data Visualization**: Real-time data is displayed on an LCD screen for monitoring temperature, humidity, and TDS levels.
- **Continuous Monitoring**: Regular sensor readings are processed and logged for detailed analytics.

## How It Works

The system takes regular readings from sensors and displays the information on an LCD screen. TDS values are logged and printed to the serial monitor every 5 seconds for detailed insights.

## Setup Instructions

1. **Hardware Connection**: Connect sensors and an LCD screen to the Arduino board following schematics.
2. **Code Deployment**: Upload the Arduino sketch (`Hydroponics-Monitoring.ino`) using the Arduino IDE.
3. **Real-Time Monitoring**: Power up the system to see real-time readings on the LCD screen.

## Repository Structure

- `Hydroponics-Monitoring.ino`: Main Arduino sketch.
- `libraries/`: Essential libraries for DHT20 and LiquidCrystal_I2C.

## Stretch Goals

- **Database Integration**: Upload real-time data to a database.
- **API Development**: Create an API to retrieve information from the database.
- **Web/Mobile Application**: Develop a user-friendly application to monitor garden status globally.


Anyone is able to freely explore and use this project for their own use.
 
