#if !defined(AFX_STDAFX_H__818AF292_0131_4AA3_890D_38F72ED1A174__INCLUDED_)
#define AFX_STDAFX_H__818AF292_0131_4AA3_890D_38F72ED1A174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#include "resource.h"
#include "GL/glut.h"
#include "m_import.h"
#include "ModelPainter.h"
#include "Light.h"
#include "texture.h"
#include "Roam.h"
#include <vector>
#include <assert.h>
#include <Windows.h>
#include "Display.h"
#include "Material.h"
#endif // !defined(AFX_STDAFX_H__818AF292_0131_4AA3_890D_38F72ED1A174__INCLUDED_)

CString itoa(int i);
CString ftoa(float i);

