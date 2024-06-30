#pragma once
#include <stdio.h>
#include "Airport.h"
#include "Airline.h"

int		initAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName);
int		saveAirlineToFile(const Airline* pComp, const char* fileName);
int		createPlaneArr(Airline* pComp);
int		createFlightArr(Airline* pComp);
int		loadFlightArrFromFile(Airline* pComp, AirportManager* pManager, FILE* fp);