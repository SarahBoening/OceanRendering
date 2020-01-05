#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:

	Camera(float ratio, glm::vec3 camPos, float waterheight);
	~Camera();

	void mouseMove(int x, int y);

	void mouseButton(int button, int state, int x, int y);

	void update();
	void stop() { mSpeed = 0; }
	void setViewDir(glm::fvec3 dir);
	void updateProjection(float ratio);
	void updateReflectedViewMatrix();
	void reflect();
	const glm::mat4& getViewMatrix() const;
	const glm::mat4& getProjectionMatrix() const;
	const glm::vec3& getPosition() const { return mPosition; }
	const float getFar() const { return mFar; }
	const float getNear() const { return mNear; }

private:
	int mOldX = 0;
	int mOldY = 0;
	int mMotionState;
	float mTheta;
	float mPhi;
	float mSpeed = 0.0f;
	float mMotionStep;
	float mThetaStep;
	float mPhiStep;
	float mRatio;
	float mNear;
	float mFar;
	float mApertureAngle;

	float mWaterHeight;
	glm::vec3 mPosition;
	glm::vec3 mDirection;
	glm::vec3 mUp;
	glm::mat4 mViewMatrix;
	glm::mat4 mReflectedViewMatrix;
	glm::mat4 mProjectionMatrix;

	bool mMove = true;
	bool reflected = false;
};

#endif