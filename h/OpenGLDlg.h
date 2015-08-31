// OpenGLDlg.h : header file 
#include "stdafx.h" 
#include "afxwin.h"
#include "afxcmn.h"
#include "spotlightDlg.h"
#include "directlightDlg.h"

#include "EditListCtrl.h"
#include "Display.h"
#include "Light.h"

#if !defined(AFX_OPENGLDLG_H__8E962FCE_4DD3_4AE0_BA13_D93DE3FBA4A1__INCLUDED_) 
#define AFX_OPENGLDLG_H__8E962FCE_4DD3_4AE0_BA13_D93DE3FBA4A1__INCLUDED_ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 

#define MAXLINE 10*20

class COpenGLDlg : public CDialog 
{ 
///////////////////////////////////////////////////////////////
//dialog
public: 
	COpenGLDlg(CWnd* pParent = NULL); // standard constructor 
	enum { IDD = IDD_OPENGL_DIALOG }; 
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support 
protected: 
	HICON m_hIcon; 
	virtual BOOL OnInitDialog(); 
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam); 
	afx_msg void OnPaint(); 
	afx_msg HCURSOR OnQueryDragIcon(); 
	afx_msg void OnTimer(UINT nIDEvent); 
	DECLARE_MESSAGE_MAP() 
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
///////////////////////////////////////////////////////////////
//opengl
private:
	void initOpengl();
	BOOL SetWindowPixelFormat(HDC hDC);   //设定象素格式 
	BOOL CreateViewGLContext(HDC hDC);     //View GL Context 
	void RenderScene();                                //绘制场景 
	HDC hrenderDC;      //DC 
	HGLRC hrenderRC;  //RC 

	double PI;
	double fovY;// 在gluPerspective中使用(在OnMouseWheel中使用)
	CPoint prePt, nowPt;// 在OnMouseMove中使用
	double eyeX, eyeY, eyeZ;// 在gluLookAt中使用的3个向量
	double centerX, centerY, centerZ;
	double upX, upY, upZ;
	double tVerticalAng, tHorizonAng, tRadius, tAngInc; // 水平方向、垂直方向的角、半径
	float scaleX, scaleY, scaleZ; 

	int PixelFormat;
	ModelPainter mPainter;
	objImporter mImporter;
	Color color;
	SpotLight spotlight;
	DirectLight directlight;
	Display  dmanager;
	Roam roam;
	Translate position;
	Rotate rotation;
	Parameter parameter;

	int cylinderNo;
	int cubeNo;
	int coneNo;
	int prismoidNo;
	int sphereNo;
	int trustumNo;
	
	vector<int> elementID;
	int nowID;

	void deleteElement();
	void update();

	int eyeflag;
	int lookflag;
	int aflag;

	int slflag;
	int dlflag;

	int tnflag;
	int t1flag;
	int t2flag;
	int t3flag;
	int tfflag;
///////////////////////////////////////////////////////////////
//UI控件
public:
	CStatic mStaticViewport;
	CEditListCtrl mListElement;
	CEditListCtrl mListProperty;
	CEdit mEditDscale;
	CEdit mEditRed;
	CEdit mEditGreen;
	CEdit mEditBlue;
	CEdit mEditAlpha;
	CSliderCtrl mSliderRed;
	CSliderCtrl mSliderGreen;
	CSliderCtrl mSliderBlue;
	CSliderCtrl mSliderAlpha;
	CEdit mEditX;
	CEdit mEditY;
	CEdit mEditZ;
	CEdit mEditRX;
	CEdit mEditRY;
	CEdit mEditRZ;
	CEdit mEditA;
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonDelete();

	afx_msg void OnNMCustomdrawSliderRed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderGreen(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderBlue(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderAlpha(NMHDR *pNMHDR, LRESULT *pResult);
	
	//check
	void OnMenuItemUI(CCmdUI *pCmdUI);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnMenuQuit();
	
	afx_msg void OnMenuCylinder();
	afx_msg void OnMenuCube();
	afx_msg void OnMenuCone();
	afx_msg void OnMenuPrismoid();
	afx_msg void OnMenuSphere();
	afx_msg void OnMenuTrustum();
	
	//travel
	afx_msg void OnTransformViewport();
	afx_msg void OnTransformPosition();
			
	//光照
	afx_msg void OnSpotlightEnable();
	afx_msg void OnDirectlightEnable();
	afx_msg void OnSpotlightEdit();
	afx_msg void OnDirectlightEdit();
	//材质
	afx_msg void OnRenderMaterial();
	//纹理
	afx_msg void OnTextureNone();
	afx_msg void OnTextureTexture1();
	afx_msg void OnTextureTexture2();
	afx_msg void OnTextureTexture3();
	afx_msg void OnTextureOpenfile();
	
	CStatic mStaticTex;
	afx_msg void OnEditScreenshot();
	afx_msg void OnTravelAnimation();
	afx_msg void OnFileImport();
	afx_msg void OnFileOutport();
	afx_msg void OnMaterial();
	afx_msg void OnMaterialBrass();
	afx_msg void OnMaterialBronze();
	afx_msg void OnMaterialGold();
	afx_msg void OnMaterialWax();
	afx_msg void OnMaterialSliver();
	afx_msg void OnMaterialEmerald();
	afx_msg void OnMaterialObsidian();
	afx_msg void OnMaterialBlackplastic();
	afx_msg void OnMaterialBlackrubber();
	afx_msg void OnFileOpen();
	afx_msg void OnGameMaze();
};
#endif // !defined(AFX_OPENGLDLG_H__8E962FCE_4DD3_4AE0_BA13_D93DE3FBA4A1__INCLUDED_) 
