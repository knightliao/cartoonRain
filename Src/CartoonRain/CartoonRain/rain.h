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
// Description	:	卡通雨
//
// Time			:	2009 - 5 - 17
//					
// Email		:	KnightLiao@gmail.com	liaoqiqi@cad.zju.edu.cn
// Blog			:   http://knightliao.blogspot.com
////////////////////////////////////////////////////////////////////////////////////


/*	
This program is completed with DX9
*/


#ifndef _KNIGHT_RAIN_H_
#define _KNIGHT_RAIN_H_

#include <list>
#include "AllInclude.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "d3d9Utility.h"

using namespace std;


// 雨滴顶点结构
struct StrRain
{
	D3DXVECTOR3 m_position;		// 位置
	D3DCOLOR    m_color;		// 颜色
	float m_u, m_v;			// 纹理 
	static const DWORD FVF;		// 格式
};


// 雨滴类
class CRainDrop
{
public:
	D3DXVECTOR3 m_pos;		// 位置
	VectorR3 m_size;	// 大小
	D3DCOLOR m_color;	// 颜色

	int mTextureLayer;	// 该用哪一个纹理
	int upda;		// 在空中停留的时间

public:
	CRainDrop():mTextureLayer(-1),upda(0){};
	~CRainDrop(){}

};


class CRain
{
private:
	list<CRainDrop> m_particles;
	
	IDirect3DVertexBuffer9* m_rainBuffer;	// 三角形缓存
	IDirect3DVertexBuffer9* m_quardBuffer;	// 四边形缓存

	// 
	float m_DisappearHeight;	// 第一次显示的高度
	float m_initHeight;			// 初使高度
	D3DXVECTOR3 m_center;
	float m_range;		// Z方向雨的宽度

	IDirect3DTexture9*      m_Drop;	// 雨滴纹理

	int textry;
	int upda;	

	DWORD m_vbSize;	// 在一个给定时间顶点缓存中所存储的顶点个数。该值不依赖于粒子系统中的实际粒子个数


private:
	void AddParticle();
	void initBuffer();

public:
	bool InitializeParticleSystem(IDirect3DDevice9* device,float disapper,float initHeight,float range,D3DXVECTOR3 center,int parNum );
	void UpdateParticles(float time);
	void Render(IDirect3DDevice9* device);

	CRain();
	~CRain(void);
};


#endif

