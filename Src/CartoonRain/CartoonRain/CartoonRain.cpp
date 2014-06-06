
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
This program is completed with DX9
*/


#include "d3d9Utility.h"
#include "camera.h"
#include <cstdlib>
#include <ctime>
#include "rain.h"
#include "AllInclude.h"


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3dx9.lib")


IDirect3DDevice9* Device = 0;				// 设备
Camera TheCamera(Camera::LANDOBJECT);		// 摄像机
CRain myRain;								// 雨


//const int Width  = 640;
//const int Height = 480;

const int Width = 1280;
const int Height = 800;



// 摄像机参数
// pos : VectorR3 pos(0.0,0.0,-20.0);
// look: VectorR3 look(0.0,0.0,1.0);
// 640*480

//
// Framework Functions
//
bool Setup()
{
	//
	// Create the vertex buffer.
	//
	// seed random number generator
	srand((unsigned int)time(0));


	VectorR3 pos(0.0,3.0,-10.0);
	VectorR3 look(0.0,0.0,1.0);
	TheCamera.setPosLook(pos,look);


	//
	// Create basic scene.
	//
	d3d9::DrawBasicScene(Device, 1.0f);


	//
	// Set projection matrix.
	//
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI / 2.0f,				// 45 - degree
		(float)Width / (float)Height,
		1.0f,						// 从 1 看到 5000
		5000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);


	float disapper = -3.0f;		// 
	float iniHeight = 30.0f;	// 雨滴初始高度
	float range = 20.0f;	// 雨的范围
	int parNum = 500;		// 雨滴初始数量 
	D3DXVECTOR3 poss;		// 
	TheCamera.getPosition(&poss);	// 摄像机的位置


	myRain.InitializeParticleSystem(Device,disapper,iniHeight,range,poss,parNum);	// 初使化雨系统

	return true;
}


// 对键盘进行响应
// 时间是秒
void MyKeyboardProc(float timeDelta)
{
	if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
		TheCamera.pitch(1.0f * timeDelta);

	if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
		TheCamera.pitch(-1.0f * timeDelta);

	if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
		TheCamera.strafe(-4.0f * timeDelta);

	if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
		TheCamera.strafe(4.0f * timeDelta);

	if( ::GetAsyncKeyState('A') & 0x8000f )
		TheCamera.yaw(-1.0f * timeDelta);

	if( ::GetAsyncKeyState('D') & 0x8000f )
		TheCamera.yaw(1.0f * timeDelta);

	if( ::GetAsyncKeyState('W') & 0x8000f )
		TheCamera.walk(4.0f * timeDelta);

	if( ::GetAsyncKeyState('S') & 0x8000f )
		TheCamera.walk(-4.0f * timeDelta);



	// 调整摄像机的参数
	D3DXMATRIX V;
	TheCamera.getViewMatrix(&V);
	Device->SetTransform(D3DTS_VIEW, &V);
}



bool Display(float timeDelta)
{
	if( Device )
	{
		//
		// Update the scene:
		//
		
		MyKeyboardProc(timeDelta);


		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, d3d9::BLACK, 1.0f, 0);
		// pRect数组中矩形的数目
		// 所要执行清除操作的屏幕矩阵形数组。该参数允许我们只对表面的部分区域进行清除操作
		// 指定所要清除的表面
		//		D3DCLEAR_TARGET 绘制目标表面，通常指后台缓存
		//		D3DCLEAR_ZBUFFER 深度缓存
		
		// 更新雨系统
		myRain.UpdateParticles(timeDelta);
	
	
		Device->BeginScene();


		D3DXMATRIX I;
		D3DXMatrixIdentity(&I);
		Device->SetTransform(D3DTS_WORLD, &I);
		
		// 初始化场景
		d3d9::DrawBasicScene(Device, 1.0f);

		// order important, render snow last.
		Device->SetTransform(D3DTS_WORLD, &I);
		
		// 绘制雨
		myRain.Render(Device);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);	// 提交后台缓存

	}

	return true;
}



LRESULT CALLBACK d3d9::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}




void Cleanup()
{
	d3d9::DrawBasicScene(0, 1.0f);
}



int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{

	Trace::t_log.on_stream();
	Trace::t_log<<"Begin Tracing"<<std::endl;


	// 初使化主显示窗口及D3D
	if(!d3d9::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	// 调用Setup函数对应用程序进行设置
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	// 将Display函数作为显示函数，进入消息循环
	d3d9::EnterMsgLoop( Display );

	// 执行清除操作
	Cleanup();

	Device->Release();

	return 0;
}
