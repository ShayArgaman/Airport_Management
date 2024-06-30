#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AirportManager.h"
#include "General.h"

int	initManager(AirportManager* pManager, const char* fileName)
{

	if (loadManagerFromFile(pManager, fileName))
		return FROM_FILE;

	printf("-----------  Init airport Manager ---- User\n");
	if (!L_init(&pManager->airportList))
		return ERROR;


	return FROM_USER;
}

int	addAirport(AirportManager* pManager)
{
	Airport* pPort  = (Airport*)calloc(1, sizeof(Airport));
	if (!pPort)
		return 0;

	if (!initAirport(pPort, pManager))
	{
		freeAirport(pPort); //will free also pPort
		return 0;
	}

	return insertNewAirportToList(&pManager->airportList, pPort);
}

int		insertNewAirportToList(LIST* pProductList, Airport* pPort)
{
	NODE* pN = pProductList->head.next; //first Node
	NODE* pPrevNode = &pProductList->head;
	Airport* pTemp;
	int compRes;
	while (pN != NULL)
	{
		pTemp = (Airport*)pN->key;
		compRes = strcmp(pTemp->code, pPort->code);
		if (compRes == 0) //found a product with this name is cart
		{
			printf("Not new airport - error!!!\n");
			return 0;
		}

		if (compRes > 0) {//found a place for new item, the next one bigger	
			if (!L_insert(pPrevNode, pPort))
				return 0;
			return 1;
		}
		pPrevNode = pN;
		pN = pN->next;
	}
	//insert at end
	if (!L_insert(pPrevNode, pPort))
		return 0;
	return 1;
}

int  initAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	return initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{

	NODE* pN = pManager->airportList.head.next; //first Node
	if (!pN)
		return NULL;

	Airport* pTemp;
	int compRes;
	while (pN != NULL)
	{
		pTemp = (Airport*)pN->key;
		compRes = strcmp(pTemp->code, code);
		if (compRes == 0)
			return pTemp;
		if (compRes > 1) //not fount
			return NULL;
		pN = pN->next;
	}
	
	return NULL;
}

int checkUniqeCode(const char* code,const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}



int		getAirportcount(const AirportManager* pManager)
{
	int count = 0;
	NODE* pN = pManager->airportList.head.next; //first Node

	while (pN != NULL)
	{
		count++;
		pN = pN->next;
	}
	return count;
}

void	printAirports(const AirportManager* pManager)
{
	int count = getAirportcount(pManager);
	printf("there are %d airports\n", count); 
	L_print(&pManager->airportList, printAirportV);
	
}

int	saveManagerToFile(const AirportManager* pManager, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "w");
	if (!fp) {
		printf("Error open airport manager file to write\n");
		return 0;
	}

	int count = getAirportcount(pManager);
	fprintf(fp, "%d\n", count);
	if (count > 0)
	{
		NODE* pN = pManager->airportList.head.next; //first Node

		Airport* pTemp;
		while (pN != NULL)
		{
			pTemp = (Airport*)pN->key;
			if (!saveAirportToFile(pTemp, fp))
			{
				printf("Error write airport\n");
				fclose(fp);
				return 0;
			}
			pN = pN->next;
		}

	}

	fclose(fp);
	return 1;
}

int		loadManagerFromFile(AirportManager* pManager, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("Error open airport manager file\n");
		return 0;
	}

	L_init(&pManager->airportList);
	int count;
	fscanf(fp, "%d", &count);
	//clean the buffer
	fgetc(fp);
	
	Airport* pPort;
	//NODE* pN = &pManager->airportList.head;
	for (int i = 0; i < count; i++)
	{
		pPort = (Airport*)calloc(1, sizeof(Airport));
		if (!pPort)
			break;
		if (!loadAirportFromFile(pPort, fp))
		{
			printf("Error loading airport from file\n");
			fclose(fp);
			return 0;
		}
		//pN = L_insert(pN, pPort);
		insertNewAirportToList(&pManager->airportList, pPort);
	}

	fclose(fp);
	return 1;
}


void	freeManager(AirportManager* pManager)
{
	L_free(&pManager->airportList, freeAirportV);
}