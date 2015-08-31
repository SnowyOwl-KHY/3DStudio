// OpenGL.h : main header file for the OPENGL application

#if !defined(AFX_OPENGL_H__F6C19F18_DFB7_4954_A6E5_AB30B65AF0A7__INCLUDED_)
#define AFX_OPENGL_H__F6C19F18_DFB7_4954_A6E5_AB30B65AF0A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COpenGLApp:
// See OpenGL.cpp for the implementation of this class

class COpenGLApp : public CWinApp
{
public:
	COpenGLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	public:
	virtual BOOL InitInstance();

// Implementation

		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGL_H__F6C19F18_DFB7_4954_A6E5_AB30B65AF0A7__INCLUDED_)
