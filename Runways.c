#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "RunwayList.h"

struct outerNode* createOuterList()
{
	return NULL;
}

struct outerNode* createOuterNode(int value, struct innerNode* child)
{
	struct outerNode* temp = (struct outerNode*)malloc(sizeof(struct outerNode));
	if (temp != NULL)
	{
		temp->value = value;
		temp->numChildren = 0;
		temp->child = child;
		temp->next = NULL;
	}
	return temp;
}

void addOuterNode(struct outerNode** list, int value, struct innerNode* child)
{
	struct outerNode* temp = createOuterNode(value, child);

	temp->next = *list;
	*list = temp;
}

struct innerNode* createInnerList(struct outerNode** list)
{
	(*list)->child = NULL;
	return (*list)->child;
}

struct innerNode* createInnerNode(int value, int flightNo)
{
	struct innerNode* temp = (struct innerNode*)malloc(sizeof(struct innerNode));
	if (temp != NULL)
	{
		temp->value = value;
		temp->flightNo = flightNo;
		temp->next = NULL;
	}
	return temp;
}

void addInnerNode(struct outerNode* list, int value, int flightNo)
{
	struct innerNode* temp = createInnerNode(value , flightNo);
	if (list != NULL)
	{
		if (list->child != NULL)
		{
			temp->next = list->child;
		}
		else 
		{
			temp->next = NULL;
		}
		list->child = temp;
		list->numChildren += 1;
	}
}

void printInnerList(struct innerNode* list) 
{
	int count = 1;
	while (list != NULL)
	{
		printf("Flight BA %d has been waiting for %d tick(s)\n", list->flightNo, list->value);
		list = list->next;
		count++;
	}
}

void printOuterList(struct outerNode* list)
{
	while (list != NULL)
	{
		printf("Runway %d has %d plane(s)\n",list->value, list->numChildren);
		printInnerList(list->child);
		list = list->next;
	}
}

void addToNthList(struct outerNode* list, int n, int value, int flightNo)
{
	int offset = 0;
	struct outerNode* temp = list;

	while (offset < n && temp != NULL)
	{
		offset = offset + 1;
		temp = temp->next;
	}
	addInnerNode(temp, value, flightNo);
}

void incrementTime(struct innerNode* l)
{
	if (l == NULL)
	{
		// Error
		return;
	}
	while (l != NULL)
	{
		l->value++;
		l = l->next;
	}
}

void increment(struct outerNode* l)
{
	if (l == NULL)
	{
		// Error
		return;
	}
	while (l != NULL)
	{
		incrementTime(l->child);
		l = l->next;
	}
}

int lowestOccupiedRunway(struct outerNode* list, int index)
{
	int leastOccupied = 0;
	int lowestNumChildren;
	int i;

	leastOccupied = index;

	if (list != NULL)
	{
		lowestNumChildren = list->numChildren;
	}

	while (list != NULL)
	{
		i = list->numChildren;

		if (lowestNumChildren >= i)
		{
			lowestNumChildren = list->numChildren;
			leastOccupied = index - list->value;
		}

		list = list->next;
	}

	return leastOccupied;
}

void removeFromRunway(struct outerNode* oList)
{
	int children;

	struct innerNode* nextInList;
	struct innerNode* prevInList;


	while (oList != NULL)
	{
		children = oList->numChildren;
		
		if (oList->child != NULL)
		{

			if (children == 1)
			{
				oList->child = NULL;
			}
			else
			{
				nextInList = oList->child;
				prevInList = oList->child;
				while (nextInList->next != NULL)
				{
					nextInList = nextInList->next;
				}
				int position = 0;
				while (position < children - 2)
				{
					prevInList = prevInList->next;
					position++;
				}
				prevInList->next = nextInList->next;
			}
			oList->numChildren--;
		}
		oList = oList->next;
	}
}

int getNumChildren(struct outerNode* list, int index)
{
	int i = 0;
	int children = 0;

	while (list != NULL && i < index)
	{
		list = list->next;
		if (i == index)
		{
			children = list->numChildren;
		}
		i++;
	}

	return children;
}

//Incoming
struct incomingNode* createIncomingList()
{
	return NULL;
}

struct incomingNode* createIncomingNode(int fuel, int time, int wait, int runway, int flightNo, int passengers)
{
	struct incomingNode* temp = (struct incomingNode*)malloc(sizeof(struct incomingNode));
	if (temp != NULL)
	{
		temp->fuel = fuel;
		temp->time = time;
		temp->wait = wait;
		temp->runway = runway;
		temp->flightNo = flightNo;
		temp->passengerNo = passengers;
		temp->next = NULL;
	}
	return temp;
}

void addIncomingNode(struct incomingNode** list, int fuel, int time, int wait, int runway, int flightNo, int passengers)
{
	struct incomingNode* temp = createIncomingNode(fuel, time, wait, runway, flightNo, passengers);

	temp->next = *list;
	*list = temp;
}

void decrement(struct incomingNode * l, int index, int fuel, int time, int wait)
{
	if (l == NULL || index < 0)
	{
		// Error
		return;
	}
	// Find the node at the required index position
	int position = 0;
	while (l != NULL && position < index)
	{
		l = l->next;
		position++;
	}
	if (position < index)
	{
		// The specified index is greater than the list size, so exit
		return;
	}
	// Change the value in the node
	l->fuel = fuel;
	l->time = time;
	l->wait = wait; //Incrementing wait here for the sake of not needing another function
}

int getFuel(struct incomingNode* list, int index)
{
	int position = 0;
	while (list != NULL && position < index)
	{
		list = list->next;
		position++;
	}
	return list->fuel;
}

int getTime(struct incomingNode* list, int index)
{
	int position = 0;
	while (list != NULL && position < index)
	{
		list = list->next;
		position++;
	}
	return list->time;
}

int getWait(struct incomingNode* list, int index)
{
	int position = 0;
	while (list != NULL && position < index)
	{
		list = list->next;
		position++;
	}
	return list->wait;
}

int getRunway(struct incomingNode* l, int index)
{
	int position = 0;
	while (l != NULL && position < index)
	{
		l = l->next;
		position++;
	}
	return l->runway;
}

void setRunway(struct incomingNode* l, int index, int runway)
{
	if (l == NULL || index < 0)
	{
		// Error
		return;
	}
	// Find the node at the required index position
	int position = 0;
	while (l != NULL && position < index)
	{
		l = l->next;
		position++;
	}
	if (position < index)
	{
		// The specified index is greater than the list size, so exit
		return;
	}
	// Change the value in the node
	l->runway = runway;
}

int getFlightNo(struct incomingNode* l, int index)
{
	int position = 0;
	while (l != NULL && position < index)
	{
		l = l->next;
		position++;
	}
	return l->flightNo;
}

void removeIncoming(struct incomingNode *pList, int index)
{
	struct incomingNode *temp;
	struct incomingNode *previous;
	temp = pList;
	previous = pList;

	if (index != 0)
	{
		int position = 0;
		while (temp->next != NULL && position < index)
		{
			temp = temp->next;
			position++;
		}
		int position2 = 0;
		while (previous->next != NULL && position2 < index - 1)
		{
			previous = previous->next;
			position2++;
		}
		previous->next = temp->next;
	}
}

void removeFirst(struct incomingNode **head)
{
	struct incomingNode *temp = *head;
	if (temp == NULL)
	{
		return;
	}
	*head = temp->next;
	free(temp);
}

void value(int i)
{
	printf("%d ", i);
}

float probability(int lamda, int k)
{
	float e = pow(exp(1), -lamda);

	int kFact = 1;
	float prob;

	for (int i = 1; i <= k; i++)
	{
		kFact = kFact * i;
	}

	//calculating probability
	prob = (pow(lamda, k)*e) / kFact;

	return prob * 10000;
}

int main(int argc, char** argv)
{
	srand(time(NULL));

	int numberOfRunways;
	int ticks;
	int incoming, outgoing;
	int	currentTick = 0;
	int step = 0;
	int print = 0;
	float d1Prob[10], d2Prob[10], hour;
	int count = 0;
	int random;
	int planesGenerated = 0;
	int crashed = 0;
	int penalty = 0;
	int emergencyLand = 0;
	int lowestRunway, checkFlightNo, passengers;
	int flightNo = 0;
	int crashedHour, crashedMinute, expectedHour, expectedMinute, cTick;
	char *output;

	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
	}

	output = malloc(strlen(argv[5]) + 1);

	if (argc >= 6)
	{
		numberOfRunways = atoi(argv[1]);
		ticks = atoi(argv[2]);
		incoming = atoi(argv[3]);
		outgoing = atoi(argv[4]);
		strcpy(output, argv[5]);
		if (argc == 8)
		{
			step = atoi(argv[6]);
			print = atoi(argv[7]);
		}
	}

	FILE * fp;
	fp = fopen(output, "w");
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	struct outerNode* oList = createOuterList();
	struct incomingNode* incList = createIncomingList();

	for (int i = 0; i < numberOfRunways; i++)
	{
		addOuterNode(&oList, i, NULL);
	}

	for (int i = 0; i <= 9; i++)
	{
		d1Prob[i] = probability(incoming, i);
		d2Prob[i] = probability(outgoing, i);
	}

	for (currentTick = 1; currentTick <= ticks; currentTick++)
	{
		//Decrement fuel and time - Incoming
		for (int i = 0; i < count; i++)
		{
			int fuelValue = getFuel(incList, i);
			int timeValue = getTime(incList, i);
			int incWait = getWait(incList, i);
			
			if (timeValue > 0)
			{
				timeValue--;
			}
			else
			{
				incWait++;
			}

			fuelValue--;
			decrement(incList, i, fuelValue, timeValue, incWait);
		}

		lowestRunway = lowestOccupiedRunway(oList, numberOfRunways - 1);
		//Runway assignment of landing planes
		for (int i = 0; i < count; i++)
		{
			if (getTime(incList, i) == 0 && getRunway(incList, i) == -1)
			{

				if (lowestRunway < 0)
				{
					if (lowestRunway < 0 && i > 0)
					{
						lowestRunway = numberOfRunways - 1;
					}
				}
				if (lowestRunway <= numberOfRunways - 1)
				{
					setRunway(incList, i, lowestRunway);
				}
				lowestRunway--;
			}
		}

		//Increment wait time - Outgoing
		increment(oList);

 		if (print == 1 || currentTick == ticks)
		{
			printf("\nThe current tick is %d out of %d ticks. \n", currentTick, ticks);
			if (crashed == 1)
			{
				printf("No planes can land for %d ticks\n", penalty);
			}

			for (int i = 0; i < count; i++)
			{
				printf("Flight BA %d has %d fuel, is %d ticks away and has been waiting %d ticks. \n", getFlightNo(incList, i), getFuel(incList, i), getTime(incList, i), getWait(incList, i));
			}

			printf("\n");
			printOuterList(oList);
		}

		//Emergency landings
		for (int i = 0; i < count; i++)
		{
			crashedHour = 0;
			crashedMinute = 0;	
			cTick = currentTick;

			hour = (currentTick + getTime(incList, i)) / 60.0;
			expectedHour = (currentTick + getTime(incList, i)) / 60;
			expectedMinute = (hour - expectedHour) * 60;

			if (cTick < 60)
			{
				crashedMinute = cTick;
			}
			while (cTick > 60)
			{
				crashedHour++;
				cTick = cTick - 60;
				if (cTick < 60)
				{
					crashedMinute = cTick;
				}
			}

			if (getFuel(incList, i) < 0) //Crash landing
			{
				if (print == 1)
				{
					printf("Plane %d crashed. \n", getFlightNo(incList, i));
				}
				fprintf(fp, "CL BA %d %d:%d %d:%d %d\n", flightNo, expectedHour, expectedMinute, crashedHour, crashedMinute, passengers);
				if (i != 0)
				{
					removeIncoming(incList, i);
				}
				else
				{
					removeFirst(&incList);
				}
				
				count--;
				i--;

				if (crashed == 0)
				{
					penalty = 15;
				}

				crashed = 1;
			}
			else if (getFuel(incList, i) == 0 && getTime(incList, i) == 0 && crashed == 0 && emergencyLand == 0) //Emergency landing
			{
				if(print == 1)
				{					
					printf("Plane %d made an emergency landing. \n", getFlightNo(incList, i));
				}
				
				lowestRunway = lowestOccupiedRunway(oList, numberOfRunways - 1);
				addToNthList(oList, getRunway(incList, i), 0, getFlightNo(incList, i));
				fprintf(fp, "EL BA %d %d:%d %d:%d %d\n", flightNo, expectedHour, expectedMinute, crashedHour, crashedMinute, passengers);
				emergencyLand = 1;
				if (i != 0)
				{
					removeIncoming(incList, i);
					i--;
				}
				else 
				{
					removeFirst(&incList);
					i--;
				}
				count--;
			}
		}
		
		//Take off and landings
		//Take off
		if (emergencyLand == 0 && crashed == 0)
		{
			removeFromRunway(oList);
		}

		//Landings
		for (int i = 0; i < count; i++)
		{
			if (getTime(incList, i) <= 0 && penalty == 0 && count != 0 && emergencyLand == 0)
			{
				addToNthList(oList, getRunway(incList, i), 0, getFlightNo(incList, i));

				count--;
				if (i != 0)
				{
					removeIncoming(incList, i);
				}
				else
				{
					removeFirst(&incList);
				}
				i--;
			}
		}

		//Generation of planes coming to land
		int planesGenerated = 0;
		random = rand() % 10000;

		while (random > d1Prob[planesGenerated])
		{
			random = random - d1Prob[planesGenerated];
			planesGenerated++;
		}

		for (int i = 0; i < planesGenerated; i++)
		{
			checkFlightNo = 0;

			int timeOut = rand() % (100) + 1;
			int fuel = rand() % (100 - timeOut + 1) + timeOut;
			flightNo = rand() % (9999 - 1000) + 1000;
			passengers = rand() % (5000) + 1;

			for (int j = 0; j < count; j++)
			{
				if (flightNo == getFlightNo(incList, j))
				{
					checkFlightNo = 1;
					fprintf(fp, "ER BA %d\n", flightNo);
				}
			}
			if (checkFlightNo == 0)
			{
				expectedHour = 0;
				expectedMinute = 0;
				cTick = currentTick + getNumChildren(oList, lowestRunway);

				if (cTick < 60)
				{
					expectedMinute = cTick;
				}
				while (cTick > 60)
				{
					expectedHour++;
					cTick = cTick - 60;
					if (cTick < 60)
					{
						expectedMinute = cTick;
					}
				}

				addIncomingNode(&incList, fuel, timeOut, 0, -1, flightNo, passengers);
				count++;
				fprintf(fp, "EA BA %d %d:%d %d %d %d\n", flightNo, expectedHour, expectedMinute, passengers, timeOut , fuel);
			}
		}

		//Generation and runway assignment for planes that are taking off
		int groundPlanes = 0;
		random = rand() % 10000;

		while (random > d2Prob[groundPlanes])
		{
			random = random - d2Prob[groundPlanes];
			groundPlanes++;
		}

		for (int i = 0; i < groundPlanes; i++) 
		{
			flightNo = rand() % (9999 - 1000) + 1000;
			passengers = rand() % (5000) + 1;
			lowestRunway = lowestOccupiedRunway(oList, numberOfRunways - 1);

			//Calculating the Take off time
			expectedHour = 0;
			expectedMinute = 0;
			cTick = currentTick + getNumChildren(oList, lowestRunway);

			if (cTick < 60)
			{
				expectedMinute = cTick;
			}
			while (cTick > 60)
			{
				expectedHour++;
				cTick = cTick - 60;
				if (cTick < 60)
				{
					expectedMinute = cTick;
				}
			}
			fprintf(fp, "To BA %d %d:%d %d\n", flightNo, expectedHour, expectedMinute, passengers);

			addToNthList(oList, lowestRunway, 0, flightNo);
		}

		//decrement the penalty for a crash
		if (penalty > 0)
		{
			penalty--;
		}
		else
		{
			crashed = 0;

		}
		emergencyLand = 0;
		fprintf(fp, "+\n");
		
		if (step == 1)
		{
			getchar();
		}
	}

	printf("	=== Simulation Over === \n");
	fclose(fp);
}