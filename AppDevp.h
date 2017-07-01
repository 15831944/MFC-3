#pragma once
#include "afxwin.h"
#define IDTIMER1  1 

#include <WinSock2.h>
#include "mysql.h"
#pragma comment(lib, "libmysql.lib")

// CAppDevp 对话框

class CAppDevp : public CDialogEx
{
	DECLARE_DYNAMIC(CAppDevp)

public:
	CAppDevp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAppDevp();

	boolean ConnectSql();  //连接数据库
	CString Query(char *sql, int flag);  //查询表操作，sql为查询语句，flag:返回数据的类型，如果是flag=1,则返回UID, flag=2返回余时
	boolean Insert(char *sql);  //插入表操作
	boolean Delete(char* sql);  //删除表操作
	boolean Update(char* sql);  //更新表操作


	void insertRecord(CString contents, char *ID);  //插入历史记录
	void queryRecord(char *ID);  //查询并显示历史记录

	char* defaultRemainTime = "600";  //初始余时，默认余时， 秒

	// 对话框数据
	enum { IDD = IDD_AppDevp };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CString GetCardUID();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_AppDevpEdit61;
	CEdit m_AppDevpEdit62;
	CEdit m_AppDevpEdit63;
	CEdit m_AppDevpEdit64;
	CEdit m_AppDevpEdit71;
	CEdit m_AppDevpEdit72;
	CEdit m_AppDevpEdit73;
	CEdit m_AppDevpEdit74;
	CEdit m_AppDevpEdit81;
	afx_msg void OnClickedButton61();//余额初始化
	afx_msg void OnClickedButton62();//读取余额
	afx_msg void OnClickedButton63();//圈存
	afx_msg void OnClickedButton64();//消费
	afx_msg void OnClickedButton71();//开始上机
	afx_msg void OnClickedButton72();//用户退出
	afx_msg void OnClickedButton73();//余时默认初始化
	afx_msg void OnClickedButton74();//查询余时
	afx_msg void OnClickedButton81();//清空记录
	afx_msg void OnClickedButton82();//加载记录
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//设置颜色

private:
	bool m_EMoneyStatus;
	bool m_netStatus;
public:
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);  //定时器相应函数
};
