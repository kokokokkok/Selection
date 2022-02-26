#include "Circle.h"
#include "Library/Vector3.h"

void Circle::setPosition(const Vector3& a) {
	mPosition = a;//�~��mPosition�ʒu�̒l���X�V
}

void Circle::setRadius(double a) {
	mRadius = a;//�~��mRadius���a�̈ʒu���X�V�@�����l����łłǂ̒��x�A�ڋ߂����ꍇ�ɔ��肳���邩�����܂�
}

bool Circle::isIntersect(const Circle& b)const {
	Vector3 difference;
	difference.setSub(mPosition, b.mPosition);//�Ԃ����Ă��鑊��Ɖ~�̈ʒu�𑫂�
	double squareDistance = difference.squareLength();//���ۂ̋�����2��
	double rSum = mRadius + b.mRadius;//�Ԃ����Ă��鑊��Ɖ~�̔��a�i���݂��̔���ɗ��p�����������j�𑫂�
	rSum *= rSum;//����ɗ��p������������2��
	return (squareDistance < rSum);//���ۂ̋��������肵�����������ڋ߂��Ă����ꍇ�ATure
}
void Circle::restrictMove(Vector3* v, const Circle& a)const {//v�͈ړ���
	Circle t = *this;//���̃I�u�W�F�N�g�̃|�C���^ ����̓����o�ϐ����g�����߂ɗ��p
	t.mPosition += *v; //�ړ�����t�ɉ~�I�u�W�F�N�g�i����̂��߂̉~�j�����A������ړ������āA�Փ˂���̂����肵�����I
	bool r = t.isIntersect(a);//�����ŏՓ˔���I�ړ�����t���ړ����I�������ɁA�Ԃ���Ώە�a�ƂԂ����Ă���̂�����I
	if (!r) {
		return;//�Ԃ����Ă��Ȃ��ꍇ�͉��������A�ړ�����t.mPosition���c��
	}
	//�Ԃ����Ă���ꍇ
	Vector3 d;
	d.setSub(mPosition, a.mPosition);
	double dotDV = d.dot(*v);// d*v
	double dLengrh2 = d.squareLength();// |d|*|d|
	d *= (dotDV / dLengrh2);// ( d*v / |d|*|d| ) * d
	*v -= d; // v - ( d*v / |d|*|d| ) * d
	/*
	d�̈ʒu�̗��҂̋����Ƃ����ꍇ�A
	���߂��������x�N�g��a��
	a = v -  ( d*v / |d|*|d| ) * d �ƂȂ�I
	*/



}