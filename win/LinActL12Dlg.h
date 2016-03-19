// LinActL12Dlg.h : header file
//

#if !defined(AFX_LinActL12DLG_H__8E05920E_59EF_4B16_915E_820DF871CEDA__INCLUDED_)
#define AFX_LinActL12DLG_H__8E05920E_59EF_4B16_915E_820DF871CEDA__INCLUDED_

#include "PICConnector.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CLinActL12Dlg dialog

class CLinActL12Dlg : public CDialog
{
// Construction
public:
	BYTE	send_buf[64];
	BYTE	receive_buf[64];
	PICConnector m_PICConnector;
	CLinActL12Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLinActL12Dlg)
	enum { IDD = IDD_LinActL12_DIALOG };
	CSliderCtrl	m_sliderboth;
	CSliderCtrl	m_sliderkanan;
	CSliderCtrl	m_sliderkiri;
	CString	m_VersionInfo;
	BOOL	m_Led3;
	BOOL	m_Led4;
	DWORD	RecvLength;
	int		m_slidekiri;
	int		m_slidekanan;
	float	m_mmkir;
	float	m_mmkan;
	int		m_slideboth;
	float	m_mmboth;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinActL12Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// PIC Connector 
	

	// Generated message map functions
	//{{AFX_MSG(CLinActL12Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLed3();
	afx_msg void OnGetVersion();
	afx_msg void OnLed4();
	afx_msg void OnSendbtn();
	afx_msg void OnOpenbtn();
	afx_msg void OnClosebtn();
	afx_msg void OnEXIT();
	afx_msg void OnSliderKiri(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSliderKanan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBothslider(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LinActL12DLG_H__8E05920E_59EF_4B16_915E_820DF871CEDA__INCLUDED_)
