// stdafx.cpp : source file that includes just the standard includes
//	OpenGL.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

CString itoa(int i){
	CString s;
	s.Format(_T("%d"), i);
	return s;
}

CString ftoa(float i){
	CString s;
	s.Format(_T("%.2f"), i);
	return s;
}

