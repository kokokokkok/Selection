#ifndef INCLUDED_CIRCLE_H
#define INCLUDED_CIRCLE_H

#include <iostream>
#include <cmath>
#include "Library/Vector3.h"
class LineSegment{
public:
	bool isInsect(const LineSegment&)const;//線分通しのコリジョン
	void setFirstPosition(const Vector3&);//始点と終点の変数を代入する関数
	void setEndPosition(const Vector3&);//始点と終点の変数を代入する関数

	double Length(Vector3 mFirstPosition,Vector3 mEndPosition);
private:
	Vector3 mFirstPosition;//始点
	Vector3 mEndPosition;//終点
	
};


#endif // !INCLUDED_CIRCLE_H