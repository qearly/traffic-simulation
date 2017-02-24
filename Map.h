#ifndef MAP_H_
#define MAP_H_

class Map
{
  private:
		list<Road>*roadCollection;
		list<Intersection>intersectCollection;

	public:
		Map();
		~Map();
		void addRoad();
		void addIntersection();
		void PrintReport();
		void upDate();
};

#endif
