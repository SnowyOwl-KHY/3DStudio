// spotlightDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OpenGL.h"
#include "spotlightDlg.h"
#include "afxdialogex.h"


// spotlightDlg 对话框

IMPLEMENT_DYNAMIC(spotlightDlg, CDialog)

spotlightDlg::spotlightDlg(SpotLight& l, CWnd* pParent /*=NULL*/)
: light(l), CDialog(spotlightDlg::IDD, pParent)
{

}

spotlightDlg::~spotlightDlg()
{
}

void spotlightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_X, mEditX);
	DDX_Control(pDX, IDC_EDIT_Y, mEditY);
	DDX_Control(pDX, IDC_EDIT_Z, mEditZ);
	DDX_Control(pDX, IDC_EDIT_AR, mEditAR);
	DDX_Control(pDX, IDC_EDIT_AG, mEditAG);
	DDX_Control(pDX, IDC_EDIT_AB, mEditAB);
	DDX_Control(pDX, IDC_EDIT_AA, mEditAA);
	DDX_Control(pDX, IDC_EDIT_DR, mEditDR);
	DDX_Control(pDX, IDC_EDIT_DG, mEditDG);
	DDX_Control(pDX, IDC_EDIT_DB, mEditDB);
	DDX_Control(pDX, IDC_EDIT_DA, mEditDA);
	DDX_Control(pDX, IDC_EDIT_SR, mEditSR);
	DDX_Control(pDX, IDC_EDIT_SG, mEditSG);
	DDX_Control(pDX, IDC_EDIT_SB, mEditSB);
	DDX_Control(pDX, IDC_EDIT_SA, mEditSA);
}


BEGIN_MESSAGE_MAP(spotlightDlg, CDialog)
	ON_BN_CLICKED(IDOK, &spotlightDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// spotlightDlg 消息处理程序


BOOL spotlightDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void spotlightDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
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

	CDialog::OnOK();
}
