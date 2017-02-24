#ifndef INTERSECTION_H_
#define INTERSECTION_H_


class Intersetion
{
  private:
		int intersectionID;
		int centerPoint;
		string nameNS;
		string nameEW;

	public:
		bool isPointInIntersection();
		void upDate();
};

#endif
