#include "LineSegment.h"
#include "Library/Vector3.h"
#include <iostream>
#include <cmath>

bool LineSegment::isInsect(const LineSegment&)const{//�����ʂ��̃R���W����
	return true;
}

void LineSegment::setFirstPosition(const Vector3& a) {//�n�_�ƏI�_�̕ϐ���������֐�
	mFirstPosition = a;
}

void LineSegment::setEndPosition(const Vector3& a) {//�n�_�ƏI�_�̕ϐ���������֐�
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

