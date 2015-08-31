#pragma once

#define WM_USER_EDIT_END WM_USER +21

//edit of list
class CListCtrlEdit : public CEdit
{
     DECLARE_DYNAMIC(CListCtrlEdit)
	 
public:
     CListCtrlEdit();
     virtual ~CListCtrlEdit();
 
protected:
     DECLARE_MESSAGE_MAP()
public:
     afx_msg void OnKillFocus(CWnd* pNewWnd);
};

// list
class CEditListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CEditListCtrl)
	CString newData;
	bool change;
	bool changeEnd;
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg LRESULT OnEditEnd(WPARAM wParam,LPARAM lParam);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void ShowEdit(bool bShow, int nItem, int nSubItem, CRect rcCtrl);

public:
	int nItem;
	int nSubItem;
	int isData;
	CListCtrlEdit  m_Edit;

	CEditListCtrl();
	virtual ~CEditListCtrl();

	void setChange(bool c){
		change = c;
		changeEnd = false;
	}

	CString getNewData(){
		return newData;
	}

	bool getChangeEnd(){
		return changeEnd;
	}

	void setChangeEnd(bool c){
		changeEnd = c;
	}

};

