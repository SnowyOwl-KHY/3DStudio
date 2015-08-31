// directlightDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OpenGL.h"
#include "directlightDlg.h"
#include "afxdialogex.h"


// directlightDlg 对话框

IMPLEMENT_DYNAMIC(directlightDlg, CDialog)

directlightDlg::directlightDlg(DirectLight& l, CWnd* pParent /*=NULL*/)
	: light(l), CDialog(directlightDlg::IDD, pParent)
{

}

directlightDlg::~directlightDlg()
{
}

void directlightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_X1, mEditX);
	DDX_Control(pDX, IDC_EDIT_Y1, mEditY);
	DDX_Control(pDX, IDC_EDIT_Z1, mEditZ);
	DDX_Control(pDX, IDC_EDIT_AR1, mEditAR);
	DDX_Control(pDX, IDC_EDIT_AG1, mEditAG);
	DDX_Control(pDX, IDC_EDIT_AB1, mEditAB);
	DDX_Control(pDX, IDC_EDIT_AA1, mEditAA);
	DDX_Control(pDX, IDC_EDIT_DR1, mEditDR);
	DDX_Control(pDX, IDC_EDIT_DG1, mEditDG);
	DDX_Control(pDX, IDC_EDIT_DB1, mEditDB);
	DDX_Control(pDX, IDC_EDIT_DA1, mEditDA);
	DDX_Control(pDX, IDC_EDIT_SR1, mEditSR);
	DDX_Control(pDX, IDC_EDIT_SG1, mEditSG);
	DDX_Control(pDX, IDC_EDIT_SB1, mEditSB);
	DDX_Control(pDX, IDC_EDIT_SA1, mEditSA);
	DDX_Control(pDX, IDC_EDIT_X2, mEditX2);
	DDX_Control(pDX, IDC_EDIT_Y2, mEditY2);
	DDX_Control(pDX, IDC_EDIT_Z2, mEditZ2);
	DDX_Control(pDX, IDC_EDIT_CUTOFF, mEditCutoff);
	DDX_Control(pDX, IDC_EDIT_EXPONENT, mEditExpo);
}


BEGIN_MESSAGE_MAP(directlightDlg, CDialog)
END_MESSAGE_MAP()


// directlightDlg 消息处理程序


BOOL directlightDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mEditX.SetWindowText(ftoa(light.position[0]));
	mEditY.SetWindowText(ftoa(light.position[1]));
	mEditZ.SetWindowText(ftoa(light.position[2]));

	mEditAR.SetWindowText(ftoa(light.ambient[0]));
	mEditAG.SetWindowText(ftoa(light.ambient[1]));
	mEditAB.SetWindowText(ftoa(light.ambient[2]));
	mEditAA.SetWindowText(ftoa(light.ambient[3]));

	mEditDR.SetWindowText(ftoa(light.diffuse[0]));
	mEditDG.SetWindowText(ftoa(light.diffuse[1]));
	mEditDB.SetWindowText(ftoa(light.diffuse[2]));
	mEditDA.SetWindowText(ftoa(light.diffuse[3]));

	mEditSR.SetWindowText(ftoa(light.specular[0]));
	mEditSG.SetWindowText(ftoa(light.specular[1]));
	mEditSB.SetWindowText(ftoa(light.specular[2]));
	mEditSA.SetWindowText(ftoa(light.specular[3]));

	mEditX2.SetWindowText(ftoa(light.direction[0]));
	mEditY2.SetWindowText(ftoa(light.direction[1]));
	mEditZ2.SetWindowText(ftoa(light.direction[2]));

	mEditCutoff.SetWindowText(ftoa(light.cutoff));
	mEditExpo.SetWindowText(ftoa(light.exponent));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void directlightDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData();
	CString s;
	mEditX.GetWindowText(s);
	light.position[0] = _ttof(s);
	mEditY.GetWindowText(s);
	light.position[1] = _ttof(s);
	mEditZ.GetWindowText(s);
	light.position[2] = _ttof(s);

	mEditAR.GetWindowText(s);
	light.ambient[0] = _ttof(s);
	mEditAG.GetWindowText(s);
	light.ambient[1] = _ttof(s);
	mEditAB.GetWindowText(s);
	light.ambient[2] = _ttof(s);
	mEditAA.GetWindowText(s);
	light.ambient[3] = _ttof(s);

	mEditDR.GetWindowText(s);
	light.diffuse[0] = _ttof(s);
	mEditDG.GetWindowText(s);
	light.diffuse[1] = _ttof(s);
	mEditDB.GetWindowText(s);
	light.diffuse[2] = _ttof(s);
	mEditDA.GetWindowText(s);
	light.diffuse[3] = _ttof(s);

	mEditSR.GetWindowText(s);
	light.specular[0] = _ttof(s);
	mEditSG.GetWindowText(s);
	light.specular[1] = _ttof(s);
	mEditSB.GetWindowText(s);
	light.specular[2] = _ttof(s);
	mEditSA.GetWindowText(s);
	light.specular[3] = _ttof(s);

	mEditX2.GetWindowText(s);
	light.direction[0] = _ttof(s);
	mEditY2.GetWindowText(s);
	light.direction[1] = _ttof(s);
	mEditZ2.GetWindowText(s);
	light.direction[2] = _ttof(s);

	mEditCutoff.GetWindowText(s);
	light.cutoff = _ttof(s);

	mEditExpo.GetWindowText(s);
	light.exponent = _ttof(s);
	CDialog::OnOK();
}
