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




#include "..\headers\rain.h"
#include "..\headers\AllInclude.h"

#define MAX_PARTICLES   1600
#define ADD_PARTICLES_EACH_FRAME  5			// 每一帧加入2个雨滴
#define RAINDROP_FALLDOWN_RATE   30.0f		// 下降速度



CRain::CRain()
{
	m_Drop = 0;
	m_rainBuffer = 0;	// 顶点空间
	m_Drop = 0;		// 纹理
	m_quardBuffer = 0;
}

CRain::~CRain(void)
{
	d3d9::Release<IDirect3DVertexBuffer9*>(m_rainBuffer);	// 顶点缓存
	d3d9::Release<IDirect3DVertexBuffer9*>(m_quardBuffer);	// 顶点缓存
	d3d9::Release<IDirect3DTexture9*>(m_Drop);		// 纹理缓存
}



bool CRain::InitializeParticleSystem(IDirect3DDevice9* device,float disapper,
					float initHeight,float range,D3DXVECTOR3 center,int parNum )
{
	m_DisappearHeight = disapper;		// -3.0f

	m_initHeight = initHeight;			// 30.0f 初使高度

	m_center = center;					// 0 0  -20

	m_range = range;					// 60

	m_vbSize = parNum;					// 500


	for(int i= 0;i<(int)m_vbSize;++i){
		AddParticle();
	}


	HRESULT hr = 0;

	// 生成雨滴纹理
	hr = D3DXCreateTextureFromFile(
		device,
	//	"lake.bmp",
		"drop.png",
		&m_Drop);

	if(FAILED(hr))
	{
		::MessageBox(0, "D3DXCreateTextureFromFile() - FAILED", "PSystem", 0);
		return false;
	}

	// 初使化顶点

	hr = device->CreateVertexBuffer(
		MAX_PARTICLES *3 * sizeof(StrRain),	// 一个点要变成一个三角形
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
		StrRain::FVF,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED can't be used with D3DUSAGE_DYNAMIC 
		&m_rainBuffer,
		0);

	if(FAILED(hr))
	{
		::MessageBox(0, "CreateVertexBuffer() - FAILED", "PSystem", 0);
		return false;
	}

	hr = device->CreateVertexBuffer(
		MAX_PARTICLES*6 * sizeof(StrRain),	// 一个点要变成一个四边形
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
		StrRain::FVF,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED can't be used with D3DUSAGE_DYNAMIC 
		&m_quardBuffer,
		0);

	if(FAILED(hr))
	{
		::MessageBox(0, "CreateVertexBuffer() - m_quardBuffer - FAILED", "PSystem", 0);
		return false;
	}

	return true;
}

void CRain::AddParticle()
{
	CRainDrop newDrop;
	float x = d3d9::GetRandomFloat(-m_range/2,m_range);	// 在x方向上得到 [0,range] 大小的一个值
	float z = d3d9::GetRandomFloat(-m_range/2,m_range);	

	newDrop.m_pos = D3DXVECTOR3(x,m_initHeight,z);	// 雨滴的位置
	m_particles.push_back(newDrop);	// 加入雨滴
}


// 坐标 颜色 纹理
const DWORD StrRain::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;


void CRain::Render(IDirect3DDevice9* device)
{
	{
		device->SetMaterial(&d3d9::WHITE_MTRL);	// 白色材质 
		
		D3DXMATRIX  R,T;
		D3DXMatrixRotationZ(&R, -D3DX_PI / 12.0f);	// 绕Z轴旋转，让雨滴倾斜
		D3DXMatrixIdentity(&T);
		T = T * R;
		device->SetTransform(D3DTS_WORLD, &T);




		StrRain* v=0;
		m_rainBuffer->Lock(0,0,(void**)&v,D3DLOCK_DISCARD);
		
		list<CRainDrop>::iterator pointer;
		list<CRainDrop>::iterator pointerEnd = m_particles.end();

		StrRain * cpy = v;
		int count =0;
		for(pointer = m_particles.begin();pointer!=pointerEnd;pointer++)
		{
			if(pointer->mTextureLayer==-1){

				D3DXVECTOR3 tempPos = pointer->m_pos;
				v->m_color = d3d9::WHITE;	// 白色
				v->m_position = D3DXVECTOR3(tempPos.x+0.025f, tempPos.y-1.0f, tempPos.z);
				//Trace::t_log << VectorR3(v->m_position.x,v->m_position.y,v->m_position.z) << std::endl;
				v++;
				
				v->m_color = d3d9::WHITE;	// 白色
				v->m_position = D3DXVECTOR3(tempPos.x-0.025f, tempPos.y-1.0f, tempPos.z);
				//Trace::t_log << VectorR3(v->m_position.x,v->m_position.y,v->m_position.z) << std::endl;
				v++;
				
				v->m_color = d3d9::WHITE;	// 白色
				v->m_position = D3DXVECTOR3(tempPos.x, tempPos.y+0.8f, tempPos.z);
				//Trace::t_log << VectorR3(v->m_position.x,v->m_position.y,v->m_position.z) << std::endl;
				v++;
				
				//Trace::t_log << "******" << count << std::endl;
				count += 1;
			}
		}
		
		//Trace::t_log << count << std::endl;

		m_rainBuffer->Unlock();


		device->SetTexture(0, 0);
		device->SetFVF(StrRain::FVF);
		device->SetStreamSource(0, m_rainBuffer, 0, sizeof(StrRain));
		HRESULT  a = device->DrawPrimitive(	D3DPT_TRIANGLELIST,0,count);

	//	D3DXMatrixRotationZ(&R, D3DX_PI / 12.0f);	// 绕Z轴旋转，让雨滴倾斜
		D3DXMatrixIdentity(&T);
	//	T = T * R;
		device->SetTransform(D3DTS_WORLD, &T);
	}

	{
		device->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
		device->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);

		device->SetRenderState(D3DRS_ALPHAREF,0.2f);
		device->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
		device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		//device->SetRenderState(d3d`)

		device->SetMaterial(&d3d9::WHITE_MTRL);	// 白色材质 


		StrRain* v=0;
		m_quardBuffer->Lock(0,0,(void**)&v,D3DLOCK_DISCARD);

		list<CRainDrop>::iterator pointer;
		list<CRainDrop>::iterator pointerEnd = m_particles.end();



		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

		// 多级纹理采用。通过使用该过滤器，D3D 将选择尺寸与屏幕三角形最接近的那一级纹理
		// 一旦选择了某一级纹理，D3D就会用指定的放大过滤器和缩小过滤器对该级纹理进行过滤
		device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		device->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		device->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);



		int count = 0;
		for(pointer = m_particles.begin();pointer!=pointerEnd;pointer++){

			if(pointer->mTextureLayer!=-1){

				float texCoordStart = pointer->mTextureLayer/4.0f;

				D3DXVECTOR3 tempPos = pointer->m_pos;


				v->m_color = d3d9::WHITE;	// 白色
				v->m_position = D3DXVECTOR3(tempPos.x-0.25f, -0.8f, tempPos.z-0.25f);
				v->m_u = texCoordStart;
				v->m_v = 1.0f;
				v++;
				v->m_color = d3d9::WHITE;	// 白色
				v->m_u = texCoordStart;
				v->m_v = 0.0f;
				v->m_position = D3DXVECTOR3(tempPos.x-0.25f, -0.8f, tempPos.z+0.25f);
				v++;
				v->m_color = d3d9::WHITE;	// 白色
				v->m_position = D3DXVECTOR3(tempPos.x+0.25f, -0.8f, tempPos.z+0.25f);
				v->m_u = texCoordStart+0.25f;
				v->m_v = 0.0f;
				//Trace::t_log << "+++++++++++++"  << VectorR3(v->m_position.x,v->m_position.y,v->m_position.z) << std::endl;
				v++;

				v->m_color = d3d9::WHITE;	// 白色
				v->m_position = D3DXVECTOR3(tempPos.x-0.25f, -0.8f, tempPos.z-0.25f);
				v->m_u = texCoordStart;
				v->m_v = 1.0f;
				v++;
				v->m_color = d3d9::WHITE;	// 白色
				v->m_position = D3DXVECTOR3(tempPos.x+0.25f, -0.8f, tempPos.z+0.25f);
				v->m_u = texCoordStart+0.25f;
				v->m_v = 0.0f;
				//Trace::t_log << "+++++++++++++"  << VectorR3(v->m_position.x,v->m_position.y,v->m_position.z) << std::endl;
				v++;
				v->m_color = d3d9::WHITE;	// 白色
				v->m_position = D3DXVECTOR3(tempPos.x+0.25f, -0.8f, tempPos.z-0.25f);
				v->m_u = texCoordStart+0.25f;
				v->m_v = 1.0f;
				v++;

				count ++;
			}
		}

		//Trace::t_log <<"((((" <<  count << std::endl;

		m_quardBuffer->Unlock();

		device->SetTexture(0,m_Drop);
		device->SetFVF(StrRain::FVF);
		device->SetStreamSource(0, m_quardBuffer, 0, sizeof(StrRain));
		HRESULT b=device->DrawPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			2*count);

		device->SetTexture(0,0);
	}
}



void CRain::UpdateParticles(float time)
{
	list<CRainDrop>::iterator pointer;
	list<CRainDrop>::iterator pointerEnd = m_particles.end();

	for(pointer = m_particles.begin();pointer!=pointerEnd;)
	{

		D3DXVECTOR3 tempPos = pointer->m_pos;

		// 下降到地底下了
		if(tempPos.y<-1.0f){

			if(pointer->upda ==0 ){

				if(++pointer->mTextureLayer==4){

				//	Trace::t_log << " erase " << VectorR3(pointer->m_pos.x,pointer->m_pos.y,pointer->m_pos.z) << std::endl;

					pointer = m_particles.erase(pointer);
					
					if(pointer==pointerEnd)
						break;
					else
						continue;
				}
			}
			pointer->upda = (pointer->upda+1)%30;		// 一个水花的时间是64帧？？
			//Trace::t_log << pointer->upda << " ****  " << std::endl;
		}

		else if(pointer->mTextureLayer==-1)
		{
			// 还未降到地面

			// 远处的雨点下得更快些
			pointer->m_pos.y -= RAINDROP_FALLDOWN_RATE*time*d3d9::GetRandomFloat(1.0f,3.0f);
			if(tempPos.z <= 2.5f)
				pointer->m_pos.y -= RAINDROP_FALLDOWN_RATE*time;

		//	Trace::t_log << "*** " << time << " " << pointer->m_pos.y << std::endl;
		}

		pointer++;
	}

	for(int i=0;i<ADD_PARTICLES_EACH_FRAME;i++){
		if(m_particles.size()>=MAX_PARTICLES)
			break;
		AddParticle();
	}
}