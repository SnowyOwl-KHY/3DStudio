// EditListCtrl.cpp : implementation file

#include "stdafx.h"
#include "OpenGL.h"
#include "EditListCtrl.h"

#define STATICCOL 0//不可修改的列号
/////////////////////////////////////////////////////////
// CEditListCtrl

IMPLEMENT_DYNAMIC(CEditListCtrl, CListCtrl)



CEditListCtrl::CEditListCtrl()
{
	change = false;
	changeEnd = false;
	isData = 0;
}

CEditListCtrl::~CEditListCtrl()
{
}

BEGIN_MESSAGE_MAP(CEditListCtrl, CListCtrl)
	ON_MESSAGE(WM_USER_EDIT_END,OnEditEnd)
	//ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CEditListCtrl message handlers
void CEditListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rcCtrl;
	LVHITTESTINFO lvhti;
	lvhti.pt = point;
	nItem = CListCtrl::SubItemHitTest(&lvhti);//行号
	if (nItem == -1) 
		return;
	nSubItem = lvhti.iSubItem;//列号
	if (nSubItem != STATICCOL){//第STATICCOL列的元素不可编辑
		CListCtrl::GetSubItemRect(nItem,nSubItem,LVIR_LABEL,rcCtrl);
		ShowEdit(TRUE,nItem,nSubItem,rcCtrl);
	}
	CListCtrl::OnLButtonDblClk(nFlags, point);
}

void CEditListCtrl::ShowEdit(bool bShow, int nItem, int nSubItem, CRect rcCtrl)
{
  if (m_Edit.m_hWnd == NULL)
  {
	  m_Edit.Create(ES_AUTOHSCROLL|WS_CHILD|ES_LEFT|ES_WANTRETURN|WS_BORDER,CRect(0,0,0,0),this,IDC_EDIT2);//
      m_Edit.ShowWindow(SW_HIDE);
 
      CFont tpFont;
      tpFont.CreateStockObject(DEFAULT_GUI_FONT);
      m_Edit.SetFont(&tpFont);
      tpFont.DeleteObject();
  }
  if (bShow == TRUE)
  {
      CString strItem = CListCtrl::GetItemText(nItem,nSubItem);
     m_Edit.MoveWindow(&rcCtrl);
     m_Edit.ShowWindow(SW_SHOW);
     m_Edit.SetWindowText(strItem);//编辑单元格内容
	
     m_Edit.SetFocus();
     m_Edit.SetSel(-1); 
  }
  else
      m_Edit.ShowWindow(SW_HIDE);
}

LRESULT CEditListCtrl::OnEditEnd(WPARAM wParam, LPARAM lParam)
{
	if (change){//只有回车了才能修改表格数据
		CString strText;
		m_Edit.GetWindowText(strText);

		if (isData == 1)
			strText = itoa(_ttoi(strText));
		else if (isData == 2)
			strText = ftoa(_ttof(strText));
		
		CListCtrl::SetItemText(nItem, nSubItem, strText);
		change = false;
		newData = strText;//在这里获得最新编辑了的值！！！！！！！！！！！！
		
		//AfxMessageBox(newData);
	}
	m_Edit.ShowWindow(SW_HIDE);
	changeEnd = true;
	
	return 0;
}



/////////////////////////////////////////////////////////
//CListCtrlEdit
IMPLEMENT_DYNAMIC(CListCtrlEdit, CEdit)

CListCtrlEdit::CListCtrlEdit()
{

}

CListCtrlEdit::~CListCtrlEdit()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEdit, CEdit)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


void CListCtrlEdit::OnKillFocus(CWnd* pNewWnd)
{
	//CListCtrl::OnKillFocus(pNewWnd);
     CEdit::OnKillFocus(pNewWnd);
 
     // 发送消息
	CWnd* pParent = this->GetParent();
	::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_END,0,0);
	
	// TODO: Add your message handler code here
}



