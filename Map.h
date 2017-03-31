#ifndef MAP_H_
#define MAP_H_

class Map
{
	private:
		vector<Road*>rCollect;
		vector<Intersection*>iCollect;

	public:
		Map(char *filename);
		~Map();
		Road *getRoad(char *rdID);
		Road *getRoad(double x, double y, double dir);
		void addIntersection(Intersection *i);
		Intersection *getIntersection(int id);
		Intersection *getNextIntersection(double x, double y, double dir);
		Intersection *getIntersection(double x, double y);
		void PrintStatus();
		void upDate(double time);
};

#endif
