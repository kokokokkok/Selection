#ifndef INCLUDED_CIRCLE_H
#define INCLUDED_CIRCLE_H

#include <iostream>
#include <cmath>
#include "Library/Vector3.h"
class LineSegment{
public:
	bool isInsect(const LineSegment&)const;//�����ʂ��̃R���W����
	void setFirstPosition(const Vector3&);//�n�_�ƏI�_�̕ϐ���������֐�
	void setEndPosition(const Vector3&);//�n�_�ƏI�_�̕ϐ���������֐�

	double Length(Vector3 mFirstPosition,Vector3 mEndPosition);
private:
	Vector3 mFirstPosition;//�n�_
	Vector3 mEndPosition;//�I�_
	
};


#endif // !INCLUDED_CIRCLE_H