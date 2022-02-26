#ifndef INCLUDED_CIRCLE_H
#define INCLUDED_CIRCLE_H

#include "Library/Vector3.h"
class Circle {
public:
	bool isIntersect(const Circle&)const;//�������Ă���̂����肵2�l�ŕς���
	void setPosition(const Vector3&);
	void setRadius(double);

	//�Փ˂��Ă���ꍇ�ɁA�����x�N�g�����v�Z����֐�
	void restrictMove(Vector3* moveVectorInOut, const Circle&)const;
//private
	Vector3 mPosition;
	double mRadius;
};
#endif // !INCLUDED_CIRCLE_H
