# ✈️ Airport Management

## Overview

This project aims to develop a flight data management system for an airline. The system handles data related to airports, flights, and airline information, including entities such as Airport and Flight, along with an Airport Manager to oversee airports.<br><br>

The system includes various functions for efficient management of flight data, encompassing flight details, aircraft types, and airport information.

## Features

### 🏢 **Airport Management**
- `isSameAirport`: Check if two airports are the same.<br>
- `isAirportName`: Verify if a given name matches an airport's name.<br>
- `addAirport`: Add a new airport to the system.<br>
- `findAirportByName`: Locate an airport by its name.<br><br>

### ✈️ **Flight Management**
- `isFlightFromSourceName`: Check if a flight departs from a specific source airport.<br>
- `isFlightToDestName`: Verify if a flight arrives at a specific destination airport.<br>
- `isPlaneCodeInFlight`: Determine if a specific plane code is used in a flight.<br>
- `isPlaneTypeInFlight`: Check if a specific plane type is used in a flight.<br>
- `addFlight`: Add a new flight to the system.<br>
- `doPrintFlightsWithPlaneCode`: Print flights that use a specific plane code.<br>
- `doPrintFlightsWithPlaneType`: Print flights that use a specific plane type.<br>
- `doCountFlightsFromName`: Count the number of flights departing from a specific airport.<br><br>

### 🏢 **Airline Management**
- Stores the company name, number of flights, and an array of flights.<br>
- Additional functions may be required to further optimize the system.<br><br>

## Getting Started

### Prerequisites

- **Java Development Kit (JDK) 8 or higher** or another programming language of your choice.<br>
- **An IDE or text editor** (e.g., Eclipse, IntelliJ IDEA, VSCode)<br><br>

### Installation

1. **Clone the Repository**:<br>
    ```bash
    git clone https://github.com/ShayArgaman/Airport_Management.git
    ```

2. **Navigate to the Project Directory**:<br>
    ```bash
    cd Airport_Management
    ```

3. **Open the Project in Your Preferred IDE**.<br><br>
    ```bash
    start Airport_Management.sln
    ```
    
### Usage

Once the application is running, you can:<br>
- Manage airport data and flight information.<br>
- Use the provided functions to query and update flight and airport details.<br><br>

## Project Structure

- `src/AirportManagement/`: Contains the source files for the system.<br>
  - `Airport.java`: Defines the Airport entity.<br>
  - `Flight.java`: Defines the Flight entity.<br>
  - `AirportManager.java`: Manages airport operations and interactions.<br>
  - `Airline.java`: Represents the airline with flights and company details.<br>
- `README.md`: This file.<br>
- `.gitignore`: Specifies files and directories to be ignored by Git.<br><br>

## Acknowledgments

- ✈️ Inspired by real-world flight management systems.<br>
- 🙌 Thanks to the open-source community for various resources and tools.
