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
	wc.hInstance     = hInstance;		// 句柄
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
	// 获取接口IDirect3D9的指针。该接口用于获取系统中物理硬件设备的信息并创建接口IDirect3DDevice9，
	// 该接口是一个C++对象，代表了我们用来显示3D图形的物理硬件设备

	IDirect3D9* d3d9 = 0;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	// 该对象主要有两个用途：设备枚举(device enumeration)以及创建IDirect3DDevice9类型的对象。
	// 设备枚举是指获取系统中可用的每块图形卡的性能、显示模式(display mode)、格式及其他信息
	// 

	if( !d3d9 )
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}



	// Step 2: Check for hardware vp.
	// 创建一个代表主显卡的IDirect3DDevice9类型对象时，必须指定使用该对象进行顶点运算的类型。
	// 如果可以，我们希望使用硬件顶点运算，但是由于并非所有的显卡都支持硬件顶点运算，我们必须首先检查图形卡是否支持
	// 该类型的运算。

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);		// ****

	// Can we use hardware vertex processing?
	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;



	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.
	// 我们可以通过这些变量来指定即将创建的接口IDirectDDevice9的特性

	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth            = width;				// 后台缓存中表面的宽度 单位为像素	***
	d3dpp.BackBufferHeight           = height;				// 后台缓存中表面的宽度 单位为像素	***
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;		// 后台缓存的像素格式
	d3dpp.BackBufferCount            = 1;					// 所需使用的后台缓存的个数，通常指定为1，表明我们仅需要一个后台缓存
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;	// 后台缓存所使用的多重采样类型
	d3dpp.MultiSampleQuality         = 0;					// 多重采用的质量水平
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
		// D3DSWAPEEFECT枚举类型的一个成员。该枚举类型指定了交换链中的缓存的页面转换方式
		// 指定为D3DSWAPEFFECT_DISCARD时效率最高
	d3dpp.hDeviceWindow              = hwnd;				// 与设备相关的窗口句柄 指定了所要进行绘制的应用程序窗口  ****
	d3dpp.Windowed                   = windowed;			// 为TRUE时，表示窗口模式。为FALSE时，表示全屏模式  ****
	d3dpp.EnableAutoDepthStencil     = true;				// 设为TRUE，则Direct3D自动创建并维护深度缓存或模板缓存
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;		// 深度缓存或模板缓存的像素格式(24位表示深度并将8位保留模板缓存使用)
	d3dpp.Flags                      = 0;					
		// D3DPRESENTFLAG_LOCKABLE_DEPTHBUFFER 指定可锁定的后台缓存。注意，使用 一个可锁定的后台缓存会降低性能
		// D3DPRESENT_DISCARD_DEPTHBUFFER 指定当下一个后台缓存提交时，哪个深度或模板缓存将被丢弃
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		// 刷新频率。如果想使用默认的刷新频率，可将该参数指定为D3DPRESENT_RATE_DEFAULT
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
		// D3DPRESENT集合中的一个成员。
		// D3DPRESENT_INTERVAL_IMMEDIATE  立即提交



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
			// 时间是相邻两次调用 ptr_display的时间间隔，即相邻的时间间隔
			float currTime  = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;		// 把毫秒变成秒

			ptr_display(timeDelta);		// 一般来说，这个timeDelta 零点几秒 0<timeDelta<1.0

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
	mtrl.Emissive = e;	// 如果为BLACK，则表示不发光，没有增强物体的高度
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
//	light.Ambient   = *color * 0.6f;	// 环境光
	light.Ambient   = *color;	// 环境光
	light.Diffuse   = *color;			// 
//	light.Specular  = *color * 0.6f;	// 镜面光
	light.Specular  = *color;	// 镜面光
	light.Direction = *direction;		// 方向

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
			6 * sizeof(d3d9::Vertex),	// 6个顶点
			0,								
			d3d9::Vertex::FVF,	// 灵活顶点格式
			D3DPOOL_MANAGED,	// 放入该托管内存池中的资源将交由Direct3D管理（这些资源将根据需要被设备自动
								// 转移到显存或AGP存储区中）
			&floor,				// 用于接收所创建的顶点缓存的指针 
			0);

		Vertex* v = 0;
		floor->Lock(0, 0, (void**)&v, 0);

		// 顶点顺序以 顺时针 为规则
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

		// 多级纹理采用。通过使用该过滤器，D3D 将选择尺寸与屏幕三角形最接近的那一级纹理
		// 一旦选择了某一级纹理，D3D就会用指定的放大过滤器和缩小过滤器对该级纹理进行过滤
		device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		device->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		device->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		
		// 将取与屏幕三角形尺寸最接近的两个纹理级，用指定的放大过滤器和缩小过滤器对每级纹理进行过滤，然后
		// 再将这两级纹理进行线性组合，从而形成最终的颜色值
		//device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		

		// 光源
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
		// draw pillars 总共有10个
		device->SetMaterial(&d3d9::YELLOW_MTRL);	// 使用黄色材质 
		device->SetTexture(0, 0);	 // 不使用纹理
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
