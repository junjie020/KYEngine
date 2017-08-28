#ifndef _CAMERACONTROLLER_H_
#define _CAMERACONTROLLER_H_

namespace KY
{
    /*
     * Class CameraController
     */
	class Camera;

	class CameraController
	{
	public:
		CameraController(Camera *c);

		void Rotate(const glm::vec2 &delta);

		enum CameraMoveType
		{
			MT_Direction,
			MT_LeftRight,
			MT_UpDown,
			MT_Unknown,
		};

		void Move(CameraMoveType type, const glm::vec3 &delta);

		static void SetRotateSpeed(float speed);
		static void SetMoveSpeed(float speed);

	private:
		static float msRotateSpeed;
		static float msMoveSpeed;
	private:
		Camera* mCamera;
	};
}
#endif // _CAMERACONTROLLER_H_