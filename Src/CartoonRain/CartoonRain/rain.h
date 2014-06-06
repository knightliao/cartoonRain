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
// Description	:	��ͨ��
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


// ��ζ���ṹ
struct StrRain
{
	D3DXVECTOR3 m_position;		// λ��
	D3DCOLOR    m_color;		// ��ɫ
	float m_u, m_v;			// ���� 
	static const DWORD FVF;		// ��ʽ
};


// �����
class CRainDrop
{
public:
	D3DXVECTOR3 m_pos;		// λ��
	VectorR3 m_size;	// ��С
	D3DCOLOR m_color;	// ��ɫ

	int mTextureLayer;	// ������һ������
	int upda;		// �ڿ���ͣ����ʱ��

public:
	CRainDrop():mTextureLayer(-1),upda(0){};
	~CRainDrop(){}

};


class CRain
{
private:
	list<CRainDrop> m_particles;
	
	IDirect3DVertexBuffer9* m_rainBuffer;	// �����λ���
	IDirect3DVertexBuffer9* m_quardBuffer;	// �ı��λ���

	// 
	float m_DisappearHeight;	// ��һ����ʾ�ĸ߶�
	float m_initHeight;			// ��ʹ�߶�
	D3DXVECTOR3 m_center;
	float m_range;		// Z������Ŀ��

	IDirect3DTexture9*      m_Drop;	// �������

	int textry;
	int upda;	

	DWORD m_vbSize;	// ��һ������ʱ�䶥�㻺�������洢�Ķ����������ֵ������������ϵͳ�е�ʵ�����Ӹ���


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

