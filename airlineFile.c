#include <stdio.h>
#include <stdlib.h>
#include "Airline.h"
#include "Airport.h"
#include "General.h"
#include "fileHelper.h"
#include "airlineFile.h"


int	initAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open company file\n");
		return 0;
	}

	pComp->flightArr = NULL;

	pComp->name = readStringFromFile(fp, "Error reading company name\n");
	if (!pComp->name)
	{
		fclose(fp);
		return 0;
	}

	pComp->flightSortOpt = eNone;

	if (!readIntFromFile(&pComp->planeCount, fp, "Error reading plane count\n"))
	{
		free(pComp->name);
		fclose(fp);
		return 0;
	}

	if(!createPlaneArr(pComp))
	{
		printf("Alocation error\n");
		free(pComp->name);
		fclose(fp);
		return 0;
	}

	if (fread(pComp->planeArr, sizeof(Plane), pComp->planeCount, fp) != pComp->planeCount)
	{
		printf("Error reading plane array\n");
		free(pComp->planeArr);
		free(pComp->name);
		fclose(fp);
		return 0;
	}

	if (!readIntFromFile(&pComp->flightCount, fp, "Error reading flight count name\n"))
	{
		free(pComp->planeArr);
		free(pComp->name);
		fclose(fp);
		return 0;
	}


	if(!createFlightArr(pComp))
	{
		printf("Alocation error\n");
		free(pComp->planeArr);
		free(pComp->name);
		fclose(fp);
		return 0;
	}

	if (!loadFlightArrFromFile(pComp, pManager, fp))
	{
		free(pComp->planeArr);
		free(pComp->flightArr);
		free(pComp->name);
		fclose(fp);
		return 0;
	}

	fclose(fp);
	return 1;
}


int		saveAirlineToFile(const Airline* pComp, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (!fp) {
		printf("Error open copmpany file to write\n");
		return 0;
	}

	if (!writeStringToFile(pComp->name, fp, "Error write comapny name\n"))
	{
		fclose(fp);
		return 0;
	}


	if (!writeIntToFile(pComp->planeCount, fp, "Error write plane count\n"))
	{
		fclose(fp);
		return 0;
	}

	if (fwrite(pComp->planeArr, sizeof(Plane), pComp->planeCount, fp) != pComp->planeCount)
	{
		printf("Error write plane array\n");
		fclose(fp);
		return 0;
	}

	if (!writeIntToFile(pComp->flightCount, fp, "Error write flight count\n"))
	{
		fclose(fp);
		return 0;
	}

	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (!saveFlightToFile(pComp->flightArr[i], fp))
		{
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	return 1;
}


int		createPlaneArr(Airline* pComp)
{
	pComp->planeArr = (Plane*)malloc(pComp->planeCount * sizeof(Plane));
	if (!pComp->planeArr)
	{
		printf("Alocation error\n");
		return 0;
	}
	return 1;
}

int createFlightArr(Airline* pComp)
{
	if (pComp->flightCount > 0)
	{
		pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));
		if (!pComp->flightArr)
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	else
		pComp->flightArr = NULL;

	for (int i = 0; i < pComp->flightCount; i++)
	{
		pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
		if (!pComp->flightArr[i])
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	return 1;
}

int loadFlightArrFromFile(Airline* pComp, AirportManager* pManager, FILE* fp)
{

	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (!loadFlightFromFile(pComp->flightArr[i], pManager, pComp->planeArr,
			pComp->planeCount, fp))
		{
			return 0;
		}
	}
	return 1;
}