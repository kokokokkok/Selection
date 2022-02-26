#include "LineSegment.h"
#include "Library/Vector3.h"
#include <iostream>
#include <cmath>

bool LineSegment::isInsect(const LineSegment&)const{//線分通しのコリジョン
	return true;
}

void LineSegment::setFirstPosition(const Vector3& a) {//始点と終点の変数を代入する関数
	mFirstPosition = a;
}

void LineSegment::setEndPosition(const Vector3& a) {//始点と終点の変数を代入する関数
	mEndPosition = a;
}
double LineSegment::Length(Vector3 mFirstPosition, Vector3 mEndPosition) {
	double Length;
	double zLength;
	double yLength;
	double xLength;
	zLength = std::pow(mEndPosition.z - mFirstPosition.z,2);
	yLength = std::pow(mEndPosition.y - mFirstPosition.y, 2);
	xLength = std::pow(mEndPosition.x - mFirstPosition.x, 2);
	Length = sqrt(zLength + yLength + xLength);

	return Length;
}

