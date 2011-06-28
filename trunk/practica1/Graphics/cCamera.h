//This class will encase all camera functionality

#ifndef cCamera_H
#define cCamera_H

#include "..\MathLib\MathLib.h"

class cCamera
{
public:

	//Init function for camera class
	void Init();

	//Locate camera function
	void SetLookAt( const cVec3 &lvPosition, const cVec3 &lvTarget, const cVec3 &lvUpWorld );

	//Sets orthogonal perspective
	void SetOrtho( float lfLeft, float lfRight, float lfBottom, float lfTop, float lfZNear, float lfZNFar );

	//Sets perspective projection
	void SetPerspective( float lfFOVY_Rad, float lfAspect, float lfZNear, float lfZFar );

	//Class getters
	cVec3 GetFront() const { mView.GetFront(); }
	cVec3 GetLeft() const { mView.GetLeft(); }
	cVec3 GetRight() const { mView.GetRight(); }
	cVec3 GetUp() const { mView.GetUp(); }
	cVec3 GetPosition() const { mView.GetPosition(); }
	const cMatrix &GetView() const { return mView; }
	const cMatrix &GetProj() const { return mProj; }
	const cMatrix &GetViewProj() const { return mViewProj; }

private:
	//Private attributes for camera class
	//View, Projection and View-Projection matrixes
	cMatrix mView;
	cMatrix mProj;
	cMatrix mViewProj;

	//Keeps View Projection matrix updated
	inline void RefreshViewProj() { mViewProj = mView * mProj; }

};

#endif cCamera_H