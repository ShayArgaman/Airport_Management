#pragma once

#define CODE_LENGTH 8
#define MIN_SN 1
#define MAX_SN 9999

typedef enum { 
	eCommercial, eCargo, eMilitary, eNofPlaneTypes 
} ePlaneType;


static const char* PlaneTypeStr[eNofPlaneTypes];

typedef struct
{
	int			serialNum;
	ePlaneType	type;
}Plane;

void			initPlane(Plane* pPlane, Plane* planeArr, int planeCount);
ePlaneType		getPlaneType();
const char*		GetPlaneTypeStr(int type); 
int			getPlaneSN(Plane* planeArr, int planeCount);
Plane*			findPlaneBySN(Plane* planeArr, int count, int sn);
int			isSerialNumUnique(Plane* planeArr, int planeCount, int num);
void			printPlane(const Plane* pPlane);
void			printPlaneV(void* val);
void 			freePlane(void* pPlane);

int			savePlaneToFile(const Plane* pPlane, FILE* fp);
int			loadPlaneFromFile(Plane* pPlane, FILE* fp);

