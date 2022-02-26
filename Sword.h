#ifndef INCLUDED_SWORD_H
#define INCLUDED_SWORD_H

class Model;
class GraphicsDatabese;
class Matrix44;
class Vector3;

class Sword {
public:
	Sword();
	~Sword();
	void create(
		GraphicsDatabase* ,
		const char* batchName,
		const Vector3& position,
		double angleX,
		double angleY,
		unsigned color);

	
	const Vector3* position() const;
	const Vector3* angle() const;

	Vector3 Push(Vector3 myPosition, Vector3 enemyPosition);


	void update(double myAngleY,Vector3* position);
	void draw(const Matrix44& projectionVewMatrix)const;
	bool isEmpty() const; //égÇ¡ÇƒÇ»ÇØÇÍÇŒtrueÅBmCount<0Ç≈îªíË
	void die();

private:
	Model* mModel;
	int mCount;

	static const float mSwordPush;//åïÇÃí∑Ç≥ 


};

#endif 
