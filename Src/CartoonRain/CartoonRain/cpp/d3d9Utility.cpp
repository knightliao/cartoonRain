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


#include "..\headers\d3d9Utility.h"




bool d3d9::InitD3D(
				  HINSTANCE hInstance,
				  int width, int height,
				  bool windowed,
				  D3DDEVTYPE deviceType,
				  IDirect3DDevice9** device)
{

	//
	// Create the main application window.
	//

	// 1. the first task to creating a window is to describe its characteristics by filling out a WNDCLASS structure

	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)d3d9::WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;		// ���
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "Direct3D9App";

	// 2. Then we register this window class description with Windows so that we can create a window based 
	//    on that description.
	if( !RegisterClass(&wc) ) 
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}

	// 3.With our window class description registered, we can create a window with the CreateWindow function.
	//   Note, this function returns a HWND to the created window, which we save in hwnd.
	//   Through hwnd we can reference this particular window we creating.
	HWND hwnd = 0;
	hwnd = ::CreateWindow("Direct3D9App", "Cartoon Rain System -- http://knightliao.blogspot.com", 
		WS_EX_TOPMOST,
		0, 0, width, height,
		0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/); 

	if( !hwnd )
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}

	// 4.Finally we show and update the window we just created 
	//   Observe we pass hwnd to these functions so that these functions know what particular window to show and update.
	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);



	// ---------------------------------------------------------------------------------------------

	//
	// Init D3D: 
	//

	HRESULT hr = 0;

	// Step 1: Create the IDirect3D9 object.
	// ��ȡ�ӿ�IDirect3D9��ָ�롣�ýӿ����ڻ�ȡϵͳ������Ӳ���豸����Ϣ�������ӿ�IDirect3DDevice9��
	// �ýӿ���һ��C++���󣬴���������������ʾ3Dͼ�ε�����Ӳ���豸

	IDirect3D9* d3d9 = 0;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	// �ö�����Ҫ��������;���豸ö��(device enumeration)�Լ�����IDirect3DDevice9���͵Ķ���
	// �豸ö����ָ��ȡϵͳ�п��õ�ÿ��ͼ�ο������ܡ���ʾģʽ(display mode)����ʽ��������Ϣ
	// 

	if( !d3d9 )
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}



	// Step 2: Check for hardware vp.
	// ����һ���������Կ���IDirect3DDevice9���Ͷ���ʱ������ָ��ʹ�øö�����ж�����������͡�
	// ������ԣ�����ϣ��ʹ��Ӳ���������㣬�������ڲ������е��Կ���֧��Ӳ���������㣬���Ǳ������ȼ��ͼ�ο��Ƿ�֧��
	// �����͵����㡣

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);		// ****

	// Can we use hardware vertex processing?
	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;



	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.
	// ���ǿ���ͨ����Щ������ָ�����������Ľӿ�IDirectDDevice9������

	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth            = width;				// ��̨�����б���Ŀ�� ��λΪ����	***
	d3dpp.BackBufferHeight           = height;				// ��̨�����б���Ŀ�� ��λΪ����	***
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;		// ��̨��������ظ�ʽ
	d3dpp.BackBufferCount            = 1;					// ����ʹ�õĺ�̨����ĸ�����ͨ��ָ��Ϊ1���������ǽ���Ҫһ����̨����
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;	// ��̨������ʹ�õĶ��ز�������
	d3dpp.MultiSampleQuality         = 0;					// ���ز��õ�����ˮƽ
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
		// D3DSWAPEEFECTö�����͵�һ����Ա����ö������ָ���˽������еĻ����ҳ��ת����ʽ
		// ָ��ΪD3DSWAPEFFECT_DISCARDʱЧ�����
	d3dpp.hDeviceWindow              = hwnd;				// ���豸��صĴ��ھ�� ָ������Ҫ���л��Ƶ�Ӧ�ó��򴰿�  ****
	d3dpp.Windowed                   = windowed;			// ΪTRUEʱ����ʾ����ģʽ��ΪFALSEʱ����ʾȫ��ģʽ  ****
	d3dpp.EnableAutoDepthStencil     = true;				// ��ΪTRUE����Direct3D�Զ�������ά����Ȼ����ģ�建��
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;		// ��Ȼ����ģ�建������ظ�ʽ(24λ��ʾ��Ȳ���8λ����ģ�建��ʹ��)
	d3dpp.Flags                      = 0;					
		// D3DPRESENTFLAG_LOCKABLE_DEPTHBUFFER ָ���������ĺ�̨���档ע�⣬ʹ�� һ���������ĺ�̨����ή������
		// D3DPRESENT_DISCARD_DEPTHBUFFER ָ������һ����̨�����ύʱ���ĸ���Ȼ�ģ�建�潫������
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		// ˢ��Ƶ�ʡ������ʹ��Ĭ�ϵ�ˢ��Ƶ�ʣ��ɽ��ò���ָ��ΪD3DPRESENT_RATE_DEFAULT
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
		// D3DPRESENT�����е�һ����Ա��
		// D3DPRESENT_INTERVAL_IMMEDIATE  �����ύ



	// Step 4: Create the device.

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		deviceType,         // device type				*****
		hwnd,               // window associated with device
		vp,                 // vertex processing	
		&d3dpp,             // present parameters	
		device);            // return created device	****

	if( FAILED(hr) )
	{
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			hwnd,
			vp,
			&d3dpp,
			device);

		if( FAILED(hr) )
		{
			d3d9->Release(); // done with d3d9 object
			::MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}

	d3d9->Release(); // done with d3d9 object

	return true;
}



int d3d9::EnterMsgLoop( bool (*ptr_display)(float timeDelta) )
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	// The timeGetTime function retrieves the system time, in milliseconds. 
	// The system time is the time elapsed since Windows was started.
	static float lastTime = (float)timeGetTime(); 

	while(msg.message != WM_QUIT)
	{
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{	
			// ʱ�����������ε��� ptr_display��ʱ�����������ڵ�ʱ����
			float currTime  = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;		// �Ѻ�������

			ptr_display(timeDelta);		// һ����˵�����timeDelta ��㼸�� 0<timeDelta<1.0

			lastTime = currTime;
		}
	}
	return (int)msg.wParam;
}





//
// Materials
//

D3DMATERIAL9 d3d9::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient  = a;
	mtrl.Diffuse  = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;	// ���ΪBLACK�����ʾ�����⣬û����ǿ����ĸ߶�
	mtrl.Power    = p;
	return mtrl;
}





//
// Lights
//

D3DLIGHT9 d3d9::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_DIRECTIONAL;
//	light.Ambient   = *color * 0.6f;	// ������
	light.Ambient   = *color;	// ������
	light.Diffuse   = *color;			// 
//	light.Specular  = *color * 0.6f;	// �����
	light.Specular  = *color;	// �����
	light.Direction = *direction;		// ����

	return light;
}

D3DLIGHT9 d3d9::InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_POINT;
	light.Ambient   = *color * 0.6f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

D3DLIGHT9 d3d9::InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_SPOT;
	light.Ambient   = *color * 0.0f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Direction = *direction;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta        = 0.4f;
	light.Phi          = 0.9f;

	return light;
}




//
// Bounding Objects
//


d3d9::BoundingBox::BoundingBox()
{
	// infinite small 
	m_min.x = d3d9::INFINITY;
	m_min.y = d3d9::INFINITY;
	m_min.z = d3d9::INFINITY;

	m_max.x = -d3d9::INFINITY;
	m_max.y = -d3d9::INFINITY;
	m_max.z = -d3d9::INFINITY;
}

bool d3d9::BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if( p.x >= m_min.x && p.y >= m_min.y && p.z >= m_min.z &&
		p.x <= m_max.x && p.y <= m_max.y && p.z <= m_max.z )
	{
		return true;
	}
	else
	{
		return false;
	}
}

d3d9::BoundingSphere::BoundingSphere()
{
	m_radius = 0.0f;
}



// vertex formats
const DWORD d3d9::Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

bool d3d9::DrawBasicScene(IDirect3DDevice9* device, float scale)
{
	static IDirect3DVertexBuffer9* floor  = 0;
	static IDirect3DTexture9*      tex    = 0;
	static ID3DXMesh*              pillar = 0;

	HRESULT hr = 0;

	if( device == 0 )
	{
		if( floor && tex && pillar )
		{
			// they already exist, destroy them
			d3d9::Release<IDirect3DVertexBuffer9*>(floor);
			d3d9::Release<IDirect3DTexture9*>(tex);
			d3d9::Release<ID3DXMesh*>(pillar);
		}
	}
	else if( !floor && !tex && !pillar )
	{
		// they don't exist, create them
		device->CreateVertexBuffer(
			6 * sizeof(d3d9::Vertex),	// 6������
			0,								
			d3d9::Vertex::FVF,	// �����ʽ
			D3DPOOL_MANAGED,	// ������й��ڴ���е���Դ������Direct3D������Щ��Դ��������Ҫ���豸�Զ�
								// ת�Ƶ��Դ��AGP�洢���У�
			&floor,				// ���ڽ����������Ķ��㻺���ָ�� 
			0);

		Vertex* v = 0;
		floor->Lock(0, 0, (void**)&v, 0);

		// ����˳���� ˳ʱ�� Ϊ����
		v[0] = Vertex(-20.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v[1] = Vertex(-20.0f, -1.0f,  20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v[2] = Vertex( 20.0f, -1.0f,  20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		v[3] = Vertex(-20.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v[4] = Vertex( 20.0f, -1.0f,  20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v[5] = Vertex( 20.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

		floor->Unlock();

		// Radius1 Radius2 Length Slices Stacks ppMesh 
		D3DXCreateCylinder(device, 0.5f, 0.5f, 5.0f, 3, 1, &pillar, 0);

		D3DXCreateTextureFromFile(
			device,
			"desert.bmp",
			&tex);
	}
	else
	{
		//
		// Pre-Render Setup
		//
		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

		// �༶������á�ͨ��ʹ�øù�������D3D ��ѡ��ߴ�����Ļ��������ӽ�����һ������
		// һ��ѡ����ĳһ������D3D�ͻ���ָ���ķŴ����������С�������Ըü�������й���
		device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		device->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		device->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		
		// ��ȡ����Ļ�����γߴ���ӽ���������������ָ���ķŴ����������С��������ÿ��������й��ˣ�Ȼ��
		// �ٽ��������������������ϣ��Ӷ��γ����յ���ɫֵ
		//device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		

		// ��Դ
		D3DXVECTOR3 dir(0.707f, -0.707f, 0.707f);
		D3DXCOLOR col(1.0f, 1.0f, 1.0f, 1.0f);
		D3DLIGHT9 light = d3d9::InitDirectionalLight(&dir, &col);

		device->SetLight(0, &light);
		device->LightEnable(0, true);
		device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		device->SetRenderState(D3DRS_SPECULARENABLE, true);

		//
		// Render
		//

		D3DXMATRIX T, R, P, S;

		D3DXMatrixScaling(&S, scale, scale, scale);

		// used to rotate cylinders to be parallel with world's y-axis
		D3DXMatrixRotationX(&R, -D3DX_PI * 0.5f);

		// draw floor
		D3DXMatrixIdentity(&T);
		T = T * S;
		device->SetTransform(D3DTS_WORLD, &T);

		device->SetMaterial(&d3d9::GRAY_MTRL);

		device->SetTexture(0,tex);
		device->SetStreamSource(0, floor, 0, sizeof(Vertex));
		device->SetFVF(Vertex::FVF);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

/*
		// draw pillars �ܹ���10��
		device->SetMaterial(&d3d9::YELLOW_MTRL);	// ʹ�û�ɫ���� 
		device->SetTexture(0, 0);	 // ��ʹ������
		for(int i = 0; i < 5; i++)
		{
			D3DXMatrixTranslation(&T, -5.0f, 1.5f, -15.0f + (i * 7.5f));
			P = R * T * S;
			device->SetTransform(D3DTS_WORLD, &P);
			pillar->DrawSubset(0);

			D3DXMatrixTranslation(&T, 5.0f, 1.5f, -15.0f + (i * 7.5f));
			P = R * T * S;
			device->SetTransform(D3DTS_WORLD, &P);
			pillar->DrawSubset(0);

		}
*/
	}
	return true;
}



float d3d9::GetRandomFloat(float lowBound, float highBound)
{
	if( lowBound >= highBound ) // bad input
		return lowBound;

	// get random float in [0, 1] interval
	float f = (rand() % 10000) * 0.0001f; 

	// return float in [lowBound, highBound] interval. 
	return (f * (highBound - lowBound)) + lowBound; 
}

void d3d9::GetRandomVector(
						  D3DXVECTOR3* out,
						  D3DXVECTOR3* min,
						  D3DXVECTOR3* max)
{
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

DWORD d3d9::FtoDw(float f)
{
	return *((DWORD*)&f);
}
