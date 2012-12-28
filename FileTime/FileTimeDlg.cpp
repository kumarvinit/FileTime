
// FileTimeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileTime.h"
#include "FileTimeDlg.h"
#include "afxdialogex.h"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <share.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileTimeDlg �Ի���




CFileTimeDlg::CFileTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileTimeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE, _edtFile);
	DDX_Control(pDX, IDC_EDIT_ORIGIN, _edtOrigin);
	DDX_Control(pDX, IDC_EDIT_NEW, _edtNew);
}

BEGIN_MESSAGE_MAP(CFileTimeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CFileTimeDlg::OnBnClickedButtonBrowse)
	ON_EN_CHANGE(IDC_EDIT_FILE, &CFileTimeDlg::OnEnChangeEditFile)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CFileTimeDlg::OnBnClickedButtonModify)
END_MESSAGE_MAP()


// CFileTimeDlg ��Ϣ�������

BOOL CFileTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFileTimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFileTimeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFileTimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileTimeDlg::OnBnClickedButtonBrowse()
{
	CString init_dir;
	_edtFile.GetWindowText(init_dir);

	wchar_t path[MAX_PATH];
	//BOOL bRet = GetFileNameFromBrowse(GetSafeHwnd(), sPath, MAX_PATH, init_dir, L"rvp", L"rvp file(*.rvp)\0*.rvp\0*.*\0*.*\0\0", sTitle);
	BOOL bRet = GetFileNameFromBrowse(GetSafeHwnd(), path, MAX_PATH, init_dir, L"", L"*.*\0*.*\0\0", L"Select file...");
	if(bRet)	{
		_edtFile.SetWindowText(path);
	}
}


void CFileTimeDlg::OnEnChangeEditFile()
{
	CString fn;
	_edtFile.GetWindowText(fn);

	CString mts;
	if (_taccess(fn, 0) == 0)		//�ж��ļ��Ƿ����
	{
		int fd = _tsopen(fn, _O_RDONLY, _SH_DENYNO, _S_IREAD);
		if(fd != -1)
		{
			struct _stat st;
			_fstat(fd, &st);
			_close(fd);

			tm t;
			localtime_s(&t, &st.st_mtime);

			mts.Format(_T("%d-%d-%d %d:%d:%d"), t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
		}		
	}
	_edtOrigin.SetWindowText(mts);
}


void CFileTimeDlg::OnBnClickedButtonModify()
{
	CString fn;
	_edtFile.GetWindowText(fn);

	OFSTRUCT ofs;
	memset(&ofs, 0, sizeof(ofs));
	ofs.cBytes = sizeof(ofs);
	//HANDLE h_file = (HANDLE)OpenFile((LPCSTR)(LPCTSTR)fn, &ofs, OF_EXIST|OF_READWRITE);
	HANDLE h_file = CreateFile(fn, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if (h_file == INVALID_HANDLE_VALUE)
		return;
	
	CString mts_new;
	_edtNew.GetWindowText(mts_new);

	struct tm tmfile;
	memset(&tmfile, 0, sizeof(tmfile));
	
	_stscanf(mts_new, _T("%d-%d-%d %d:%d:%d"), &tmfile.tm_year, &tmfile.tm_mon, &tmfile.tm_mday, &tmfile.tm_hour, &tmfile.tm_min, &tmfile.tm_sec);
	tmfile.tm_year -= 1900;
	tmfile.tm_mon -= 1;
	time_t mt = _mkgmtime(&tmfile);
	mt += timezone;
	
	
	FILETIME ftCreTime, ftAccTime, ftWriTime;
	if (GetFileTime(h_file, &ftCreTime,&ftAccTime,&ftWriTime))
	{
		LONGLONG ll = Int32x32To64(mt, 10000000) + 116444736000000000;
		ftWriTime.dwLowDateTime = (DWORD) ll;
		ftWriTime.dwHighDateTime = (DWORD)(ll >> 32);
		SetFileTime(h_file, &ftCreTime, &ftAccTime, &ftWriTime);
	}
	CloseHandle(h_file);	
}
