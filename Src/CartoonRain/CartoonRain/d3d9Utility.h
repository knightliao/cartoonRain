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


#ifndef _KNIGHT_ENGINE_D3D9UTILITY_H_
#define _KNIGHT_ENGINE_D3D9UTILITY_H_


#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <limits>
#pragma warning (disable:4996)		// disable deprecated warning


namespace d3d9{

	// D3D9��ʹ�����̣�����ú����ɹ����أ����õ�һ��ָ�����������õ�IDirect3DDevice9�ӿڵ�ָ��
	bool InitD3D(
		HINSTANCE hInstance,			// [in] Application instance
		int width,						// [in] Back buffer dimensions	 ���ڳߴ�
		int height,						// [in] Back buffer dimensions 
		bool windowed,					// [in] windowed (true) or full screen(false)  ����ģʽ ����ģʽ ȫ��ģʽ
		D3DDEVTYPE deviceType,			// [in] HAL or REF  
		IDirect3DDevice9** device);		// [out] The created device   �豸�ӿ�ָ��
	

	// ��װ��Ӧ�ó������Ϣѭ�� ����һ��ָ����ʾ����(display function)�ĺ���ָ�롣����ʾ��������ʵ�ֻ��ƹ��ܵ��Ǹ�����
	// ����Ϣѭ��������Ҫ֪��ʹ���ĸ��������������ɶ�����е��ã����ڿ����ڼ���ʾ���� 
	int EnterMsgLoop(
		bool (*ptr_display)(float timeDelta));	


	LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg, 
		WPARAM wParam,
		LPARAM lParam);


	// ������ͷ�COM�ӿڲ���������ΪNULL
	template<class T> 
	void Release(T t)
	{
		if( t )
		{
			t->Release();
			t = 0;
		}
	}

	// ��ģ�庯�������Ŀ���Ƿ����ɾ�����ɶ��еĶ��󣬲�����ָ�븳ΪNULL
	template<class T> 
	void Delete(T t)
	{
		if( t )
		{
			delete t;
			t = 0;
		}
	}


	//
	// Colors
	//

	const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );
	const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
	const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) );
	const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
	const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
	const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
	const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
	const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );
	const D3DXCOLOR		  GRAY( D3DCOLOR_XRGB(122,122,122));


	//
	// Lights
	//

	// �����
	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	// ���Դ
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	// �۹��
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);
	/* how to use it
	D3DXVECTOR3 dir(1.0f,0.0f,0.0f);
	D3DXCOLOR c = d3d9::WHITE;
	D3DLIGHT9 direLight = d3d9::InitDirectionalLight(&dir,&c);
	*/



	//
	// Materials
	//

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 WHITE_MTRL  = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);		// ����ȫ��
	const D3DMATERIAL9 GRAY_MTRL = InitMtrl(GRAY,GRAY,GRAY,BLACK,2.0f);		// ��ɫ
	const D3DMATERIAL9 RED_MTRL    = InitMtrl(RED, RED, RED, BLACK, 2.0f);				// ֻ������
	const D3DMATERIAL9 GREEN_MTRL  = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);	// ��
	const D3DMATERIAL9 BLUE_MTRL   = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);		// ��
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);	// ��
	/* how to use
	D3DMATERIAL9 blueMaterial, redMaterial;
	// set up material structures

	Device->SetMaterial(&blueMaterial);
	drawSphere();
	Device->SetMaterial(&redMaterial);
	drawSphere();
	*/



	//
	// Bounding Objects
	//

	struct BoundingBox
	{
		BoundingBox();

		bool isPointInside(D3DXVECTOR3& p);

		D3DXVECTOR3 m_min;
		D3DXVECTOR3 m_max;
	};

	struct BoundingSphere
	{
		BoundingSphere();

		D3DXVECTOR3 m_center;
		float       m_radius;
	};

	//
	// Constants
	//

	const float INFINITY = FLT_MAX;
	const float EPSILON  = 0.001f;




	//
	// Drawing
	//

	// Function references "desert.bmp" internally.  This file must
	// be in the working directory.
	bool DrawBasicScene(
		IDirect3DDevice9* device,// Pass in 0 for cleanup.
		float scale);            // uniform scale 

	//
	// Vertex Structures
	//

	struct Vertex
	{
		Vertex(){}
		Vertex(float x, float y, float z, 
			float nx, float ny, float nz,
			float u, float v)
		{
			_x  = x;  _y  = y;  _z  = z;
			_nx = nx; _ny = ny; _nz = nz;
			_u  = u;  _v  = v;
		}
		float _x, _y, _z;		// λ��	
		float _nx, _ny, _nz;	// ���� 
		float _u, _v;			// ���� 

		static const DWORD FVF;
	};

	//
	// Randomness
	//

	// Desc: Return random float in [lowBound, highBound] interval.
	float GetRandomFloat(float lowBound, float highBound);


	// Desc: Returns a random vector in the bounds specified by min and max.
	void GetRandomVector(
		D3DXVECTOR3* out,
		D3DXVECTOR3* min,
		D3DXVECTOR3* max);

	//
	// Conversion
	//
	DWORD FtoDw(float f);
}




#endif