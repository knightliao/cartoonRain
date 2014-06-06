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


#include "camera.h"

Camera::Camera()
{
	m_cameraType = AIRCRAFT;		// Ĭ��Ϊ�ɻ�ģʽ
	
	m_pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 0,0,0
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);		// 1,0,0
	m_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 0,1,0
	m_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);		// 0,0,1
}


// ����һ��ֻ���趨 ����� λ�� �� �۲췽��
void Camera::setPosLook(VectorR3 &pos, VectorR3 &look)
{
	D3DXVECTOR3 tmp_pos(pos.x,pos.y,pos.z);
	D3DXVECTOR3 tmp_look(look.x,look.y,look.z);
	m_pos = tmp_pos;
	m_look = tmp_look;
}

Camera::Camera(CameraType cameraType)
{
	m_cameraType = cameraType;

	m_pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

Camera::~Camera()
{

}



void Camera::getViewMatrix(D3DXMATRIX* V)
{
	// Keep camera's axes orthogonal to each other
	// ������Ϊ �ڼ�����ת�任֮�����ڸ������������������ĸ��������ܲ����Ǳ�׼������
	// ���ԣ�ÿ�ε��øú���ʱ�����Ǳ������¸�������look��������up��right�Ա�֤�����໥����
	// �µ���������up���� up = look * right�õ�
	// �µ���������right���� right = up * look ����õ�
	D3DXVec3Normalize(&m_look, &m_look);

	D3DXVec3Cross(&m_up, &m_look, &m_right);
	D3DXVec3Normalize(&m_up, &m_up);

	D3DXVec3Cross(&m_right, &m_up, &m_look);
	D3DXVec3Normalize(&m_right, &m_right);

	// Build the view matrix:
	float x = -D3DXVec3Dot(&m_right, &m_pos);
	float y = -D3DXVec3Dot(&m_up, &m_pos);
	float z = -D3DXVec3Dot(&m_look, &m_pos);

	(*V)(0,0) = m_right.x; (*V)(0, 1) = m_up.x; (*V)(0, 2) = m_look.x; (*V)(0, 3) = 0.0f;
	(*V)(1,0) = m_right.y; (*V)(1, 1) = m_up.y; (*V)(1, 2) = m_look.y; (*V)(1, 3) = 0.0f;
	(*V)(2,0) = m_right.z; (*V)(2, 1) = m_up.z; (*V)(2, 2) = m_look.z; (*V)(2, 3) = 0.0f;
	(*V)(3,0) = x;        (*V)(3, 1) = y;     (*V)(3, 2) = z;       (*V)(3, 3) = 1.0f;
}


// ��������right��ת  ����****
void Camera::pitch(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &m_right,angle);

	// rotate _up and _look around _right vector
	D3DXVec3TransformCoord(&m_up,&m_up, &T);
	D3DXVec3TransformCoord(&m_look,&m_look, &T);
}


// ƫ��
void Camera::yaw(float angle)
{
	D3DXMATRIX T;

	// rotate around world y (0, 1, 0) always for land object
	// ����LANDOBJECT���͵��������Ӧʹ������������ϵ��Y����ת����YAW�����е�UP����
	if( m_cameraType == LANDOBJECT )
		D3DXMatrixRotationY(&T, angle);

	// rotate around own up vector for aircraft
	if( m_cameraType == AIRCRAFT )
		D3DXMatrixRotationAxis(&T, &m_up, angle);

	// rotate _right and _look around _up or y-axis
	D3DXVec3TransformCoord(&m_right,&m_right, &T);
	D3DXVec3TransformCoord(&m_look,&m_look, &T);
}


// ����
void Camera::roll(float angle)
{
	// only roll for aircraft type
	// ������ȫ��ֹ�ض����巢������
	if( m_cameraType == AIRCRAFT )
	{
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &m_look,	angle);

		// rotate _up and _right around _look vector
		D3DXVec3TransformCoord(&m_right,&m_right, &T);
		D3DXVec3TransformCoord(&m_up,&m_up, &T);
	}
}


// ����look����  ע�⣬ֻ������XZƽ�����˶�
void Camera::walk(float units)
{
	// move only on xz plane for land object
	if( m_cameraType == LANDOBJECT )
		m_pos += D3DXVECTOR3(m_look.x, 0.0f, m_look.z) * units;

	if( m_cameraType == AIRCRAFT )
		m_pos += m_look * units;
}

// ɨ�ӣ���ָ���ֹ۲췽�򲻱䣬������right�����һ��ƽ�Ƶ���һ��    ע�⣬ֻ������XZƽ�����˶�
void Camera::strafe(float units)
{
	// move only on xz plane for land object
	if( m_cameraType == LANDOBJECT )
		m_pos += D3DXVECTOR3(m_right.x, 0.0f, m_right.z) * units;

	if( m_cameraType == AIRCRAFT )
		m_pos += m_right * units;
}

// ��ֹlandobject������
// ��������LANDOBJECT���͵���������Ըı���߶ȣ�������¥�ݻ���ɽ��
// ������setPosition�ֹ��������ָ����һ�����ʵĸ߶Ⱥ�λ���ϡ�
void Camera::fly(float units)
{
	if( m_cameraType == AIRCRAFT )
		m_pos += m_up * units;
}





// get set ---------------------------------------------------------
void Camera::getPosition(D3DXVECTOR3* pos)
{
	*pos = m_pos;
}

void Camera::setPosition(D3DXVECTOR3* pos)
{
	m_pos = *pos;
}

void Camera::getRight(D3DXVECTOR3* right)
{
	*right = m_right;
}

void Camera::getUp(D3DXVECTOR3* up)
{
	*up = m_up;
}

void Camera::getLook(D3DXVECTOR3* look)
{
	*look = m_look;
}

void Camera::setCameraType(CameraType cameraType)
{
	m_cameraType = cameraType;
}
