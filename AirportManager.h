#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "GeneralList.h"
#include "Airport.h"

#define ERROR 0
#define FROM_FILE 1
#define FROM_USER 2

typedef struct
{
	LIST		airportList;
}AirportManager;

int		initManager(AirportManager* pManager, const char* fileName);
int		addAirport(AirportManager* pManager);
int		initAirport(Airport* pPort, AirportManager* pManager);
int		insertNewAirportToList(LIST* pProductList, Airport* pPort);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
int		checkUniqeCode(const char* code, const AirportManager* pManager);
void	printAirports(const AirportManager* pManager);
int		getAirportcount(const AirportManager* pManager);

int		saveManagerToFile(const AirportManager* pManager, const char* fileName);
int		loadManagerFromFile(AirportManager* pManager, const char* fileName);


void	freeManager(AirportManager* pManager);

#endif