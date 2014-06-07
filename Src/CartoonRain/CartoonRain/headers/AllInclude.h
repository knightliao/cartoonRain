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


#ifndef _KNINGHT_ALL_INCLUDE_H_
#define _KNINGHT_ALL_INCLUDE_H_


// 载入数学库 -----------------------------------------------------------------------
#include "../../KnightMath/KnightMath.h"
#include "../../KnightMath/VectorR2.h"
#include "../../KnightMath/VectorR3.h"

#ifdef _DEBUG
#pragma comment(lib, "../KnightMath/d_lib/KnightMath.lib")
#else
#pragma comment(lib, "../KnightMath/r_lib/KnightMath.lib")
#endif
//-----------------------------------------------------------------------------------

// 载入调试库 -----------------------------------------------------------------------
#include "../../KnightTrace/Knight_Trace.h"

#ifdef _DEBUG
#pragma comment(lib, "../KnightTrace/d_lib/KnightTrace.lib")
#else
#pragma comment(lib, "../KnightTrace/r_lib/KnightTrace.lib")
#endif
//-----------------------------------------------------------------------------------

#endif