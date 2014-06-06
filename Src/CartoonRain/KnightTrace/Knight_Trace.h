/////////////////////////////////////////////////////////////////////////////////
// author		:	KNIGHT
// Description	:	����ģ��
//
//					ע�⣬�����ѵ���ģ����һ��LIB���ļ����Ͳ�����CPP�ļ��ж���ȫ�ֱ���
//					Ӧ����� ���ǲ�������Ҫ����ɿ���ļ��к��������ط�Ҫ���õ�ȫ�ֱ���
//					����,���ǲ�����Knight_Trace.cpp�������������Ա���,�����ǻ��������(LINK2001)��.					
//
//					����3��ȫ�ֵ��Ա���
//					t_stream t_log t_tmp
//
// Time			:	2008/12/10
//					����ʱ�� 09-03-26
// Email		:	KnightLiao@gmail.com	liaoqiqi@cad.zju.edu.cn
// Blog			:	http://knightliao.blogspot.com
//////////////////////////////////////////////////////////////////////////////////


//+++++++++++++++++++++++++++++++++++Debug+++++++++++++++++++++++++++++++++++++++++++++


#ifndef _KNIGHT_TRACE_H_
#define _KNIGHT_TRACE_H_


#include <iostream>
#include <fstream>


class Trace {
public:
	
	static  Trace t_stream;	// ȫ�־�̬��ӡ����
	static  Trace t_log;
	static  Trace t_tmp;

	//-------------------------------���²���C�������ķ�ʽ------------------------------------------
	//---������Ļ���---
	Trace() {m_noisy = 0; m_f = stdout;}
	
	//---����C�����ļ��������---
	Trace(FILE *ff) { m_noisy = 0; m_f= ff;}

	//---����C�����ļ�����ӡ��ʽ---
	void print(char* s)
	{ 
		if(!m_stream_cplus && m_noisy)
			fprintf(m_f,"%s",s);
	}

	//---����C�����ļ���:�Ƿ������
	void on() { m_noisy = 1;}
	void off() {m_noisy = 0;}

	//-----C�����ļ����Ĺرշ�ʽ-----
	void offFile(){
		if(!m_stream_cplus){
			m_noisy = 0;
			fclose(m_f);
		}
	}
	
	//------------------------------���²���C++����C���ķ�ʽ��ʵ��------------------------------------
	//-----C++��Cʵ��,����func��ѡ����---------
	Trace(bool func,const char *filename){
		//---C++ʵ�ַ�ʽ
		if(func==true){
			m_stream_cplus = true;	// ����C++��
			m_noisy_cplus = 0;		// Ĭ�ϲ����
			m_log.open(filename);		// ��ָ���ļ�
			if(!m_log)
				std::cout << " open file " << filename << " error " << std::endl;
		}
		//--- C���Է�ʽ
		else{
			m_stream_cplus = false;	// ����C��
			m_noisy = 0;				// Ĭ�ϲ����
			fopen_s(&m_f,filename,"w");	// ��ָ���ļ�				
		}
	}

	//---����C++���ĸ������������---------
	bool setPrecision(int num){
		if(m_log && num>0){
			m_log.precision(num);
			return true;
		}
		else
			return false;
	}

	//---����C++��,�Ƿ������---------------------
	void on_stream(){m_noisy_cplus = 1;}
	void off_stream(){m_noisy_cplus = 0;}

	//---ģ�巽��,C++�������,���Ƽ�ʹ��----
	template<typename U>
	void print_stream(U u){
		if(m_stream_cplus && m_noisy_cplus)
			m_log << u << std::endl;
	}

	//---�ر�C++�ļ���----------
	void offFile_stream(){
		if(m_stream_cplus){
			m_noisy_cplus = 0;
			m_log.close();
		}
	}

	//---ģ�巽��,����ǿ���<<C++���������,���Դ������������������----------------------
	//---ǿ���Ƽ�ʹ��--------------
	//---ע�⣺
	//		Ŀǰ����֧�� m_stream << std::endl;������------
	template<typename T>
	std::ostream & operator<< (T t){

		if(m_stream_cplus && m_noisy_cplus){
			m_log << t ;
			return m_log;
		}
		return std::cout;
	}

private:
	bool m_stream_cplus;	// �Ƿ�ʹ��C++��
	int m_noisy;		// C���Ƿ������ 
	int m_noisy_cplus;	// C++���Ƿ����
	FILE* m_f;			// C������
	std::ofstream m_log;	// C++���ļ�
};


#endif