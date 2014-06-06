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
//
// Time			:	
//					
// Email		:	KnightLiao@gmail.com	liaoqiqi@cad.zju.edu.cn
// Blog			:   http://knightliao.blogspot.com
//////////////////////////////////////////////////////////////////////////////////

//

#ifndef KNIGHT_VECTOR3R_H
#define KNIGHT_VECTOR3R_H

#include <assert.h>
#include <iostream>
#include "KnightMath.h"


using namespace std;


//****************************************************************************
// 三维矢量类
//****************************************************************************
class VectorR3 {

public:
	double x, y, z;		// The x & y & z coordinates.

public:
	// constructors
	VectorR3( ) : x(0.0), y(0.0), z(0.0) {}	// 默认构造函数
	VectorR3( double xVal, double yVal, double zVal ): x(xVal), y(yVal), z(zVal) {}

	VectorR3& operator=(const VectorR3 &v){
		x = v.x;
		y = v.y;
		z = v.z;
		return (*this);		// 引用调用
	}

	// 打印函数
	friend ostream& operator<< ( ostream& os, const VectorR3& u );

};


#endif

