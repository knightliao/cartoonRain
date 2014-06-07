/////////////////////////////////////////////////////////////////////////////////
//       ___          ___                     ___          ___
//      /__/|        /__/\       ___         /  /\        /__/\         ___
//     |  |:|        \  \:\     /  /\       /  /:/_       \  \:\       /  /\
//     |  |:|         \  \:\   /  /:/      /  /:/ /\       \__\:\     /  /:/
//   __|  |:|     _____\__\:\ /__/::\     /  /:/_/::\  ___ /  /::\   /  /:/
//  /__/\_|:|____/__/::::::::\\__\/\:\__ /__/:/__\/\:\/__/\  /:/\:\ /  /::\
//  \  \:\/:::::/\  \:\~~\~~\/   \  \:\/\\  \:\ /~~/:/\  \:\/:/__\//__/:/\:\
//   \  \::/~~~~  \  \:\  ~~~     \__\::/ \  \:\  /:/  \  \::/     \__\/  \:\
//    \  \:\       \  \:\         /__/:/   \  \:\/:/    \  \:\          \  \:\
//     \  \:\       \  \:\        \__\/     \  \::/      \  \:\          \__\/
//      \__\/        \__\/                   \__\/        \__\/
//
//
// author		:	KNIGHT
// Description	:	
//
// Time			:	2009 - 5 - 17
//					
// Email		:	KnightLiao@gmail.com	liaoqiqi@cad.zju.edu.cn
// Blog			:   http://knightliao.blogspot.com
////////////////////////////////////////////////////////////////////////////////////


/*	
	This program is finished from  <Introduction to 3D game Programming with DirectX9.0>

	completed with DX9
*/


#ifndef _KNIGHT_ENGINE_CAMERA_H_
#define _KNIGHT_ENGINE_CAMERA_H_

#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib") 
#include "AllInclude.h"


class Camera
{
public:
	enum CameraType{LANDOBJECT,AIRCRAFT};	// LANDOBJECT 地面行走的摄像机（第一人称射击游戏中，射击者不可能飞行）
											// AIRCRAFT 允许摄像机在空间自由运动 具有6个自由度

	Camera();
	void Camera::setPosLook(VectorR3 &pos, VectorR3 &look);	// 我们一般只是设定 摄像机 位置 和 观察方向
	Camera(CameraType cameraType);
	~Camera();

	void strafe(float units);		// left/right  沿向量right方向的扫视
	void fly(float units);			// up/down  沿向量up方向的升降
	void walk(float units);			// forward/backward 沿向量
	
	void pitch(float angle);		// rotate on right vector	俯仰 right
	void yaw(float angle);			// rotate on up vector		向上 up 
	void roll(float angle);			// rotate on look vector	滚动 look

	
	// get set matrix
	void getViewMatrix(D3DXMATRIX* V); 
	void setCameraType(CameraType cameraType); 
	void getPosition(D3DXVECTOR3* pos); 
	void setPosition(D3DXVECTOR3* pos); 

	// get right/up/look
	void getRight(D3DXVECTOR3* right);
	void getUp(D3DXVECTOR3* up);
	void getLook(D3DXVECTOR3* look);

private:

	// 摄像机类型
	CameraType	m_cameraType;
	
	// 三个向量
	D3DXVECTOR3 m_right;	// 注意，这三者都是向量，不是点@!!!! 所以如果把m_look设为(0,0,0)，是看不到任何东西的。
	D3DXVECTOR3	m_up;
	D3DXVECTOR3 m_look;
	
	// 像机位置
	D3DXVECTOR3 m_pos;
};




/*

How to use this class:(sample)

实现了对键盘输入的响应。
我们将摄像机对象实例化为一个全局对象。
摄像机的移动是根据时间变化(timeDelta)来进行的。这样我们就不依赖于帧频，以稳定的速度移动摄像机。
timeDelta是相邻帧间的时间差，主要用于将动画与显示器的刷新频率保持同步。
（意思是说，渲染一个场景的帧率一般是保持不变的，所以移动摄像机的速度也不变。
但是，对于帧率会改变的场景，这样实现也是不错的，一旦帧率下降，那么摄像机移动速度马上变慢。）


Camera TheCamera(Camera::LANDOBJECT);

bool Display(float timeDelta)
{
	if( Device )
	{
		//
		// Update: Update the camera.
		//

		if( ::GetAsyncKeyState('W') & 0x8000f )
			TheCamera.walk(4.0f * timeDelta);

		if( ::GetAsyncKeyState('S') & 0x8000f )
			TheCamera.walk(-4.0f * timeDelta);

		if( ::GetAsyncKeyState('A') & 0x8000f )
			TheCamera.strafe(-4.0f * timeDelta);

		if( ::GetAsyncKeyState('D') & 0x8000f )
			TheCamera.strafe(4.0f * timeDelta);

		if( ::GetAsyncKeyState('R') & 0x8000f )
			TheCamera.fly(4.0f * timeDelta);

		if( ::GetAsyncKeyState('F') & 0x8000f )
			TheCamera.fly(-4.0f * timeDelta);

		if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
			TheCamera.pitch(1.0f * timeDelta);

		if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
			TheCamera.pitch(-1.0f * timeDelta);

		if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
			TheCamera.yaw(-1.0f * timeDelta);

		if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
			TheCamera.yaw(1.0f * timeDelta);

		if( ::GetAsyncKeyState('N') & 0x8000f )
			TheCamera.roll(1.0f * timeDelta);

		if( ::GetAsyncKeyState('M') & 0x8000f )
			TheCamera.roll(-1.0f * timeDelta);

		// Update the view matrix representing the cameras 
		// new position/orientation.
		D3DXMATRIX V;
		TheCamera.getViewMatrix(&V);
		Device->SetTransform(D3DTS_VIEW, &V);

		//
		// Render
		//

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();

		d3d::DrawBasicScene(Device, 1.0f);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}



*/



#endif
