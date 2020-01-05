#include <GL/freeglut.h>
#include "Camera.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#ifndef PI
#define PI 3.141592f
#endif

#define CAMERA_ROTATE 1
#define CAMERA_MOVE 2

using namespace glm;

Camera::Camera(float ratio, vec3 camPos, float waterheight)
{
	mMotionState = CAMERA_ROTATE;										
	mTheta = 2.0;
	mPhi = 4.0;
	mSpeed = 0.0f;														
	mMotionStep = 0.001f;												// sens of camera controls
	mThetaStep = 0.001f;
	mPhiStep = 0.003f;
	mPosition = camPos;
	mRatio = ratio;
	mNear = 0.01f;
	mFar = 100000.0f;
	mUp = vec3(0.0f, 1.0f, 0.0f);
	mApertureAngle = 60.0f;
	mWaterHeight = waterheight;
	mProjectionMatrix = perspective(mApertureAngle, mRatio, mNear, mFar);
}

Camera::~Camera()
{

}


void Camera::mouseButton(int button, int state, int x, int y)
{
	mMove = true;

	mOldX = x;
	mOldY = y;

	// Left mouse button: turn camera
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mMotionState = CAMERA_ROTATE;
	}

	// right mouse button: move camera
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mMotionState = CAMERA_MOVE;
	}
}

void Camera::mouseMove(int x, int y)
{
	int deltaX = x - mOldX;
	int deltaY = y - mOldY;

	if (mMotionState == CAMERA_ROTATE)
	{
		mTheta += mThetaStep * static_cast<float>(deltaY);

		if (mTheta < mThetaStep)
			mTheta = mThetaStep;
		else if (mTheta > PI - mThetaStep)
			mTheta = PI - mThetaStep;

		mPhi += mPhiStep * static_cast<float>(deltaX);

		if (mPhi < 0.0f)
			mPhi += 2.0f*PI;
		else if (mPhi > 2.0f*PI)
			mPhi -= 2.0f*PI;
	}
	else if (mMotionState == CAMERA_MOVE)
		mSpeed -= mMotionStep * static_cast<float>(deltaY);

	mOldX = x;
	mOldY = y;
}

void Camera::update()
{
	mDirection.x = sin(mTheta) * cos(mPhi);
	mDirection.y = cos(mTheta);
	mDirection.z = sin(mTheta) * sin(mPhi);
	
	mPosition += mSpeed * mDirection;

	mViewMatrix = lookAt(mPosition, mPosition + mDirection, mUp);
	updateReflectedViewMatrix();
}

const glm::mat4& Camera::getViewMatrix() const
{
	if (reflected)
		return mReflectedViewMatrix;
	else
		return mViewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	return mProjectionMatrix;
}

void Camera::updateProjection(float ratio)
{
	mRatio = ratio;
	mProjectionMatrix = perspective(mApertureAngle, mRatio, mNear, mFar);
}

void Camera::setViewDir(glm::fvec3 dir)
{
	mViewMatrix = lookAt(mPosition, mPosition + dir, mUp);
}

void Camera::updateReflectedViewMatrix()
{
	vec3 newPosition = mPosition;
	newPosition.y = mPosition.y - (2 * (mPosition.y - mWaterHeight));
	vec3 newForward = glm::reflect(mDirection, vec3(0.0, 1.0, 0.0));
	vec3 newUp = mUp * -1.0f;

	mReflectedViewMatrix = lookAt(newPosition, newPosition+newForward, mUp);
}

void Camera::reflect()
{
	reflected = !reflected;
}