#pragma once
#include "afxwin.h"


// directlightDlg 对话框

class directlightDlg : public CDialog
{
	DECLARE_DYNAMIC(directlightDlg)
	DirectLight &light;
public:
	directlightDlg(DirectLight& l, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~directlightDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DIRECTLIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mEditX;
	CEdit mEditY;
	CEdit mEditZ;
	CEdit mEditAR;
	CEdit mEditAG;
	CEdit mEditAB;
	CEdit mEditAA;
	CEdit mEditDR;
	CEdit mEditDG;
	CEdit mEditDB;
	CEdit mEditDA;
	CEdit mEditSR;
	CEdit mEditSG;
	CEdit mEditSB;
	CEdit mEditSA;
	CEdit mEditX2;
	CEdit mEditY2;
	CEdit mEditZ2;
	CEdit mEditCutoff;
	CEdit mEditExpo;
	virtual void OnOK();
};
