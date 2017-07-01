#pragma once
#include "afxwin.h"


// CDebugger 对话框

class CDebugger : public CDialogEx
{
	DECLARE_DYNAMIC(CDebugger)

public:
	CDebugger(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDebugger();

	// 对话框数据
	enum { IDD = IDD_DEBUGGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()


private:
	//判断各个状态是否成功，主要后面界面优化字体颜色的时候用到
	bool isDeviceOpen;
	bool canGetCardInfo;
	bool canSetLED;
	bool canIO;
public:
	afx_msg void OnClickedButton11();//开启设备
	afx_msg void OnClickedButton21();//查看版本信息
	afx_msg void OnClickedButton22();//查看UID
	afx_msg void OnClickedButton31();//LED设置
	afx_msg void OnClickedButton41();//读扇区
	afx_msg void OnClickedButton42();//读块
	afx_msg void OnClickedButton43();//写块
	afx_msg void OnClickedButton51();//设置密钥
	afx_msg void OnClickedRadio51();//type_A
	afx_msg void OnClickedRadio52();//type_B
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//设置颜色
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
