#include "stdafx.h"
#include "LinActL12.h"
#include "LinActL12Dlg.h"
#include "PICConnector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinActL12Dlg dialog

CLinActL12Dlg::CLinActL12Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLinActL12Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinActL12Dlg)
	m_VersionInfo = _T("");
	RecvLength = 1;
	m_slidekiri = 0;
	m_slidekanan = 0;
	m_mmkir = 0.0f;
	m_mmkan = 0.0f;
	m_slideboth = 0;
	m_mmboth = 0.0f;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLinActL12Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinActL12Dlg)
	DDX_Control(pDX, IDC_SLIDER5, m_sliderboth);
	DDX_Control(pDX, IDC_SLIDER4, m_sliderkanan);
	DDX_Control(pDX, IDC_SLIDER3, m_sliderkiri);
	DDX_Text(pDX, IDC_EDIT1, m_slidekiri);
	DDX_Text(pDX, IDC_EDIT2, m_slidekanan);
	DDX_Text(pDX, IDC_EDIT3, m_mmkir);
	DDX_Text(pDX, IDC_EDIT4, m_mmkan);
	DDX_Text(pDX, IDC_EDIT5, m_slideboth);
	DDX_Text(pDX, IDC_EDIT6, m_mmboth);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLinActL12Dlg, CDialog)
	//{{AFX_MSG_MAP(CLinActL12Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, OnEXIT)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, OnSliderKiri)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, OnSliderKanan)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, OnBothslider)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinActL12Dlg message handlers

BOOL CLinActL12Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_sliderkiri.SetRange(0,1023,1); m_sliderkiri.SetPos(0);
	m_sliderkanan.SetRange(0,1023,1); m_sliderkanan.SetPos(0);
	m_sliderboth.SetRange(0,1023,1); m_sliderboth.SetPos(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLinActL12Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLinActL12Dlg::OnPaint() {
	if (IsIconic()){
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
	else{	CDialog::OnPaint();}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLinActL12Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLinActL12Dlg::OnEXIT() {	CDialog::OnOK();	}

void CLinActL12Dlg::OnSliderKiri(NMHDR* pNMHDR, LRESULT* pResult) {
	UpdateData(TRUE);
	m_slidekiri = m_sliderkiri.GetPos();
	float val1 = m_slidekiri+1;
	m_mmkir = (val1*30)/1024;
	UpdateData(FALSE);
	m_PICConnector.Open1();
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int value = m_slidekiri;
	if (value > 1023) value = 1023;
    if (value < 0) value = 0;
	#define SET_POSITION    0x20
    send_buf[0] = SET_POSITION;							// Command
    send_buf[1] = (unsigned char) value;				// Data Low
    send_buf[2] = (unsigned char) (value >> 8); 		// Data High
	m_PICConnector.SendReceivePacket(send_buf,3,receive_buf,&RecvLength,1000,1000);
	m_PICConnector.Close1();
	*pResult = 0;
}

void CLinActL12Dlg::OnSliderKanan(NMHDR* pNMHDR, LRESULT* pResult) {
	UpdateData(TRUE);
	m_slidekanan = m_sliderkanan.GetPos();
	float val2 = m_slidekanan+1;
	m_mmkan = (val2*30)/1024;
	UpdateData(FALSE);
	m_PICConnector.Open2();
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int value = m_slidekanan;
	if (value > 1023) value = 1023;
    if (value < 0) value = 0;
	#define SET_POSITION    0x20
    send_buf[0] = SET_POSITION;							// Command
    send_buf[1] = (unsigned char) value;				// Data Low
    send_buf[2] = (unsigned char) (value >> 8); 		// Data High
	m_PICConnector.SendReceivePacket(send_buf,3,receive_buf,&RecvLength,1000,1000);
	m_PICConnector.Close2();
	*pResult = 0;
}

void CLinActL12Dlg::OnBothslider(NMHDR* pNMHDR, LRESULT* pResult) {
	UpdateData(TRUE);
	m_slideboth = m_sliderboth.GetPos();
	float val3 = m_slideboth+1;
	m_mmboth = (val3*30)/1024;
	UpdateData(FALSE);
	m_PICConnector.Open3();
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int value = m_slideboth;
	if (value > 1023) value = 1023;
    if (value < 0) value = 0;
	#define SET_POSITION    0x20
    send_buf[0] = SET_POSITION;							// Command
    send_buf[1] = (unsigned char) value;				// Data Low
    send_buf[2] = (unsigned char) (value >> 8); 		// Data High
	m_PICConnector.SendReceivePacketBoth(send_buf,3,receive_buf,&RecvLength,1000,1000);
	m_PICConnector.Close3();
	*pResult = 0;
}
