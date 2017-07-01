#pragma once
#include "afxwin.h"


// CDebugger �Ի���

class CDebugger : public CDialogEx
{
	DECLARE_DYNAMIC(CDebugger)

public:
	CDebugger(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDebugger();

	// �Ի�������
	enum { IDD = IDD_DEBUGGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()


private:
	//�жϸ���״̬�Ƿ�ɹ�����Ҫ��������Ż�������ɫ��ʱ���õ�
	bool isDeviceOpen;
	bool canGetCardInfo;
	bool canSetLED;
	bool canIO;
public:
	afx_msg void OnClickedButton11();//�����豸
	afx_msg void OnClickedButton21();//�鿴�汾��Ϣ
	afx_msg void OnClickedButton22();//�鿴UID
	afx_msg void OnClickedButton31();//LED����
	afx_msg void OnClickedButton41();//������
	afx_msg void OnClickedButton42();//����
	afx_msg void OnClickedButton43();//д��
	afx_msg void OnClickedButton51();//������Կ
	afx_msg void OnClickedRadio51();//type_A
	afx_msg void OnClickedRadio52();//type_B
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//������ɫ
	CEdit m_DebuggerEdit11;
	CEdit m_DebuggerEdit21;
	CEdit m_DebuggerEdit22;
	CEdit m_DebuggerEdit23;
	CEdit m_DebuggerEdit31;
	CEdit m_DebuggerEdit32;
	CEdit m_DebuggerEdit33;
	CEdit m_DebuggerEdit41;
	CEdit m_DebuggerEdit42;
	CEdit m_DebuggerEdit43;
	CEdit m_DebuggerEdit44;
	CEdit m_DebuggerEdit45;
	CEdit m_DebuggerEdit46;
	CEdit m_DebuggerEdit47;
	CEdit m_DebuggerEdit51;
	CComboBox m_DebuggerCombo41;
	CComboBox m_DebuggerCombo42;
	int m_DebuggerRadio51;
	unsigned char m_RadioStatus;
	
	static void CStringToChar(const CString& s, char* ch, int len);
	static void HexStr2CharArray(const CString& hexStr, unsigned char* asc, int* asc_len);
};
