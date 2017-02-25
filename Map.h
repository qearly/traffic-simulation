#ifndef MAP_H_
#define MAP_H_

class Map
{
	private:
		

	public:
		vector<Road*>roadCollection;
		vector<Intersection*>intersectCollection;
		Map(TrafficSimDataParser *dp);
		~Map();
		Road *getRoad(char *rdID);
		Road *getRoad(double x, double y, double dir);
		void addIntersection(Intersection *i);
		Intersection *getIntersection(int id);
		Intersection *getNextIntersection(double x, double y, double dir);
		Intersection *getIntersection(double x, double y);
		void PrintReport();
		void upDate(double time);
};

#endif
