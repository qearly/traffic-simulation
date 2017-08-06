/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Map.h
*   Author: Matt Stewart
*   Desc: Map header file
*   Date: 3-19-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/

#ifndef MAP_H_
#define MAP_H_


#include <vector>
#include "Road.h"
#include "Intersection.h"
#include "TrafficSimDataParser.h"


class Map
{
	private:
		vector<Road*>rCollect;
		vector<Intersection*>iCollect;

	public:
		Map(char *filename);
		~Map();
		Road *getRoad(char *rdID);
		Road *getStartingRoad(char *rdID, char *filename);
		Road *getRoad(double x, double y, double dir);
		void addIntersection(Intersection *i);
		Intersection *getIntersection(int id);
		Intersection *getNextIntersection(double x, double y, double dir, char *roadName);
		Intersection *getIntersection(double x, double y);
		void PrintStatus();
		void upDate(double time);
};

#endif
