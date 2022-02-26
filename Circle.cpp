#include "Circle.h"
#include "Library/Vector3.h"

void Circle::setPosition(const Vector3& a) {
	mPosition = a;//円のmPosition位置の値を更新
}

void Circle::setRadius(double a) {
	mRadius = a;//円のmRadius半径の位置を更新　ここ値次第ででどの程度、接近した場合に判定させるかが決まる
}

bool Circle::isIntersect(const Circle& b)const {
	Vector3 difference;
	difference.setSub(mPosition, b.mPosition);//ぶつかっている相手と円の位置を足す
	double squareDistance = difference.squareLength();//実際の距離の2乗
	double rSum = mRadius + b.mRadius;//ぶつかっている相手と円の半径（お互いの判定に利用したい距離）を足す
	rSum *= rSum;//判定に利用したい距離の2乗
	return (squareDistance < rSum);//実際の距離が判定したい距離より接近していた場合、Ture
}
void Circle::restrictMove(Vector3* v, const Circle& a)const {//vは移動量
	Circle t = *this;//このオブジェクトのポインタ 今回はメンバ変数を使うために利用
	t.mPosition += *v; //移動物体tに円オブジェクト（判定のための円）を作り、それを移動させて、衝突するのか判定し処理！
	bool r = t.isIntersect(a);//ここで衝突判定！移動物体tが移動し終わった後に、ぶつかる対象物aとぶつかっているのか判定！
	if (!r) {
		return;//ぶつかっていない場合は何もせず、移動したt.mPositionが残る
	}
	//ぶつかっている場合
	Vector3 d;
	d.setSub(mPosition, a.mPosition);
	double dotDV = d.dot(*v);// d*v
	double dLengrh2 = d.squareLength();// |d|*|d|
	d *= (dotDV / dLengrh2);// ( d*v / |d|*|d| ) * d
	*v -= d; // v - ( d*v / |d|*|d| ) * d
	/*
	dの位置の両者の距離とした場合、
	求めたい合成ベクトルaは
	a = v -  ( d*v / |d|*|d| ) * d となる！
	*/



}