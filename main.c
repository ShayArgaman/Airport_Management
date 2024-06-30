#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Airline.h"
#include "AirportManager.h"
#include "General.h"
#include "main.h"
#include "airlineFile.h"

int main()
{
	AirportManager	manager;
	Airline			company;

	if (!initManagerAndAirline(&manager, &company))
	{
		printf("error init");
		return;
	}

	int option;
	int stop = 0;
	
	do
	{
		option = menu();
		switch (option)
		{
		case eAddPlane:
			if (!addPlane(&company))
				printf("Error adding plane\n");
			break;

		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintFlightsPlaneType:
			doPrintFlightsWithPlaneType(&company);
			break;

		case eSortFlight:
			sortFlight(&company);
			break;

		case eFindFlight:
			findFlight(&company);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	saveManagerToFile(&manager, MANAGER_FILE_NAME);
	saveAirlineToFile(&company, AIRLINE_FILE_NAME);


	freeManager(&manager);
	freeCompany(&company);

	printf("before dump\n");
	_CrtDumpMemoryLeaks();
	return 1;
}

int initManagerAndAirline(AirportManager* pManager, Airline* pCompany)
{
	int res = initManager(pManager, MANAGER_FILE_NAME);
	if (!res)
	{
		printf("error init manager\n");
		return 0;
	}

	if (res == FROM_FILE)
		return initAirlineFromFile(pCompany, pManager, AIRLINE_FILE_NAME);
	else
		initAirline(pCompany);
	return 1;
}


int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for(int i = 0 ; i < eNofOptions ; i++)
		printf("%d - %s\n",i,str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}