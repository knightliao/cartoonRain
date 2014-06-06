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
	enum CameraType{LANDOBJECT,AIRCRAFT};	// LANDOBJECT �������ߵ����������һ�˳������Ϸ�У�����߲����ܷ��У�
											// AIRCRAFT ����������ڿռ������˶� ����6�����ɶ�

	Camera();
	void Camera::setPosLook(VectorR3 &pos, VectorR3 &look);	// ����һ��ֻ���趨 ����� λ�� �� �۲췽��
	Camera(CameraType cameraType);
	~Camera();

	void strafe(float units);		// left/right  ������right�����ɨ��
	void fly(float units);			// up/down  ������up���������
	void walk(float units);			// forward/backward ������
	
	void pitch(float angle);		// rotate on right vector	���� right
	void yaw(float angle);			// rotate on up vector		���� up 
	void roll(float angle);			// rotate on look vector	���� look

	
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

	// ���������
	CameraType	m_cameraType;
	
	// ��������
	D3DXVECTOR3 m_right;	// ע�⣬�����߶������������ǵ�@!!!! ���������m_look��Ϊ(0,0,0)���ǿ������κζ����ġ�
	D3DXVECTOR3	m_up;
	D3DXVECTOR3 m_look;
	
	// ���λ��
	D3DXVECTOR3 m_pos;
};




/*

How to use this class:(sample)

ʵ���˶Լ����������Ӧ��
���ǽ����������ʵ����Ϊһ��ȫ�ֶ���
��������ƶ��Ǹ���ʱ��仯(timeDelta)�����еġ��������ǾͲ�������֡Ƶ�����ȶ����ٶ��ƶ��������
timeDelta������֡���ʱ����Ҫ���ڽ���������ʾ����ˢ��Ƶ�ʱ���ͬ����
����˼��˵����Ⱦһ��������֡��һ���Ǳ��ֲ���ģ������ƶ���������ٶ�Ҳ���䡣
���ǣ�����֡�ʻ�ı�ĳ���������ʵ��Ҳ�ǲ���ģ�һ��֡���½�����ô������ƶ��ٶ����ϱ�������


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
