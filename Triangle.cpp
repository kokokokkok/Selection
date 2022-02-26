#include "Triangle.h"
#include "Library/Vector3.h"
#include <limits>
#include <iostream>

using namespace std;

void Triangle::setPosition(const Vector3& p0, const Vector3& p1, const Vector3& p2) {
	mPosition[0] = p0;//頂点座標を配列に入れ込む
	mPosition[1] = p1;
	mPosition[2] = p2;
}

double Triangle::getIntersectionTime(const Vector3& lineBegin, const Vector3& lineVector)const {
	double inf = numeric_limits<double>::max();

	const Vector3& a = lineBegin;//p = a + tb 1次元補間でプレイヤーの移動 
	const Vector3& b = lineVector;
	const Vector3& c = mPosition[0];// q = c + vd + ue 2次元補間　で三角形

	Vector3 d, e, f, n;
	d.setSub(mPosition[1], c);//
	e.setSub(mPosition[2], c);
	f.setSub(c,a);//それぞれc-aして代入
	n.setCross(d, e);//n*d - n*e  法線

	double nf = n.dot(f);
	double nb = n.dot(b);
	if (nb == 0.f) {
		return inf;//　tでnbを分母に入れるため、最悪でも0にならないように
	}
	double t = nf / nb;
	if (t < 0 || t>1) {//tが０～１に収まらないとアウト！
		return inf;
	}
	//ここからｖとuを求める！
	Vector3 p,g;
	p.setMadd(b, t, a);//p = b*t*a tのみ定数　他はベクトル
	g.setSub(p, c);//g = p-c

	double gd = g.dot(d);//内積を返す ベクトルでなく定数を返す
	double ge = g.dot(e);
	double dd = d.dot(d);
	double de = d.dot(e);
	double ee = e.dot(e);

	double de_de_ed_dd = de * de - ee * dd;//この値は０にならないことが証明されているのでチェックなしに分母における
	double rcp_de_de_ed_dd = 1.0 / de_de_ed_dd;
	double u = (gd * de - ge * dd) * rcp_de_de_ed_dd;
	double v = (ge * de - de * ee) * rcp_de_de_ed_dd;

	if (v < 0 || v>1) {//vとuが０～１の範囲外ならアウト
		return inf;
	}
	if (u < 0 || u>1) {
		return inf;
	}
	return t;//ｔが時刻
}

bool Triangle::isIntersect(const Vector3& lineBegin, const Vector3& lineVector) const {
	//本と同じ記号に置きなおす
	const Vector3& a = lineBegin;
	const Vector3& b = lineVector;
	const Vector3& c = mPosition[0];
	Vector3 d, e;
	d.setSub(mPosition[1], c);
	e.setSub(mPosition[2], c);
	Vector3 f;
	f.setSub(c, a);
	//法線を求めよう。
	Vector3 n;
	n.setCross(d, e);
	//tを求める。
	double nf = n.dot(f);
	double nb = n.dot(b);
	if (nb == 0.f) { //平行
		return false; //はずれに
	}
	double t = nf / nb;
	if (t < 0 || t > 1) {
		return false;
	}
	///vを求める。
	Vector3 p;
	p.setMadd(b, t, a);
	Vector3 g;
	g.setSub(p, c);
	double gd = g.dot(d);
	double ge = g.dot(e);
	double dd = d.dot(d);
	double ee = e.dot(e);
	double de = d.dot(e);
	//分母は0になりえない。だからチェックしない。
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
	//まず判定
	bool r = isIntersect(p, *v);
	if (!r) {
		return false; //当たらないのでそのまま終わる
	}
	//当たっているならば、ベクタを修正する。
	//式は法線nを使って以下のように書ける
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
	//まず判定
	bool r = isIntersect(p, *v);
	if (!r) {
		return; //当たらないのでそのまま終わる
	}
	//さて当たっているならば、ベクタを修正する。
	//式は法線nを使って以下のように書ける
	//a = v - dot( n, v ) * n / |n|^2
	Vector3 d, e, n;
	d.setSub(mPosition[1], mPosition[0]);
	e.setSub(mPosition[2], mPosition[0]);
	n.setCross(d, e);

	n *= n.dot(*v) / n.squareLength();
	*v -= n;
}

double Triangle::getIntersectionTime(const Vector3& lineBegin, const Vector3& lineVector) const {
	double inf = numeric_limits< double >::max(); //doubleで表せる一番大きな数。当たらなければこれが返る
	//本と同じ記号に置きなおす
	const Vector3& a = lineBegin;
	const Vector3& b = lineVector;
	const Vector3& c = mPosition[0];
	Vector3 d, e;
	d.setSub(mPosition[1], c);
	e.setSub(mPosition[2], c);
	Vector3 f;
	f.setSub(c, a);
	//法線を求めよう。
	Vector3 n;
	n.setCross(d, e);
	//tを求める。
	double nf = n.dot(f);
	double nb = n.dot(b);
	if (nb == 0.f) { //平行
		return 0; //はずれにしちゃえ。
	}
	double t = nf / nb;
	if (t < 0 || t > 1) {
		return 0;
	}
	///vを求める。
	Vector3 p;
	p.setMadd(b, t, a);
	Vector3 g;
	g.setSub(p, c);
	double gd = g.dot(d);
	double ge = g.dot(e);
	double dd = d.dot(d);
	double ee = e.dot(e);
	double de = d.dot(e);
	//de*de - dd*eeの逆数は二回使うので、一回で済ませて高速化する。
	double dedeEedd = de * de - ee * dd; //こいつは0にはなりえないのでチェックなしで逆数が取れる
	double rcpDedeEedd = 1.0 / dedeEedd;

	double u = (gd * de - ge * dd) * rcpDedeEedd;
	if (u < 0 || u > 1) {
		return 0;
	
	}
	double v = (ge * de - gd * ee) * rcpDedeEedd;
	if (v < 0 || (u + v > 1)) {
		return 0;
	
	}
	
	return t; //tが時刻
}

bool Triangle::isIntersect(const Vector3& lineBegin, const Vector3& lineVector)const {
	double t = getIntersectionTime(lineBegin, lineVector);
	return (t >= 0.0 && t <= 1.0);
}

bool Triangle::restrictMove(Vector3* v, const Vector3& p)const {//この関数が使われる！
	bool r = isIntersect(p, *v);
	if (!r) {
		return false; //当たらないのでそのまま終わる
	}
	//さて当たっているならば、ベクタを修正する。
	//式は法線nを使って以下のように書ける
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
	bool r = isIntersect(p, *v);//判定！
	if (!r) {
		return false;//当たっていないなら終わり
	}
	/*当たっている場合
	これはCircleの時の合成ベクトルaの算出方法と同じで
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
