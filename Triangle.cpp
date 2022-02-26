#include "Triangle.h"
#include "Library/Vector3.h"
#include <limits>
#include <iostream>

using namespace std;

void Triangle::setPosition(const Vector3& p0, const Vector3& p1, const Vector3& p2) {
	mPosition[0] = p0;//���_���W��z��ɓ��ꍞ��
	mPosition[1] = p1;
	mPosition[2] = p2;
}

double Triangle::getIntersectionTime(const Vector3& lineBegin, const Vector3& lineVector)const {
	double inf = numeric_limits<double>::max();

	const Vector3& a = lineBegin;//p = a + tb 1������ԂŃv���C���[�̈ړ� 
	const Vector3& b = lineVector;
	const Vector3& c = mPosition[0];// q = c + vd + ue 2������ԁ@�ŎO�p�`

	Vector3 d, e, f, n;
	d.setSub(mPosition[1], c);//
	e.setSub(mPosition[2], c);
	f.setSub(c,a);//���ꂼ��c-a���đ��
	n.setCross(d, e);//n*d - n*e  �@��

	double nf = n.dot(f);
	double nb = n.dot(b);
	if (nb == 0.f) {
		return inf;//�@t��nb�𕪕�ɓ���邽�߁A�ň��ł�0�ɂȂ�Ȃ��悤��
	}
	double t = nf / nb;
	if (t < 0 || t>1) {//t���O�`�P�Ɏ��܂�Ȃ��ƃA�E�g�I
		return inf;
	}
	//�������炖��u�����߂�I
	Vector3 p,g;
	p.setMadd(b, t, a);//p = b*t*a t�̂ݒ萔�@���̓x�N�g��
	g.setSub(p, c);//g = p-c

	double gd = g.dot(d);//���ς�Ԃ� �x�N�g���łȂ��萔��Ԃ�
	double ge = g.dot(e);
	double dd = d.dot(d);
	double de = d.dot(e);
	double ee = e.dot(e);

	double de_de_ed_dd = de * de - ee * dd;//���̒l�͂O�ɂȂ�Ȃ����Ƃ��ؖ�����Ă���̂Ń`�F�b�N�Ȃ��ɕ���ɂ�����
	double rcp_de_de_ed_dd = 1.0 / de_de_ed_dd;
	double u = (gd * de - ge * dd) * rcp_de_de_ed_dd;
	double v = (ge * de - de * ee) * rcp_de_de_ed_dd;

	if (v < 0 || v>1) {//v��u���O�`�P�͈̔͊O�Ȃ�A�E�g
		return inf;
	}
	if (u < 0 || u>1) {
		return inf;
	}
	return t;//��������
}

bool Triangle::isIntersect(const Vector3& lineBegin, const Vector3& lineVector) const {
	//�{�Ɠ����L���ɒu���Ȃ���
	const Vector3& a = lineBegin;
	const Vector3& b = lineVector;
	const Vector3& c = mPosition[0];
	Vector3 d, e;
	d.setSub(mPosition[1], c);
	e.setSub(mPosition[2], c);
	Vector3 f;
	f.setSub(c, a);
	//�@�������߂悤�B
	Vector3 n;
	n.setCross(d, e);
	//t�����߂�B
	double nf = n.dot(f);
	double nb = n.dot(b);
	if (nb == 0.f) { //���s
		return false; //�͂����
	}
	double t = nf / nb;
	if (t < 0 || t > 1) {
		return false;
	}
	///v�����߂�B
	Vector3 p;
	p.setMadd(b, t, a);
	Vector3 g;
	g.setSub(p, c);
	double gd = g.dot(d);
	double ge = g.dot(e);
	double dd = d.dot(d);
	double ee = e.dot(e);
	double de = d.dot(e);
	//�����0�ɂȂ肦�Ȃ��B������`�F�b�N���Ȃ��B
	double u = (gd * de - ge * dd) / (de * de - ee * dd);
	if (u < 0 || u > 1) {
		return false;
	}
	double v = (ge * de - gd * ee) / (de * de - ee * dd);
	if (v < 0 || (u + v > 1)) {
		return false;
	}
	return true;
}

bool Triangle::restrictMove(Vector3* v, const Vector3& p) const {
	//�܂�����
	bool r = isIntersect(p, *v);
	if (!r) {
		return false; //������Ȃ��̂ł��̂܂܏I���
	}
	//�������Ă���Ȃ�΁A�x�N�^���C������B
	//���͖@��n���g���Ĉȉ��̂悤�ɏ�����
	//a = v - dot( n, v ) * n / |n|^2
	Vector3 d, e, n;
	d.setSub(mPosition[1], mPosition[0]);
	e.setSub(mPosition[2], mPosition[0]);
	n.setCross(d, e);

	n *= n.dot(*v) / n.squareLength();
	*v -= n;
	return true;
}


/*
void Triangle::restrictMove(Vector3* v, const Vector3& p) const {
	//�܂�����
	bool r = isIntersect(p, *v);
	if (!r) {
		return; //������Ȃ��̂ł��̂܂܏I���
	}
	//���ē������Ă���Ȃ�΁A�x�N�^���C������B
	//���͖@��n���g���Ĉȉ��̂悤�ɏ�����
	//a = v - dot( n, v ) * n / |n|^2
	Vector3 d, e, n;
	d.setSub(mPosition[1], mPosition[0]);
	e.setSub(mPosition[2], mPosition[0]);
	n.setCross(d, e);

	n *= n.dot(*v) / n.squareLength();
	*v -= n;
}

double Triangle::getIntersectionTime(const Vector3& lineBegin, const Vector3& lineVector) const {
	double inf = numeric_limits< double >::max(); //double�ŕ\�����ԑ傫�Ȑ��B������Ȃ���΂��ꂪ�Ԃ�
	//�{�Ɠ����L���ɒu���Ȃ���
	const Vector3& a = lineBegin;
	const Vector3& b = lineVector;
	const Vector3& c = mPosition[0];
	Vector3 d, e;
	d.setSub(mPosition[1], c);
	e.setSub(mPosition[2], c);
	Vector3 f;
	f.setSub(c, a);
	//�@�������߂悤�B
	Vector3 n;
	n.setCross(d, e);
	//t�����߂�B
	double nf = n.dot(f);
	double nb = n.dot(b);
	if (nb == 0.f) { //���s
		return 0; //�͂���ɂ����Ⴆ�B
	}
	double t = nf / nb;
	if (t < 0 || t > 1) {
		return 0;
	}
	///v�����߂�B
	Vector3 p;
	p.setMadd(b, t, a);
	Vector3 g;
	g.setSub(p, c);
	double gd = g.dot(d);
	double ge = g.dot(e);
	double dd = d.dot(d);
	double ee = e.dot(e);
	double de = d.dot(e);
	//de*de - dd*ee�̋t���͓��g���̂ŁA���ōς܂��č���������B
	double dedeEedd = de * de - ee * dd; //������0�ɂ͂Ȃ肦�Ȃ��̂Ń`�F�b�N�Ȃ��ŋt��������
	double rcpDedeEedd = 1.0 / dedeEedd;

	double u = (gd * de - ge * dd) * rcpDedeEedd;
	if (u < 0 || u > 1) {
		return 0;
	
	}
	double v = (ge * de - gd * ee) * rcpDedeEedd;
	if (v < 0 || (u + v > 1)) {
		return 0;
	
	}
	
	return t; //t������
}

bool Triangle::isIntersect(const Vector3& lineBegin, const Vector3& lineVector)const {
	double t = getIntersectionTime(lineBegin, lineVector);
	return (t >= 0.0 && t <= 1.0);
}

bool Triangle::restrictMove(Vector3* v, const Vector3& p)const {//���̊֐����g����I
	bool r = isIntersect(p, *v);
	if (!r) {
		return false; //������Ȃ��̂ł��̂܂܏I���
	}
	//���ē������Ă���Ȃ�΁A�x�N�^���C������B
	//���͖@��n���g���Ĉȉ��̂悤�ɏ�����
	//a = v - dot( n, v ) * n / |n|^2
	Vector3 d, e, n;
	d.setSub(mPosition[1], mPosition[0]);
	e.setSub(mPosition[2], mPosition[0]);
	n.setCross(d, e);

	n *= n.dot(*v) / n.squareLength();
	*v -= n;
	return true;

}

																/*
	bool r = isIntersect(p, *v);//����I
	if (!r) {
		return false;//�������Ă��Ȃ��Ȃ�I���
	}
	/*�������Ă���ꍇ
	�����Circle�̎��̍����x�N�g��a�̎Z�o���@�Ɠ�����
	a = v - nv * n / |n|^2
	//*
	Vector3 d, e, n;
	d.setSub(mPosition[1], mPosition[0]);
	e.setSub(mPosition[2], mPosition[0]);
	n.setCross(d, e);

	n *= n.dot(*v) / n.squareLength();
	*v -= n;
	return true;
}
*/

void Triangle::modifyMove(Vector3* v)const {
	Vector3 d, e, n;
	d.setSub(mPosition[1], mPosition[0]);
	e.setSub(mPosition[2], mPosition[0]);
	n.setCross(d, e);
	n *= n.dot(*v) / n.squareLength();
	*v -= n;
}
