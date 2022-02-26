#ifndef INCLUDED_CIRCLE_H
#define INCLUDED_CIRCLE_H

#include "Library/Vector3.h"
class Circle {
public:
	bool isIntersect(const Circle&)const;//当たっているのか判定し2値で変えす
	void setPosition(const Vector3&);
	void setRadius(double);

	//衝突している場合に、合成ベクトルを計算する関数
	void restrictMove(Vector3* moveVectorInOut, const Circle&)const;
//private
	Vector3 mPosition;
	double mRadius;
};
#endif // !INCLUDED_CIRCLE_H
