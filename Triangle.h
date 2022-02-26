#ifndef INCLUDED_TRIANGLE_H
#define INCLUDED_TRIANGLE_H

#include"Library/Vector3.h"

class Triangle{
public:
	double getIntersectionTime(const Vector3& linerBegin, const Vector3& lineVector)const;
	bool isIntersect(const Vector3& lineBegin, const Vector3& lineVector)const;
	bool restrictMove(Vector3* moveVectorInOut, const Vector3& position)const;
	//void restrictMove(Vector3* moveVectorInOut, const Vector3& position)const;

	void modifyMove(Vector3* moveVectorInout)const;
	void setPosition(const Vector3& p0, const Vector3& p1, const Vector3& p2);
private:
	Vector3 mPosition[3];
};
#endif