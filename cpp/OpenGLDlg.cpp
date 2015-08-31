// OpenGLDlg.cpp : implementation file 
#include "stdafx.h" 
#include "OpenGL.h" 
#include "OpenGLDlg.h"  

#ifdef _DEBUG 
#define new DEBUG_NEW 
#undef THIS_FILE 
static char THIS_FILE[] = __FILE__; 
#endif

///////////////////////////////////////////////////////////////////////////// 
// CAboutDlg dialog 
class CAboutDlg : public CDialog 
{ 
public: 
	CAboutDlg(); 
	
	// Dialog Data 
	enum { IDD = IDD_ABOUTBOX }; 
	// ClassWizard generated virtual function overrides 
protected: 
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support 
protected: 
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//virtual void OnOK();
	//DECLARE_MESSAGE_MAP()//被我自己注释掉了
//	afx_msg void OnInitMenu(CMenu* pMenu);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) 
{ 
} 

void CAboutDlg::DoDataExchange(CDataExchange* pDX) 
{ 
	CDialog::DoDataExchange(pDX); 
} 

///////////////////////////////////////////////////////////////////////////// 
// COpenGLDlg dialog 
COpenGLDlg::COpenGLDlg(CWnd* pParent /*=NULL*/)
: CDialog(COpenGLDlg::IDD, pParent) 
, dmanager(spotlight, directlight)
, roam(dmanager)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); 

	PixelFormat=0; 

	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;

	eyeflag = 0;
	lookflag = 0;
	aflag = 0;

	slflag = 0;
	dlflag = 0;
	tnflag = 0;
	t1flag = 0;
	t2flag = 0;
	t3flag = 0;
	tfflag = 0;

	cylinderNo=0;
	cubeNo=0;
	coneNo = 0;
	prismoidNo = 0;
	sphereNo = 0;
	trustumNo = 0;

	nowID = -1;
} 

void COpenGLDlg::DoDataExchange(CDataExchange* pDX) 
{ 
	CDialog::DoDataExchange(pDX);
	// NOTE: the ClassWizard will add DDX and DDV calls here 
	DDX_Control(pDX, IDC_LIST2, mListElement);
	DDX_Control(pDX, IDC_LIST1, mListProperty);
	DDX_Control(pDX, IDC_EDIT_DSCALE, mEditDscale);

	DDX_Control(pDX, IDC_EDIT_R, mEditRed);
	DDX_Control(pDX, IDC_EDIT_G, mEditGreen);
	DDX_Control(pDX, IDC_EDIT_B, mEditBlue);
	DDX_Control(pDX, IDC_SLIDER_RED, mSliderRed);
	DDX_Control(pDX, IDC_SLIDER_GREEN, mSliderGreen);
	DDX_Control(pDX, IDC_SLIDER_BLUE, mSliderBlue);

	DDX_Control(pDX, IDC_EDIT_X, mEditX);
	DDX_Control(pDX, IDC_EDIT_Y, mEditY);
	DDX_Control(pDX, IDC_EDIT_Z, mEditZ);
	DDX_Control(pDX, IDC_RENDER, mStaticViewport);
	DDX_Control(pDX, IDC_SLIDER_ALPHA, mSliderAlpha);
	DDX_Control(pDX, IDC_EDIT_ALPHA, mEditAlpha);
	DDX_Control(pDX, IDC_EDIT_X3, mEditRX);
	DDX_Control(pDX, IDC_EDIT_Y3, mEditRY);
	DDX_Control(pDX, IDC_EDIT_Z3, mEditRZ);
	DDX_Control(pDX, IDC_EDIT_A, mEditA);
	DDX_Control(pDX, IDC_STATIC_TEXTURE, mStaticTex);
}

///////////////////////////////////////////////////////////////////////////// 
// COpenGLDlg消息处理 
BEGIN_MESSAGE_MAP(COpenGLDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()

	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEMOVE()

	ON_BN_CLICKED(IDOK, &COpenGLDlg::OnBnClickedOk)

	ON_COMMAND(ID_MENU_QUIT, &COpenGLDlg::OnMenuQuit)
	ON_COMMAND(ID_MENU_CYLINDER, &COpenGLDlg::OnMenuCylinder)
	ON_COMMAND(ID_MENU_CUBE, &COpenGLDlg::OnMenuCube)
	ON_COMMAND(ID_TRANSFORM_VIEWPORT, &COpenGLDlg::OnTransformViewport)

	ON_WM_INITMENU()
	ON_WM_INITMENUPOPUP()

	//check
	ON_UPDATE_COMMAND_UI_RANGE(ID_TRANSFORM_POSITION, ID_TRANSFORM_VIEWPORT, &OnMenuItemUI)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TRANSFORM_POSITION, ID_TRANSFORM_POSITION, &OnMenuItemUI)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TRANSFORM_POSITION, ID_SPOTLIGHT_ENABLE, &OnMenuItemUI)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TRANSFORM_POSITION, ID_DIRECTLIGHT_ENABLE, &OnMenuItemUI)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TRANSFORM_POSITION, ID_TRAVEL_ANIMATION, &OnMenuItemUI)
	////check-texture
	//ON_UPDATE_COMMAND_UI_RANGE(ID_TRANSFORM_POSITION, ID_TEXTURE_NONE, &OnMenuItemUI)
	//ON_UPDATE_COMMAND_UI_RANGE(ID_TRANSFORM_POSITION, ID_TEXTURE_TEXTURE1, &OnMenuItemUI)
	//ON_UPDATE_COMMAND_UI_RANGE(ID_TRANSFORM_POSITION, ID_TEXTURE_TEXTURE2, &OnMenuItemUI)
	//ON_UPDATE_COMMAND_UI_RANGE(ID_TRANSFORM_POSITION, ID_TEXTURE_TEXTURE3, &OnMenuItemUI)
	//ON_UPDATE_COMMAND_UI_RANGE(ID_TRANSFORM_POSITION, ID_TEXTURE_OPENFILE, &OnMenuItemUI)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_RED, &COpenGLDlg::OnNMCustomdrawSliderRed)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GREEN, &COpenGLDlg::OnNMCustomdrawSliderGreen)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BLUE, &COpenGLDlg::OnNMCustomdrawSliderBlue)
	ON_WM_SIZE()
	ON_COMMAND(ID_TEXTURE_OPENFILE, &COpenGLDlg::OnTextureOpenfile)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &COpenGLDlg::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &COpenGLDlg::OnNMClickList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &COpenGLDlg::OnNMClickList1)
	ON_COMMAND(ID_SPOTLIGHT_ENABLE, &COpenGLDlg::OnSpotlightEnable)
	ON_COMMAND(ID_DIRECTLIGHT_ENABLE, &COpenGLDlg::OnDirectlightEnable)
	ON_COMMAND(ID_SPOTLIGHT_EDIT, &COpenGLDlg::OnSpotlightEdit)
	ON_COMMAND(ID_DIRECTLIGHT_EDIT, &COpenGLDlg::OnDirectlightEdit)
	ON_COMMAND(ID_MENU_CONE, &COpenGLDlg::OnMenuCone)
	ON_COMMAND(ID_MENU_PRISMOID, &COpenGLDlg::OnMenuPrismoid)
	ON_COMMAND(ID_MENU_SPHERE, &COpenGLDlg::OnMenuSphere)
	ON_COMMAND(ID_MENU_TRUSTUM, &COpenGLDlg::OnMenuTrustum)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ALPHA, &COpenGLDlg::OnNMCustomdrawSliderAlpha)
	ON_COMMAND(ID_RENDER_MATERIAL, &COpenGLDlg::OnRenderMaterial)
	ON_COMMAND(ID_TEXTURE_NONE, &COpenGLDlg::OnTextureNone)
	ON_COMMAND(ID_TEXTURE_TEXTURE1, &COpenGLDlg::OnTextureTexture1)
	ON_COMMAND(ID_TEXTURE_TEXTURE2, &COpenGLDlg::OnTextureTexture2)
	ON_COMMAND(ID_TEXTURE_TEXTURE3, &COpenGLDlg::OnTextureTexture3)
	ON_COMMAND(ID_TRANSFORM_POSITION, &COpenGLDlg::OnTransformPosition)
	ON_COMMAND(ID_EDIT_SCREENSHOT, &COpenGLDlg::OnEditScreenshot)
	ON_COMMAND(ID_TRAVEL_ANIMATION, &COpenGLDlg::OnTravelAnimation)
	ON_COMMAND(ID_FILE_IMPORT, &COpenGLDlg::OnFileImport)
	ON_COMMAND(ID_FILE_OUTPORT, &COpenGLDlg::OnFileOutport)
	ON_COMMAND(ID_MATERIAL_, &COpenGLDlg::OnMaterial)
	ON_COMMAND(ID_MATERIAL_BRASS, &COpenGLDlg::OnMaterialBrass)
	ON_COMMAND(ID_MATERIAL_BRONZE, &COpenGLDlg::OnMaterialBronze)
	ON_COMMAND(ID_MATERIAL_GOLD, &COpenGLDlg::OnMaterialGold)
	ON_COMMAND(ID_MATERIAL_WAX, &COpenGLDlg::OnMaterialWax)
	ON_COMMAND(ID_MATERIAL_SLIVER, &COpenGLDlg::OnMaterialSliver)
	ON_COMMAND(ID_MATERIAL_EMERALD, &COpenGLDlg::OnMaterialEmerald)
	ON_COMMAND(ID_MATERIAL_OBSIDIAN, &COpenGLDlg::OnMaterialObsidian)
	ON_COMMAND(ID_MATERIAL_BLACKPLASTIC, &COpenGLDlg::OnMaterialBlackplastic)
	ON_COMMAND(ID_MATERIAL_BLACKRUBBER, &COpenGLDlg::OnMaterialBlackrubber)
	ON_COMMAND(ID_FILE_OPEN32841, &COpenGLDlg::OnFileOpen)
	ON_COMMAND(ID_GAME_MAZE, &COpenGLDlg::OnGameMaze)
END_MESSAGE_MAP()

BOOL COpenGLDlg::OnInitDialog() 
{ 
	CDialog::OnInitDialog(); 
	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX); 
	ASSERT(IDM_ABOUTBOX < 0xF000); 
	CMenu* pSysMenu = GetSystemMenu(FALSE); 
	if (pSysMenu != NULL) 
	{ 
		CString strAboutMenu; 
		strAboutMenu.LoadString(IDS_ABOUTBOX); 
		if (!strAboutMenu.IsEmpty()) 
		{ 
			pSysMenu->AppendMenu(MF_SEPARATOR); 
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu); 
		} 
	} 
	// Set the icon for this dialog.  The framework does this automatically 
	//  when the application's main window is not a dialog 
	SetIcon(m_hIcon, TRUE);   // Set big icon 
	SetIcon(m_hIcon, FALSE);  // Set small icon 
	
	//UI控件初始化
	//列表
	DWORD dwStyle = mListElement.GetExtendedStyle(); //添加列表框的网格线！！！

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	mListElement.SetExtendedStyle(dwStyle);
	mListElement.InsertColumn(0, _T("No."), LVCFMT_LEFT, 50);
	mListElement.InsertColumn(1, _T("Element"), LVCFMT_LEFT,180);
	
	mListProperty.SetExtendedStyle(dwStyle);
	mListProperty.InsertColumn(0, _T("Property"), LVCFMT_LEFT,80);
	mListProperty.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 140);
	mListProperty.isData = 2;

	//文本框
	mEditDscale.SetWindowText(_T("100"));
	
	mEditRed.SetWindowText(_T("255"));
	mEditGreen.SetWindowText(_T("255"));
	mEditBlue.SetWindowText(_T("255"));
	
	mEditX.SetWindowText(_T("0.00"));
	mEditY.SetWindowText(_T("0.00"));
	mEditZ.SetWindowText(_T("0.00"));
	
	mEditRX.SetWindowText(_T("0.00"));
	mEditRY.SetWindowText(_T("0.00"));
	mEditRZ.SetWindowText(_T("0.00"));
	mEditA.SetWindowText(_T("0.00"));

	//滑块
	mSliderRed.SetRange(0, 255);
	mSliderRed.SetTicFreq(1);
	mSliderRed.SetPos(255);
	mSliderGreen.SetRange(0, 255);
	mSliderRed.SetTicFreq(5);
	mSliderGreen.SetPos(255);
	mSliderBlue.SetRange(0, 255);
	mSliderRed.SetTicFreq(2);
	mSliderBlue.SetPos(255);

	///////////////////////OPENGL INIT///////////////////////// 
	CWnd *wnd=GetDlgItem(IDC_RENDER); 
    hrenderDC=::GetDC(wnd->m_hWnd); 
	if(SetWindowPixelFormat(hrenderDC)==FALSE) 
		return 0; 
	if(CreateViewGLContext(hrenderDC)==FALSE) 
		return 0; 

	initOpengl();

	return TRUE;  // return TRUE  unless you set the focus to a control 
} 

void COpenGLDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{ 
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) 
	{ 
		CAboutDlg dlgAbout; 
		dlgAbout.DoModal(); 
	} 
	else 
	{ 
		CDialog::OnSysCommand(nID, lParam); 
	} 
} 

void COpenGLDlg::OnPaint() 
{ 
	if (IsIconic()) 
	{ 
		CPaintDC dc(this); // device context for painting 
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0); 
		// Center icon in client rectangle 
		int cxIcon = GetSystemMetrics(SM_CXICON); 
		int cyIcon = GetSystemMetrics(SM_CYICON); 
		CRect rect; 
		GetClientRect(&rect); 
		int x = (rect.Width() - cxIcon + 1) / 2; 
		int y = (rect.Height() - cyIcon + 1) / 2; 
		// Draw the icon 
		dc.DrawIcon(x, y, m_hIcon); 
	} 
	else 
	{ 
		CDialog::OnPaint(); 
	} 
} 

HCURSOR COpenGLDlg::OnQueryDragIcon() 
{ 
	return (HCURSOR) m_hIcon; 
} 

///////////////////////////////////////////////////////////////////////////// 
//opengl init
BOOL CAboutDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此添加专用代码和/或调用基类
	cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_THICKFRAME;
	return CDialog::PreCreateWindow(cs);
}

BOOL COpenGLDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	wglDeleteContext(hrenderRC);
	return CDialog::DestroyWindow();
}

BOOL COpenGLDlg::SetWindowPixelFormat(HDC hDC) 
{ 
	PIXELFORMATDESCRIPTOR pixelDesc; 
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR); 
	pixelDesc.nVersion = 1; 
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | 
		PFD_SUPPORT_OPENGL | 
		PFD_DOUBLEBUFFER | 
		PFD_TYPE_RGBA; 
	pixelDesc.iPixelType = PFD_TYPE_RGBA; 
	pixelDesc.cColorBits = 32; 
	pixelDesc.cRedBits = 0; 
	pixelDesc.cRedShift = 0; 
	pixelDesc.cGreenBits = 0; 
	pixelDesc.cGreenShift = 0; 
	pixelDesc.cBlueBits = 0; 
	pixelDesc.cBlueShift = 0; 
	pixelDesc.cAlphaBits = 0; 
	pixelDesc.cAlphaShift = 0; 
	pixelDesc.cAccumBits = 0; 
	pixelDesc.cAccumRedBits = 0; 
	pixelDesc.cAccumGreenBits = 0; 
	pixelDesc.cAccumBlueBits = 0; 
	pixelDesc.cAccumAlphaBits = 0; 
	pixelDesc.cDepthBits = 0; 
	pixelDesc.cStencilBits = 1; 
	pixelDesc.cAuxBuffers = 0; 
	pixelDesc.iLayerType = PFD_MAIN_PLANE; 
	pixelDesc.bReserved = 0; 
	pixelDesc.dwLayerMask = 0; 
	pixelDesc.dwVisibleMask = 0; 
	pixelDesc.dwDamageMask = 0; 
	PixelFormat = ChoosePixelFormat(hDC,&pixelDesc); 
	if(PixelFormat==0) // Choose default 
	{ 
		PixelFormat = 1; 
		if(DescribePixelFormat(hDC,PixelFormat, 
			sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0) 
		{ 
			return FALSE; 
		} 
	} 
	if(SetPixelFormat(hDC,PixelFormat,&pixelDesc)==FALSE) 
	{ 
		return FALSE; 
	} 
	return TRUE; 
} 

BOOL COpenGLDlg::CreateViewGLContext(HDC hDC) 
{ 
	hrenderRC = wglCreateContext(hDC); 
	if(hrenderRC==NULL) 
		return FALSE; 
	if(wglMakeCurrent(hDC,hrenderRC)==FALSE) 
		return FALSE; 
	return TRUE; 
} 

///////////////////////////////////////////////////////////////////////////// 
//opengl 绘制
//初始化opengl
void COpenGLDlg::initOpengl(){
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	CRect rect;
	GetDlgItem(IDC_RENDER)->GetWindowRect(&rect);
	glViewport(0, 0, rect.Width(), rect.Height());

	glShadeModel(GL_SMOOTH);       // Enable Smooth Shading 
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);    // Black Background 
	glClearDepth(1.0f);         // Depth Buffer Setup 
	glEnable(GL_DEPTH_TEST);       // Enables Depth Testing 
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do 
	///////////////////////////////////////////////////////////////////////// 
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	SetTimer(1, 10, 0);//ID为1，定时10ms

	// TODO: Add extra initialization here 
	// 通过鼠标操作调整openGL视角的设置
	fovY = 45.0;
	prePt.SetPoint(-1, -1);                 // 初始化prePt & nowPt(在OnMouseMove中使用)
	nowPt.SetPoint(-1, -1);
	

	dmanager.initTexture();//初始化纹理
}
 
//绘制场景
void COpenGLDlg::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovY, 1, 0.1, 1000.0);// 注意zNear,zFar的取值

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(roam.eyeX, roam.eyeY, roam.eyeZ, roam.centerX, roam.centerY, roam.centerZ, roam.upX, roam.upY, roam.upZ);
	glClear(GL_COLOR_BUFFER_BIT);

	glScalef(scaleX, scaleY, scaleZ);
	
	//网格线
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINES); {
		for (int i = -MAXLINE; i < MAXLINE + 20; i += 20){
			glVertex3f(i, 0.0f, -MAXLINE);
			glVertex3f(i, 0.0f, MAXLINE);
		}
		for (int i = -MAXLINE; i < MAXLINE + 20; i += 20){
			glVertex3f(-MAXLINE, 0.0f, i);
			glVertex3f(MAXLINE, 0.0f, i);
		}
	}glEnd();

	//箭头
	const float offset = -200;
	float signX = 1.0;
	float signY = 1.0;/// X,Y轴向的符号标记
	float deltX = 30;
	float deltY = 30;
	float cosalph = deltX / sqrt(deltX*deltX + deltY*deltY);//算一算旋转的角度
	float sinalph = deltY / sqrt(deltX*deltX + deltY*deltY);
	float x = cosalph*(-5 * signX);
	float y = sinalph*(-5 * signY);
	
	if (deltX >= 0){
		signX = -1.0;
	}
	if (deltY >= 0){
		signY = -1.0;
	}

	// 画带箭头的直线
	glColor3f(0, 1.0, 1.0);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES); {
		glVertex3f(offset, 0, offset);
		glVertex3f(offset, 30, offset);
	}glEnd();
	glBegin(GL_LINE_STRIP); {
		glVertex3f(offset, (x*cos(-0.5) - y*sin(-0.5)) + 30, (x*sin(-0.5) + y*cos(-0.5)) + offset);
		glVertex3f(offset, 30, offset);
		glVertex3f(offset, (x*cos(0.5) + y*sin(0.5)) + 30, (x*sin(0.5) - y*cos(0.5)) + offset);
	}glEnd();
	glDisable(GL_LINE_SMOOTH);

	//绘制图形
	dmanager.show();
	
	roam.flashRotate();

	SwapBuffers(hrenderDC);
}

//实时绘制&动画
void COpenGLDlg::OnTimer(UINT nIDEvent) //实时绘制场景 
{ 
	RenderScene(); 

	if (mListElement.getChangeEnd()){
		mListElement.setChangeEnd(false);
	}
	if (mListProperty.getChangeEnd()){
		int ni, ns;
		CString s = mListProperty.getNewData();
		vector<CString> values;
		for (int i = mListProperty.GetItemCount() - 1; i >= 0; i--){
			values.push_back(mListProperty.GetItemText(i, 1));
		}
		dmanager.update(nowID, values);

		mListProperty.setChangeEnd(false);
	}

	

	CDialog::OnTimer(nIDEvent); 
} 

//键盘控制//回车输入参数！
BOOL COpenGLDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	CString strText;
	
	switch (pMsg->message){ //注意这里的参数设置。
	case WM_KEYDOWN:
		switch (pMsg->wParam)
		{
			//放大缩小
		case 187://ctrl + +
			if (GetKeyState(VK_CONTROL)<0){
				scaleX += 0.1;
				scaleY += 0.1;
				scaleZ += 0.1;
				mEditDscale.GetWindowText(strText);
				strText.Format(_T("%d"), _ttoi(strText) + 10);
				mEditDscale.SetWindowText(strText);
			}
			break;
		case 189://ctrl + -
			if (GetKeyState(VK_CONTROL)<0){
				scaleX -= 0.1;
				scaleY -= 0.1;
				scaleZ -= 0.1;
				mEditDscale.GetWindowText(strText);
				strText.Format(_T("%d"), _ttoi(strText) - 10);
				mEditDscale.SetWindowText(strText);
			}
			break;
		case VK_UP:
			if (GetKeyState(VK_CONTROL)<0){
				roam.ahead();
			}
			else if (nowID >= 0){
				mEditZ.GetWindowText(strText);
				position.z = _ttof(strText)+1;
				mEditZ.SetWindowText(ftoa(position.z));
				dmanager.update(nowID, position);
			}
			break;
		case VK_DOWN:
			if (GetKeyState(VK_CONTROL)<0)
				roam.back();
			else if (nowID >= 0){
				mEditZ.GetWindowText(strText);
				position.z = _ttof(strText) - 1;
				mEditZ.SetWindowText(ftoa(position.z));
				dmanager.update(nowID, position);
			}
			break;
		case VK_LEFT:
			if (GetKeyState(VK_CONTROL)<0){
				roam.turnLeft();
				//roam.left();
			}
			else if (nowID >= 0){
				mEditX.GetWindowText(strText);
				position.x = _ttof(strText) + 1;
				mEditX.SetWindowText(ftoa(position.x));
				dmanager.update(nowID, position);
			}
			break;
		case VK_RIGHT:
			if (GetKeyState(VK_CONTROL) < 0){
				roam.turnRight();
				//roam.right();
			}
			else if(nowID>=0){
				mEditX.GetWindowText(strText);
				position.x = _ttof(strText) - 1;
				mEditX.SetWindowText(ftoa(position.x));
				dmanager.update(nowID, position);
			}
			break;
		case VK_PRIOR:
			if (GetKeyState(VK_CONTROL)<0){
				roam.up();
			}
			else if (nowID >= 0){
				mEditY.GetWindowText(strText);
				position.y = _ttof(strText) + 1;
				mEditY.SetWindowText(ftoa(position.y));
				dmanager.update(nowID, position);
			}
			break;
		case VK_NEXT:
			if (GetKeyState(VK_CONTROL)<0){
				roam.down();
			}
			else if (nowID >= 0){
				mEditY.GetWindowText(strText);
				position.y = _ttof(strText) - 1;
				mEditY.SetWindowText(ftoa(position.y));
				dmanager.update(nowID, position);
			}
			break;
		case 'A':
			roam.left();
			break;
		case 'D':
			roam.right();
			break;
		case 'W':
			roam.ahead();
			break;
		case 'S':
			roam.back();
			break;
		case 'E':
			roam.up();
			break;
		case 'C':
			roam.down();
			break;
		//return
		case VK_RETURN:
			UpdateData();
			//缩放
			if (GetDlgItem(IDC_EDIT_DSCALE) == GetFocus()){
				mEditDscale.GetWindowText(strText);
				scaleX = _ttoi(strText) / 100.0;
				scaleY = _ttoi(strText) / 100.0;
				scaleZ = _ttoi(strText) / 100.0;
			}
			//调节颜色
			if (GetDlgItem(IDC_EDIT_R) == GetFocus()){
				mEditRed.GetWindowText(strText);
				color.r = _ttoi(strText);
				mSliderRed.SetPos(_ttoi(strText));
				dmanager.update(nowID, color);
			}
			if (GetDlgItem(IDC_EDIT_G) == GetFocus()){
				mEditGreen.GetWindowText(strText);
				color.g = _ttoi(strText);
				mSliderGreen.SetPos(_ttoi(strText));
				dmanager.update(nowID, color);
			}
			if (GetDlgItem(IDC_EDIT_B) == GetFocus()){
				mEditBlue.GetWindowText(strText);
				color.b = _ttoi(strText);
				mSliderBlue.SetPos(_ttoi(strText));
				dmanager.update(nowID, color);
			}
			if (GetDlgItem(IDC_EDIT_ALPHA) == GetFocus()){
				mEditAlpha.GetWindowText(strText);
				color.a = _ttoi(strText);
				mSliderAlpha.SetPos(_ttoi(strText));
				dmanager.update(nowID, color);
			}
			//调节位置
			if (GetDlgItem(IDC_EDIT_X) == GetFocus()){
				mEditX.GetWindowText(strText);
				position.x = _ttof(strText);
				dmanager.update(nowID, position);
			}
			if (GetDlgItem(IDC_EDIT_Y) == GetFocus()){
				mEditY.GetWindowText(strText);
				position.y = _ttof(strText);
				dmanager.update(nowID, position);
			}
			if (GetDlgItem(IDC_EDIT_Z) == GetFocus()){
				mEditZ.GetWindowText(strText);
				position.z = _ttof(strText);
				dmanager.update(nowID, position);
			}
			//旋转
			if (GetDlgItem(IDC_EDIT_X3) == GetFocus()){
				mEditRX.GetWindowText(strText);
				rotation.x = _ttof(strText);
				dmanager.update(nowID, rotation);
			}
			if (GetDlgItem(IDC_EDIT_Y3) == GetFocus()){
				mEditRY.GetWindowText(strText);
				rotation.y = _ttof(strText);
				dmanager.update(nowID, rotation);
			}
			if (GetDlgItem(IDC_EDIT_Z3) == GetFocus()){
				mEditRZ.GetWindowText(strText);
				rotation.z = _ttof(strText);
				dmanager.update(nowID, rotation);
			}
			if (GetDlgItem(IDC_EDIT_A) == GetFocus()){
				mEditA.GetWindowText(strText);
				rotation.angle = _ttof(strText);
				dmanager.update(nowID, rotation);
			}
			//列表编辑
			if (mListElement.GetFocus()){
				mListElement.setChange(true);
			}
			if (mListProperty.GetFocus()){
				mListProperty.setChange(true);
			}
			break;
		case 'X'://退出迷宫
			//if (GetKeyState(VK_CONTROL)<0){
			roam.disableMaze();
			//}
			break;
		case VK_DELETE: 
			if (GetKeyState(VK_CONTROL)<0 && mListElement.GetFocus()){
				deleteElement();
			}
			break;
		default:
			break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

//鼠标控制
void COpenGLDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	WINDOWPLACEMENT wp;
	RECT rect;
	GetDlgItem(IDC_RENDER)->GetWindowPlacement(&wp);  //client坐标系  
	rect = wp.rcNormalPosition;//将鼠标操作限制在viewport内
	if (point.x> rect.left && point.x < rect.right&& point.y> rect.top && point.y <rect.bottom&& nFlags & MK_LBUTTON == TRUE){
		nowPt.x = point.x;
		nowPt.y = point.y;
		if (prePt.x != -1 && prePt.y != -1 && nowPt.x != -1 && nowPt.y != -1) {
			if (eyeflag)
				roam.rotateEye(nowPt, prePt);
			if (lookflag)
				roam.rotateCenter(nowPt, prePt);
		}
		prePt.x = nowPt.x;
		prePt.y = nowPt.y;
	}

	CDialog::OnMouseMove(nFlags, point);
}

//鼠标滚轮控制
void COpenGLDlg::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int tWheelCount = zDelta / 120;
	if (tWheelCount > 0) {
		fovY += 1.0;
	}
	else if (tWheelCount < 0) {
		fovY -= 1.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                                            // 此处尤其不可少glLoadIdentity()
	gluPerspective(fovY, 1, 0.1, 1000.0);                        // 注意zNear,zFar的取值
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//return TRUE;
	CDialog::OnMouseHWheel(nFlags, zDelta, pt);
}

///////////////////////////////////////////////////////////////////////////// 
//UI控件
void COpenGLDlg::deleteElement(){
	for (int i = mListElement.GetItemCount()-1; i >=0 ;i--){
		if (mListElement.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED){
			//int k = _ttoi(mListElement.GetItemText(i, 0)) - 1;
			int k = mListElement.GetItemCount() - 1 - i;
			//MessageBox(itoa(k));
			mListElement.DeleteItem(i);
			nowID = elementID[k];
			dmanager.del(nowID);
			elementID.erase(elementID.begin() + k);
			//MessageBox(_T("ok"));
		}
	}
	//更新mListElement中的序号
	int n = 1;
	for (int i = mListElement.GetItemCount() - 1; i >= 0; i--){
		mListElement.SetItemText(i, 0, itoa(n));     //将第i行的第1个item修改为2
		n++;
	}
}

//重载ok，使按enter时不退出
void COpenGLDlg::OnBnClickedOk(){
	return;
}

//菜单控件
void COpenGLDlg::OnMenuQuit()
{
	// TODO:  在此添加命令处理程序代码
	CDialog::OnCancel();
}

//cylinder
void COpenGLDlg::OnMenuCylinder()
{
	int nRow = mListElement.InsertItem(0, itoa(mListElement.GetItemCount() + 1));// 插入行
	mListElement.SetItemText(nRow, 1, "cylinder" + itoa(cylinderNo));//设置其它列数据
	cylinderNo++;

	nowID = dmanager.add(CYLINDER);
	elementID.push_back(nowID);
	update();
}

//cube
void COpenGLDlg::OnMenuCube()
{
	int nRow = mListElement.InsertItem(0, itoa(mListElement.GetItemCount()+1));// 插入行
	mListElement.SetItemText(nRow, 1, "cube"+itoa(cubeNo));//设置其它列数据
	cubeNo++;

	nowID = dmanager.add(CUBE);
	elementID.push_back(nowID);
	update();
}

//cone
void COpenGLDlg::OnMenuCone()
{
	// TODO:  在此添加命令处理程序代码
	int nRow = mListElement.InsertItem(0, itoa(mListElement.GetItemCount() + 1));// 插入行
	mListElement.SetItemText(nRow, 1, "cone" + itoa(coneNo));//设置其它列数据
	coneNo++;

	nowID = dmanager.add(CONE);
	elementID.push_back(nowID);
	update();
}

//prismoid
void COpenGLDlg::OnMenuPrismoid()
{
	// TODO:  在此添加命令处理程序代码
	int nRow = mListElement.InsertItem(0, itoa(mListElement.GetItemCount() + 1));// 插入行
	mListElement.SetItemText(nRow, 1, "prismoid" + itoa(prismoidNo));//设置其它列数据
	prismoidNo++;

	nowID = dmanager.add(PRISMOID);
	elementID.push_back(nowID);
	update();
}

//sphere
void COpenGLDlg::OnMenuSphere()
{
	// TODO:  在此添加命令处理程序代码
	int nRow = mListElement.InsertItem(0, itoa(mListElement.GetItemCount() + 1));// 插入行
	mListElement.SetItemText(nRow, 1, "sphere" + itoa(sphereNo));//设置其它列数据
	sphereNo++;

	nowID = dmanager.add(SPHERE);
	elementID.push_back(nowID);
	update();
}

//trustum
void COpenGLDlg::OnMenuTrustum()
{
	// TODO:  在此添加命令处理程序代码
	int nRow = mListElement.InsertItem(0, itoa(mListElement.GetItemCount() + 1));// 插入行
	mListElement.SetItemText(nRow, 1, "trustum" + itoa(trustumNo));//设置其它列数据
	trustumNo++;

	nowID = dmanager.add(TRUSTUM);
	elementID.push_back(nowID);
	update();
}

void COpenGLDlg::OnTransformViewport(){
	if (lookflag == 1 && eyeflag == 0){
		lookflag = 0;
	}
	eyeflag = !eyeflag;	
}

void COpenGLDlg::OnTransformPosition()
{
	if (eyeflag == 1 && lookflag == 0){
		eyeflag = 0;
	}
	lookflag = !lookflag;
}

void COpenGLDlg::OnTravelAnimation()
{
	// TODO:  在此添加命令处理程序代码
	aflag = !aflag;
	if (aflag){
		roam.flash();
	}
}

//菜单check
void COpenGLDlg::OnInitMenu(CMenu* pMenu)
{
	CDialog::OnInitMenu(pMenu);

	// TODO:  在此处添加消息处理程序代码
	
}

void COpenGLDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO:  在此处添加消息处理程序代码
	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// Determine if menu is popup in top-level menu and set m_pOther to 
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup). 
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup. 
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		// Child windows don't have menus--need to go to the top! 
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// When popup is found, m_pParentMenu is containing menu. 
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
		state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it. 

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// Possibly a popup menu, route to first item of that popup. 
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // First item of popup can't be routed to. 
			}
			state.DoUpdate(this, TRUE);   // Popups are never auto disabled. 
		}
		else
		{
			// Normal menu item. 
			// Auto enable/disable if frame window has m_bAutoMenuEnable 
			// set and command is _not_ a system command. 
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}

		// Adjust for menu deletions and additions. 
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}

void COpenGLDlg::OnMenuItemUI(CCmdUI *pCmdUI){
	if (pCmdUI->m_nID == ID_TRANSFORM_VIEWPORT){
		pCmdUI->SetCheck(eyeflag);
	}
	if (pCmdUI->m_nID == ID_TRANSFORM_POSITION){
		pCmdUI->SetCheck(lookflag);
	}
	if (pCmdUI->m_nID == ID_TRAVEL_ANIMATION){
		pCmdUI->SetCheck(aflag);
	}
	if (pCmdUI->m_nID == ID_SPOTLIGHT_ENABLE){
		pCmdUI->SetCheck(slflag);
	}
	if (pCmdUI->m_nID == ID_DIRECTLIGHT_ENABLE){
		pCmdUI->SetCheck(dlflag);
	}
	////texture
	//if (pCmdUI->m_nID == ID_TEXTURE_NONE){
	//	pCmdUI->SetCheck(tnflag);
	//}
	//if (pCmdUI->m_nID == ID_TEXTURE_TEXTURE1){
	//	pCmdUI->SetCheck(t1flag);
	//}
	//if (pCmdUI->m_nID == ID_TEXTURE_TEXTURE2){
	//	pCmdUI->SetCheck(t2flag);
	//}
	//if (pCmdUI->m_nID == ID_TEXTURE_TEXTURE3){
	//	pCmdUI->SetCheck(t3flag);
	//}
	//if (pCmdUI->m_nID == ID_TEXTURE_OPENFILE){
	//	pCmdUI->SetCheck(tfflag);
	//}
}

//slider
void COpenGLDlg::OnNMCustomdrawSliderRed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	color.r = mSliderRed.GetPos();
	dmanager.update(nowID, color);
	CString s;
	s.Format(_T("%d"), mSliderRed.GetPos());
	mEditRed.SetWindowText(s);
	UpdateData(FALSE);
	*pResult = 0;
}

void COpenGLDlg::OnNMCustomdrawSliderGreen(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	color.g = mSliderGreen.GetPos();
	dmanager.update(nowID, color);
	CString s;
	s.Format(_T("%d"), mSliderGreen.GetPos());
	mEditGreen.SetWindowText(s);
	UpdateData(FALSE);
	*pResult = 0;
}

void COpenGLDlg::OnNMCustomdrawSliderBlue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	color.b = mSliderBlue.GetPos();
	dmanager.update(nowID, color);
	CString s;
	s.Format(_T("%d"), mSliderBlue.GetPos());
	mEditBlue.SetWindowText(s);
	UpdateData(FALSE);
	*pResult = 0;
}

void COpenGLDlg::OnNMCustomdrawSliderAlpha(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	color.a = mSliderAlpha.GetPos();
	dmanager.update(nowID, color);
	CString s;
	s.Format(_T("%d"), mSliderAlpha.GetPos());
	mEditAlpha.SetWindowText(s);
	UpdateData(FALSE);
	*pResult = 0;
}

void COpenGLDlg::OnBnClickedButtonDelete(){
	// TODO:  在此添加控件通知处理程序代码
	deleteElement();
}

void COpenGLDlg::update(){
	vector<CString> paraName = dmanager.getParaName(nowID);
	vector<CString> paraValue = dmanager.getParaValue(nowID);

	//更新mListProperty
	for (int i = mListProperty.GetItemCount() - 1; i >= 0; i--){
		mListProperty.DeleteItem(i);
	}
	for (int i = 0; i < paraName.size(); i++){
		int nRow = mListProperty.InsertItem(0, paraName[i]);// 插入行
		mListProperty.SetItemText(nRow, 1, paraValue[i]);//设置其它列数据
	}

	//更新其他
	color = dmanager.getCol(nowID);
	vector<CString> colorValue = dmanager.getColor(nowID);
	//AfxMessageBox("colorValue:" + itoa(colorValue.size()));
	mEditRed.SetWindowText(colorValue[0]);
	mEditGreen.SetWindowText(colorValue[1]);
	mEditBlue.SetWindowText(colorValue[2]);
	mEditAlpha.SetWindowText(colorValue[3]);
	mSliderRed.SetPos(_ttoi(colorValue[0]));
	mSliderGreen.SetPos(_ttoi(colorValue[1]));
	mSliderBlue.SetPos(_ttoi(colorValue[2]));
	mSliderAlpha.SetPos(_ttoi(colorValue[3]));

	position = dmanager.getTra(nowID);
	vector<CString> posValue = dmanager.getTranslate(nowID);
	mEditX.SetWindowText(posValue[0]);
	mEditY.SetWindowText(posValue[1]);
	mEditZ.SetWindowText(posValue[2]);

	rotation = dmanager.getRot(nowID);
	vector<CString> rotValue = dmanager.getRotate(nowID);
	//AfxMessageBox("rotValue:" + itoa(rotValue.size()));
	mEditRX.SetWindowText(rotValue[1]);
	mEditRY.SetWindowText(rotValue[2]);
	mEditRZ.SetWindowText(rotValue[3]);
	mEditA.SetWindowText(rotValue[0]);

	mStaticTex.SetWindowText(dmanager.getTextureName(nowID));
}

//选中一个element
void COpenGLDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	
	int nItem = pNMItemActivate->iItem;
	if (nItem>=0)
	{
		nowID=elementID[_ttoi(mListElement.GetItemText(nItem, 0))-1];
		//AfxMessageBox(itoa(nowID));
		update();//更新数据
	}

	

	*pResult = 0;
}

//property列表
void COpenGLDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	int nItem = pNMItemActivate->iItem;
	
	if (nItem >= 0)
	{
		//输入要求int的情况
		switch (dmanager.getType(nowID)){
		case CYLINDER:
			if (nItem == 2 || nItem==3)
				mListProperty.isData = 1;
			break;
		case CONE:
			if (nItem == 2 || nItem == 3)
				mListProperty.isData = 1;
			break;
		case SPHERE:
			if (nItem == 1 || nItem == 2)
				mListProperty.isData = 1;
			break;
		case PRISMOID:
			if (nItem == 0)
				mListProperty.isData = 1;
			break;
		case TRUSTUM:
			if (nItem == 0)
				mListProperty.isData = 1;
			break;
		default:
			mListProperty.isData = 2;
		}

		//AfxMessageBox(itoa(nowID));
	}
	*pResult = 0;
}

//light
void COpenGLDlg::OnSpotlightEnable()
{
	// TODO:  在此添加命令处理程序代码
	slflag = !slflag;
	if (slflag){
		spotlight.enable();
		//spotlight.show();
	}
	else{
		spotlight.disable();
	}
}

void COpenGLDlg::OnDirectlightEnable()
{
	// TODO:  在此添加命令处理程序代码
	dlflag = !dlflag;
	if (dlflag){
		directlight.enable();
		//directlight.show();
	}
	else{
		directlight.disable();
	}
}

void COpenGLDlg::OnSpotlightEdit()
{
	// TODO:  在此添加命令处理程序代码
	spotlightDlg slDlg(spotlight);
	slDlg.DoModal();
	//spotlight.show();
}

void COpenGLDlg::OnDirectlightEdit()
{
	// TODO:  在此添加命令处理程序代码
	directlightDlg dlDlg(directlight);
	dlDlg.DoModal();
	//directlight.show();
}

//材质
void COpenGLDlg::OnRenderMaterial()
{
	// TODO:  在此添加命令处理程序代码

}

//纹理
void COpenGLDlg::OnTextureNone()
{
	// TODO:  在此添加命令处理程序代码
	tnflag = !tnflag;
	dmanager.update(nowID, -1);
	mStaticTex.SetWindowText(dmanager.getTextureName(nowID));
}

void COpenGLDlg::OnTextureTexture1()
{
	// TODO:  在此添加命令处理程序代码
	t1flag = !t1flag;
	dmanager.update(nowID, 0);
	mStaticTex.SetWindowText(dmanager.getTextureName(nowID));
}

void COpenGLDlg::OnTextureTexture2()
{
	// TODO:  在此添加命令处理程序代码
	t2flag = !t2flag;
	dmanager.update(nowID, 1);
	mStaticTex.SetWindowText(dmanager.getTextureName(nowID));
}

void COpenGLDlg::OnTextureTexture3()
{
	t3flag = !t3flag;
	dmanager.update(nowID, 2);
	mStaticTex.SetWindowText(dmanager.getTextureName(nowID));
}

//选择纹理图片
void COpenGLDlg::OnTextureOpenfile()
{
	tfflag = !tfflag;
	const TCHAR szFilters[] = _T("MyType Files (*.bmp)|*.bmp|All Files (*.*)|*.*||");

	CFileDialog fileDlg(TRUE, _T("bmp"), _T("*.bmp"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);

	CString fileName;
	CString file;
	if (fileDlg.DoModal() == IDOK)
	{
		//fileName = fileDlg.GetFileName(); 
		file = fileDlg.GetPathName();//√
		UpdateData(false);
		dmanager.update(nowID, file);//直接用CString好像可以诶！
	}
	
}

//截屏 至剪切板！
void COpenGLDlg::OnEditScreenshot()
{
	typedef void (WINAPI * TESTDLL)();

	HINSTANCE hmod;
	hmod = ::LoadLibrary(_T("Screenshot.dll"));
	if (hmod == NULL)
	{
		AfxMessageBox(_T("Fail"));
	}
	TESTDLL lpproc;
	lpproc = (TESTDLL)GetProcAddress(hmod, "Show");
	if (lpproc != (TESTDLL)NULL)
		(*lpproc)();
	FreeLibrary(hmod);
}

void COpenGLDlg::OnFileOpen()
{
	// TODO:  在此添加命令处理程序代码
	const TCHAR szFilters[] = _T("MyType Files (*.dsproj)|*.dsproj|All Files (*.*)|*.*||");

	CFileDialog fileDlg(TRUE, _T("dsproj"), _T("*.dsproj"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);

	CString fileName;
	CString file;
	if (fileDlg.DoModal() == IDOK)
	{
		file = fileDlg.GetPathName();
		UpdateData(false);

		map<int, Type> m=dmanager.importObj(file);
		for (map<int, Type>::iterator it = m.begin(); it != m.end(); it++){
			elementID.push_back(it->first);
			int nRow = mListElement.InsertItem(0, itoa(mListElement.GetItemCount() + 1));// 插入行
			
			switch (it->second){
			case CYLINDER:
				cylinderNo++;
				mListElement.SetItemText(nRow, 1, "cylinder" + itoa(cylinderNo));//设置其它列数据
				break;
			case CUBE:
				cubeNo++;
				mListElement.SetItemText(nRow, 1, "cube" + itoa(cubeNo));
				break;
			case CONE:
				coneNo++;
				mListElement.SetItemText(nRow, 1, "cone" + itoa(coneNo));
				break;
			case PRISMOID:
				prismoidNo++;
				mListElement.SetItemText(nRow, 1, "prismoid" + itoa(prismoidNo));
				break;
			case SPHERE:
				sphereNo++;
				mListElement.SetItemText(nRow, 1, "sphere" + itoa(sphereNo));
				break;
			case TRUSTUM:
				trustumNo++;
				mListElement.SetItemText(nRow, 1, "trustum" + itoa(trustumNo));
				break;
			}
		}
	}
}

void COpenGLDlg::OnFileImport()
{
	// TODO:  在此添加命令处理程序代码
	const TCHAR szFilters[] = _T("MyType Files (*.obj)|*.obj|All Files (*.*)|*.*||");

	CFileDialog fileDlg(TRUE, _T("obj"), _T("*.obj"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);

	CString fileName;
	CString file;
	if (fileDlg.DoModal() == IDOK)
	{
		file = fileDlg.GetPathName();
		UpdateData(false);
		
		int nRow = mListElement.InsertItem(0, itoa(mListElement.GetItemCount() + 1));// 插入行
		mListElement.SetItemText(nRow, 1, file);//设置其它列数据
		nowID = dmanager.addImportObject(file);
		elementID.push_back(nowID);
	}
}

void COpenGLDlg::OnFileOutport()
{
	// TODO:  在此添加命令处理程序代码
	const TCHAR szFilters[] = _T("MyType Files (*.dsproj)|*.dsproj|All Files (*.*)|*.*||");

	CFileDialog fileDlg(FALSE, _T("dsproj"), _T("*.dsproj"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);

	CString fileName;
	CString file;
	if (fileDlg.DoModal() == IDOK)
	{
		fileName = fileDlg.GetFileName();
		file = fileDlg.GetPathName();
		UpdateData(false);
		dmanager.exportObj(file);//他要绝对路径？
	}
}

//材质
void COpenGLDlg::OnMaterial()
{
	dmanager.setMaterial(nowID, -1);
}

void COpenGLDlg::OnMaterialBrass()
{
	dmanager.setMaterial(nowID, 0);
}

void COpenGLDlg::OnMaterialBronze()
{
	dmanager.setMaterial(nowID, 1);
}

void COpenGLDlg::OnMaterialGold()
{
	dmanager.setMaterial(nowID, 2);
}

void COpenGLDlg::OnMaterialWax()
{
	dmanager.setMaterial(nowID, 3);
}

void COpenGLDlg::OnMaterialSliver()
{
	dmanager.setMaterial(nowID, 4);
}

void COpenGLDlg::OnMaterialEmerald()
{
	dmanager.setMaterial(nowID, 5);
}

void COpenGLDlg::OnMaterialObsidian()
{
	dmanager.setMaterial(nowID, 6);
}

void COpenGLDlg::OnMaterialBlackplastic()
{
	dmanager.setMaterial(nowID, 7);
}

void COpenGLDlg::OnMaterialBlackrubber()
{
	dmanager.setMaterial(nowID, 8);
}

void COpenGLDlg::OnGameMaze()
{
	// TODO:  在此添加命令处理程序代码
	roam.enableMaze();
	spotlight.enable();
	MessageBox(_T("Start game! Press\nw/Ctrl+UP: go ahead\ns/Ctrl+DOWN: go back\na: move left\nd: move right\nmouse/Ctrl+LEFT: turn left\nmous/Ctrl+RIGHT: turn right\nx: return.\nTips: you can use Ctrl+-(or alter the 'display scale') to shrink the maze to find the correct path~"));
}
