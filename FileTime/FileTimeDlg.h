
// FileTimeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CFileTimeDlg �Ի���
class CFileTimeDlg : public CDialogEx
{
// ����
public:
	CFileTimeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FILETIME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBrowse();
	CEdit _edtFile;
	CEdit _edtOrigin;
	CEdit _edtNew;
	afx_msg void OnEnChangeEditFile();
	afx_msg void OnBnClickedButtonModify();
};
