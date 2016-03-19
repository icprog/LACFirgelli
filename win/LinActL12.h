// LinActL12.h : main header file for the LinActL12 application
//

#if !defined(AFX_LinActL12_H__5EB4976E_FF97_4412_8122_12BE74E33040__INCLUDED_)
#define AFX_LinActL12_H__5EB4976E_FF97_4412_8122_12BE74E33040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLinActL12App:
// See LinActL12.cpp for the implementation of this class
//

class CLinActL12App : public CWinApp
{
public:
	CLinActL12App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinActL12App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLinActL12App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LinActL12_H__5EB4976E_FF97_4412_8122_12BE74E33040__INCLUDED_)
