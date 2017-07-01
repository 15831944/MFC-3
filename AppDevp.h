#pragma once
#include "afxwin.h"
#define IDTIMER1  1 

#include <WinSock2.h>
#include "mysql.h"
#pragma comment(lib, "libmysql.lib")

// CAppDevp �Ի���

class CAppDevp : public CDialogEx
{
	DECLARE_DYNAMIC(CAppDevp)

public:
	CAppDevp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAppDevp();

	boolean ConnectSql();  //�������ݿ�
	CString Query(char *sql, int flag);  //��ѯ�������sqlΪ��ѯ��䣬flag:�������ݵ����ͣ������flag=1,�򷵻�UID, flag=2������ʱ
	boolean Insert(char *sql);  //��������
	boolean Delete(char* sql);  //ɾ�������
	boolean Update(char* sql);  //���±����


	void insertRecord(CString contents, char *ID);  //������ʷ��¼
	void queryRecord(char *ID);  //��ѯ����ʾ��ʷ��¼

	char* defaultRemainTime = "600";  //��ʼ��ʱ��Ĭ����ʱ�� ��

	// �Ի�������
	enum { IDD = IDD_AppDevp };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	afx_msg void OnClickedButton61();//����ʼ��
	afx_msg void OnClickedButton62();//��ȡ���
	afx_msg void OnClickedButton63();//Ȧ��
	afx_msg void OnClickedButton64();//����
	afx_msg void OnClickedButton71();//��ʼ�ϻ�
	afx_msg void OnClickedButton72();//�û��˳�
	afx_msg void OnClickedButton73();//��ʱĬ�ϳ�ʼ��
	afx_msg void OnClickedButton74();//��ѯ��ʱ
	afx_msg void OnClickedButton81();//��ռ�¼
	afx_msg void OnClickedButton82();//���ؼ�¼
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//������ɫ

private:
	bool m_EMoneyStatus;
	bool m_netStatus;
public:
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);  //��ʱ����Ӧ����
};
