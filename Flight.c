#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"
#include "fileHelper.h"


void	initFlight(Flight* pFlight,Plane* thePlane, const AirportManager* pManager)
{
	Airport* pPortOr = setAiportToFlight(pManager, "Enter code of origin airport:");
	strcpy(pFlight->sourceCode, pPortOr->code);
	int same;
	Airport* pPortDes;
	do {
		pPortDes = setAiportToFlight(pManager, "Enter code of destination airport:");
		same = isSameAirport(pPortOr, pPortDes);
		if (same)
			printf("Same origin and destination airport\n");
	} while (same);
	strcpy(pFlight->destCode, pPortDes->code);
	pFlight->flightPlane = *thePlane;
	getCorrectDate(&pFlight->date);
}

int		isFlightFromSourceAirport(const Flight* pFlight, const char* code)
{
	if (strcmp(pFlight->sourceCode, code) == 0)
		return 1;
		
	return 0;
}


int		isFlightToDestAirport(const Flight* pFlight, const char* code)
{
	if (strcmp(pFlight->destCode, code) == 0)
		return 1;

	return 0;


}

int		isPlaneTypeInFlight(const Flight* pFlight, ePlaneType type)
{
	return (pFlight->flightPlane.type == type);
}


void	printFlight(const Flight* pFlight)
{
	printf("Flight From %s To %s\t",pFlight->sourceCode, pFlight->destCode);
	printDate(&pFlight->date);
	printf("\t");
	printPlane(&pFlight->flightPlane);
}

void	printFlightPtr(void* pFlightPtr)
{
	const Flight* temp = *(Flight**)pFlightPtr;
	printFlight(temp);
}

Airport* setAiportToFlight(const AirportManager* pManager, const char* msg)
{
	char code[MAX_STR_LEN];
	Airport* port;
	do
	{
		printf("%s\t", msg);
		getAirportCode(code);
		port = findAirportByCode(pManager, code);
		if (port == NULL)
			printf("No airport with this code - try again\n");
	} while (port == NULL);

	return port;
}

void	freeFlightPtr(void* pFlightPtr)
{
	Flight* temp = *(Flight**)pFlightPtr;
	free(temp);
}


int saveFlightToFile(const Flight* pF, FILE* fp)
{
	if (!writeCharsToFile(pF->sourceCode, IATA_LENGTH, fp, "Error write flight source code\n"))
		return 0;

	if (!writeCharsToFile(pF->destCode, IATA_LENGTH, fp, "Error write flight destination code\n"))
		return 0;

	if (!writeIntToFile(pF->flightPlane.serialNum, fp, "Error write plane SN\n"))
		return 0;

	if (!saveDateToFile(&pF->date, fp))
		return 0;

	return 1;
}


int loadFlightFromFile(Flight* pF, const AirportManager* pManager,Plane* planeArr, int planeCount, FILE* fp)
{
	memset(pF, 0, sizeof(Flight));
	if(!readCharsFromFile(pF->sourceCode, IATA_LENGTH, fp, "Error reading flight source code\n"))
		return 0;

	if (findAirportByCode(pManager, pF->sourceCode) == NULL)
	{
		printf("Airport %s  not in manager\n", pF->sourceCode);
		return 0;
	}

	if (!readCharsFromFile(pF->destCode, IATA_LENGTH, fp, "Error reading flight destination code\n"))
		return 0;

	if (findAirportByCode(pManager, pF->destCode) == NULL)
	{
		printf("Airport %s not in manager\n", pF->destCode);
		return 0;
	}

	int sn;
	if(!readIntFromFile(&sn,fp, "Error reading plane SN\n"))
		return 0;
	Plane* pPlane = findPlaneBySN(planeArr, planeCount,sn);
	if (!pPlane)
	{
		printf("Plane with SN %d not in airline\n", sn);
		return 0;
	}
	pF->flightPlane = *pPlane;

	if (!loadDateFromFile(&pF->date, fp))
		return 0;

	return 1;
}

int		compareFlightBySourceCode(const void* flight1, const void* flight2)
{
	const Flight* pFlight1 = *(const Flight**)flight1;
	const Flight* pFlight2 = *(const Flight**)flight2;
	return strcmp(pFlight1->sourceCode, pFlight2->sourceCode);

}

int		compareFlightByDestCode(const void* flight1, const void* flight2)
{
	const Flight* pFlight1 = *(const Flight**)flight1;
	const Flight* pFlight2 = *(const Flight**)flight2;
	return strcmp(pFlight1->destCode, pFlight2->destCode);

}

int		compareFlightByDate(const void* flight1, const void* flight2)
{
	const Flight* pFlight1 = *(const Flight**)flight1;
	const Flight* pFlight2 = *(const Flight**)flight2;


	return compareDate(&pFlight1->date, &pFlight2->date);


	return 0;
}