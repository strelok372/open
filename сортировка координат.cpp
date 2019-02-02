#include "stdafx.h"
#include <iostream>
#include <vector>
#include <ctime>

#define RADIAN (180/PI)
#define COUNT_POINT 15 //количество координат

struct gf_point
{
	int x, y;
};



int main()
{
	gf_point aaa[COUNT_POINT];

	for (int i = 0; i < COUNT_POINT; i++)
	{
		aaa[i].x = rand() % 30;
		aaa[i].y = rand() % 30;
	}

	printf("Neotsortirovannie koordinaty\n\n");

	for (int i = 0; i < COUNT_POINT; i++)
	{
		printf("[%d][%d]\n", aaa[i].x, aaa[i].y);
	}
	

	int MINX = aaa[1].x;
	for (int i = 0; i < COUNT_POINT; i++)
	{
		if (MINX > aaa[i].x)
			MINX = aaa[i].x;
	}
	printf("\nminimalnaia koordinata X = [%d]\n\n", MINX);
	



	for (int i = 0; i < COUNT_POINT; i++)
	{
		for (int x = i + 1; x < COUNT_POINT; x++)
		{
			if (aaa[i].x > aaa[x].x)
			{
				int m = aaa[i].x;
				aaa[i].x = aaa[x].x;
				aaa[x].x = m;
				int y = aaa[i].y;
				aaa[i].y = aaa[x].y;
				aaa[x].y = y;
			}
			if (aaa[i].x == aaa[x].x)
			{
				if (aaa[i].y > aaa[x].y)
				{
					int m = aaa[i].x;
					aaa[i].x = aaa[x].x;
					aaa[x].x = m;
					int y = aaa[i].y;
					aaa[i].y = aaa[x].y;
					aaa[x].y = y;
				}
			}
		}
	}





	for (int i = 0; i < COUNT_POINT; i++)
	{
		printf("[%d][%d]\n", aaa[i].x, aaa[i].y);
	}

	printf("\nOtsortirovano po X zatem po Y sohranena Y koordinata\n\n");

	return 0;
}


/*int MINY = aaa[1].y;
for (int i=0; i < COUNT_POINT;i++)
{
if (MINY > aaa[i].y)
MINY = aaa[i].y;
}*/