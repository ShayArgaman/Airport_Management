#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"

typedef enum { eNone, eSourceCode, eDestCode, eDate, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt];

typedef struct
{
	char*		name;
	int			flightCount;
	Flight**	flightArr;
	eSortOption	flightSortOpt;
	int			planeCount;
	Plane*		planeArr;
}Airline;

void	initAirline(Airline* pComp);
int		addFlight(Airline* pComp,const AirportManager* pManager);
int		addPlane(Airline* pComp);
Plane*	FindAPlane(Airline* pComp);

void	sortFlight(Airline* pComp);
void	findFlight(const Airline* pComp);
eSortOption showSortMenu();

void	printCompany(const Airline* pComp);
void	printFlightArr(Flight** arr, int size);
void	printPlanesArr(Plane* arr,int size);
void	doPrintFlightsWithPlaneType(const Airline* pComp);

void	freeFlightArr(Flight** arr, int size);
void	freePlanes(Plane* arr, int size);
void	freeCompany(Airline* pComp);

#endif

