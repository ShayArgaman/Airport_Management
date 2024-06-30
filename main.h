#pragma once
#include "AirportManager.h"
#include "Airline.h"

typedef enum
{
	eAddAirport, eAddPlane, eAddFlight, ePrintCompany, ePrintAirports,
	ePrintFlightsPlaneType, eSortFlight, eFindFlight, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Airport","Add Plane","Add Flight",
								"Print Airline", "Print all Airports",
								"Print all flights with plane type",
								"Sort Flight",
								"Find Flight" };

#define EXIT			-1
#define MANAGER_FILE_NAME "airport_authority.txt"
#define AIRLINE_FILE_NAME "airline.bin"


int menu();
int initManagerAndAirline(AirportManager* pManager, Airline* pCompany);

