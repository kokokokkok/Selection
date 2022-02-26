#include "GameLib/Framework.h"
#include "Triangle.h"
#include "Stage.h"
#include "Library/GraphicsDatabase.h"
#include "Library/Batch.h"
#include "Library/IndexBuffer.h"
#include "Library/VertexBuffer.h"
#include "Library/Model.h"
#include "Library/Matrix44.h"
#include "Library/Vector3.h"
#include <limits>
#include <iostream>
using namespace std;

Stage::Stage(const char* filename) : mDatabase( 0 ), mModel( 0 ),mTriangles(0){
	mDatabase = new GraphicsDatabase( filename );
	//std::unique_ptr<GraphicsDatabase> mDatabase(mDatabase);// unique Pointer
	mModel = mDatabase->createModel("draw");

	//衝突処理用データ作成
	const Batch* batch = mDatabase->batch("collision");
	const IndexBuffer* ib = batch->indexBuffer();
	const VertexBuffer* vb = batch->vertexBuffer();

	mTriangleNumber = ib->size() / 3;
	mTriangles = new Triangle[mTriangleNumber];
	//std::unique_ptr<Triangle> mTriangles(mTriangles);// unique Pointer
	for (int i = 0; i < mTriangleNumber; ++i) {
		unsigned i0 = ib->index(i * 3 + 0);
		unsigned i1 = ib->index(i * 3 + 1);
		unsigned i2 = ib->index(i * 3 + 2);
		mTriangles[i].setPosition(
			*vb->position(i0),
			*vb->position(i1),
			*vb->position(i2));
	}
}


Stage::~Stage(){
	SAFE_DELETE( mModel );
	SAFE_DELETE( mDatabase );
	SAFE_DELETE(mTriangles);
}

void Stage::draw( const Matrix44& pvm ) const {
	mModel->draw( pvm );
}

void Stage::restrictMove(Vector3* v, const Vector3& p) const {

	Vector3 vCopy = *v;
	//第一ループ
	double t = numeric_limits< double >::max();
	int minI = -1;
	for (int i = 0; i < mTriangleNumber; ++i) {
		double tt = mTriangles[i].getIntersectionTime(p, vCopy);
		if (tt < t) {
			t = tt;
			minI = i;
		}
	}
	if (t >= 0.f && t <= 1.f) { //当たった
		mTriangles[minI].restrictMove(&vCopy, p);
		//vCopy.y = 0;
	}
	//第二ループ
	t = numeric_limits< double >::max();
	minI = -1;
	for (int i = 0; i < mTriangleNumber; ++i) {
		double tt = mTriangles[i].getIntersectionTime(p, vCopy);
		if (tt < t) {
			t = tt;
			minI = i;
		}
	}
	if (t >= 0.f && t <= 1.f) { //当たった
		mTriangles[minI].restrictMove(&vCopy, p);
	
	}
	//第三ループ。当たるようならなかったことにして終わる。
	t = numeric_limits< double >::max();
	minI = -1;
	for (int i = 0; i < mTriangleNumber; ++i) {
		if (mTriangles[i].isIntersect(p, vCopy)) {
			v->set(0.0, 0.0, 0.0);
			return;
		}
	}
	*v = vCopy;
	//v->y = 0;
}

