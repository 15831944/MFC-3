// AppDevp.cpp : ʵ���ļ�
//
#pragma once

#include "stdafx.h"
#include "MFCApplication1.h"
#include "AppDevp.h"
#include "afxdialogex.h"
#include <afx.h>
#include <WinSock2.h>
#include "mysql.h"
#include "CRecordHelper.h"
#pragma comment(lib, "libmysql.lib")

#pragma comment(lib,"libs/ZM124U.h")
#include "libs/ZM124U.h"
#define RED RGB(255, 0, 0)
#define BLUE RGB(0, 0, 255)
#define BLACK RGB(0, 0, 0)
CString returnValueMean(int value) {
	CString state;
	switch (value) {
	case 0: state = "�ɹ�"; break;
	case -1: state = "��Ƭ���Ͳ���"; break;
	case -2: state = "�޿�"; break;
	case -3: state = "�п�δ�ϵ�"; break;
	case -4: state = "��Ƭ��Ӧ��"; break;
	case -5: state = "BCCУ�����"; break;
	case -6: state = "���ճ�ʱ"; break;
	case -7: state = "ִ��ʧ��"; break;
	case -8: state = "��Ƭλ�ô���"; break;
	case -9: state = "����ʧ��"; break;
	case -11: state = "���������Ӵ���"; break;
	case -12: state = "δ�������ӣ�û��ִ�д��豸������"; break;
	case -13: state = "����̬�⣩��֧�ָ�����"; break;
	case -14: state = "��������̬��ģ������������"; break;
	case -15: state = "��ϢУ��ͳ���"; break;
	case -16: state = "��Ƭ�ϵ�ʧ��"; break;
	case -17: state = "��Ƭ��λʧ��"; break;
	case -18: state = "��Ƭ�µ�ʧ��"; break;
	default: state = ""; break;
	}
	return state;
}

void CString2CharStar(const CString& s, char* ch, int len) {
	int i;
	for (i = 0; i < len; i++) {
		ch[i] = s[i];
	}
	ch[i] = '\0';
	return;
}
//��Կ����ת��
void HexCString2UnsignedCharStar(const CString& hexStr, unsigned char* asc, int* asc_len) {
	*asc_len = 0;
	int len = hexStr.GetLength();

	char temp[200];
	char tmp[3] = { 0 };
	char* Hex;
	unsigned char* p;

	CString2CharStar(hexStr, temp, len);
	Hex = temp;
	p = asc;

	while (*Hex != '\0') {
		tmp[0] = *Hex;
		Hex++;
		tmp[1] = *Hex;
		Hex++;
		tmp[2] = '\0';
		*p = (unsigned char)strtol(tmp, NULL, 16);
		//	TRACE("\n %s  ",tmp); //���ʧ��
		p++;
		(*asc_len)++;
	}
	*p = '\0';
	return;
}
// CAppDevp �Ի���

IMPLEMENT_DYNAMIC(CAppDevp, CDialogEx)

CAppDevp::CAppDevp(CWnd* pParent /*=NULL*/)
: CDialogEx(CAppDevp::IDD, pParent)
{
	SetTimer(IDTIMER1, 1000, NULL);   //������ʱ��
}

CAppDevp::~CAppDevp()
{
	KillTimer(IDTIMER1);  //�رն�ʱ��
}

void CAppDevp::DoDataExchange(CDataExchange* pDX)
{
	//SetTimer(IDTIMER1, 1000, NULL);   //������ʱ��

	ConnectSql();  //�������ݿ�
	
	//��ȡ��ƬID
	//CString UID = GetCardUID();
	//char _UID[20] = { '\0' };
	//WideCharToMultiByte(CP_OEMCP, NULL, UID, -1, _UID, 20, NULL, FALSE); //��CString תΪchar *
	char *_UID = "3058d70e";

	//�����ѯ��ʱ�û������
	char sql_query1[255];
	char * sql1 = "select * from RemainTimeTable where UID = '";
	strcpy_s(sql_query1, sql1);
	strcat_s(sql_query1, _UID);
	strcat_s(sql_query1, "'");

	CString query1 = Query(sql_query1, 0);   //��ѯ�û��ϻ������Ƿ��Ѵ��ڸ��û�
	if (query1 == _T(""))
	{
		//���������û������
		char sql_insert1[255];
		char * sql3 = "insert into RemainTimeTable(UID, RemainTime) values('";
		strcpy_s(sql_insert1, sql3);
		strcat_s(sql_insert1, _UID);
		strcat_s(sql_insert1, "', '");
		strcat_s(sql_insert1, defaultRemainTime);
		strcat_s(sql_insert1, "')");
		boolean flag = Insert(sql_insert1);   //�����û����ݲ����û�����
	}

	//char *_UID = "12678";

	

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT61, m_AppDevpEdit61);
	DDX_Control(pDX, IDC_EDIT62, m_AppDevpEdit62);
	DDX_Control(pDX, IDC_EDIT63, m_AppDevpEdit63);
	DDX_Control(pDX, IDC_EDIT64, m_AppDevpEdit64);
	DDX_Control(pDX, IDC_EDIT71, m_AppDevpEdit71);
	DDX_Control(pDX, IDC_EDIT72, m_AppDevpEdit72);
	DDX_Control(pDX, IDC_EDIT73, m_AppDevpEdit73);
	DDX_Control(pDX, IDC_EDIT74, m_AppDevpEdit74);
	DDX_Control(pDX, IDC_EDIT81, m_AppDevpEdit81);


}


BEGIN_MESSAGE_MAP(CAppDevp, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON61, &CAppDevp::OnClickedButton61)
	ON_BN_CLICKED(IDC_BUTTON62, &CAppDevp::OnClickedButton62)
	ON_BN_CLICKED(IDC_BUTTON63, &CAppDevp::OnClickedButton63)
	ON_BN_CLICKED(IDC_BUTTON64, &CAppDevp::OnClickedButton64)
	ON_BN_CLICKED(IDC_BUTTON71, &CAppDevp::OnClickedButton71)
	ON_BN_CLICKED(IDC_BUTTON72, &CAppDevp::OnClickedButton72)
	ON_BN_CLICKED(IDC_BUTTON73, &CAppDevp::OnClickedButton73)
	ON_BN_CLICKED(IDC_BUTTON74, &CAppDevp::OnClickedButton74)
	ON_BN_CLICKED(IDC_BUTTON81, &CAppDevp::OnClickedButton81)
	ON_BN_CLICKED(IDC_BUTTON82, &CAppDevp::OnClickedButton82)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()

//��ȡUID
CString CAppDevp::GetCardUID() {
	CString uid, temp;
	unsigned char buffer[1024];
	int bufferLength;
	//�ɹ���ȡ
	int flag = find_14443(buffer, &bufferLength);
	if (flag == IFD_OK) {
		uid.Empty();
		for (int i = 0; i < bufferLength; i++) {
			//����õ�UID����ת��Ϊ16����
			temp.Format(_T("%02x"), buffer[i]);
			uid += temp;
		}
		return uid;
	}
	else {
		CString str = returnValueMean(flag);
		return str;
	}
}

// CAppDevp ��Ϣ�������

//Ǯ����ʼ�����û������༭���������CString���ͣ�Ҫת��Ϊlong���ͱ��棬
void CAppDevp::OnClickedButton61()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����ʾ����Ϊ��
	((CEdit*)GetDlgItem(IDC_EDIT62))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT63))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T(""));

	CString remainings;// = _T("12");
	((CEdit*)GetDlgItem(IDC_EDIT61))->GetWindowText(remainings);//�����ı༭���ȡֵCString
	TRACE(L"\n\n�����ʼ�������%s\n", remainings);//\r\n���

	if (remainings.IsEmpty()) {
		this->m_EMoneyStatus = false;//��һ������������ʲô    ???????????????????
		//((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("��������ȷ��"));
		MessageBox(_T("��������ȷ�ĳ�ʼ����"));
		return;
	}
	long account = _ttol(remainings);//CStringתΪlong��
	if (account < 0) {
		this->m_EMoneyStatus = false;//��һ������������ʲô    ???????????????????
		MessageBox(_T("��Ǯ����С��0����������ȷ�ĳ�ʼ����"));
		return;
	}

	int sectionNum = 15;
	int blockNum = 0;
	unsigned char pswtype = 0x0A;
	unsigned char psw[8];
	unsigned char exaplme[8];
	exaplme[0] = 1;
	exaplme[1] = 0xF;
	int len_chpwd = 0;
	CString pwd = _T("FFFFFFFFFFFF");
	//��Կ����ת��
	HexCString2UnsignedCharStar(pwd, psw, &len_chpwd);
	//����鿴����ת���Ƿ���ȷ
	TRACE(" \n %s", psw);
	TRACE(" \n\n ����ת��������\n\n");
	//int write_account(int page, int block, unsigned char pswtype, unsigned char *psw, LONG account);
	int flag = write_account(sectionNum, blockNum, pswtype, psw, account);//�����д�����Ǯ��
	//TRACE(L"\n\nflag%d\n", flag);//\r\n���												//�ж�д���Ƿ�ɹ�
	CString str = returnValueMean(flag);
	if (flag == 0) {
		this->m_EMoneyStatus = true;
	}
	else{
		this->m_EMoneyStatus = false;
	}
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(str);
	
}

// ��ѯ������
void CAppDevp::OnClickedButton62()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����ʾ����Ϊ��
	((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT62))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT63))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T(""));

	unsigned char pswtype = 0x0A;
	unsigned char psw[8];
	int len_chpwd = 0;
	CString pwd = _T("FFFFFFFFFFFF");
	//��Կ����ת��
	HexCString2UnsignedCharStar(pwd, psw, &len_chpwd);
	long account;
	int flag = read_account(int(15), int(0), pswtype, psw, &account);//��ȡ����Ǯ�����
	CString strState = returnValueMean(flag);
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(strState);//״̬����ʾ��ѯ״̬
	if (flag == 0) {
		this->m_EMoneyStatus = true;
		CString str;
		str.Format(_T("%ld"), account);//long��תΪCString
		((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(str);//��ѯ���������ʾ������
		return;
	}
	this->m_EMoneyStatus = false;
}

//��ֵ
void CAppDevp::OnClickedButton63()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����ʾ����Ϊ��
	((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT63))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T(""));

	//��ȡ��ֵ����Ϊ����return
	CString recharge;
	((CEdit*)GetDlgItem(IDC_EDIT62))->GetWindowText(recharge);//�����ı༭���ȡֵCString
	long rechargeLong = _ttol(recharge);//CString--->long
	if (recharge.IsEmpty()) {
		//((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("��������ȷ��ֵ��"));
		MessageBox(_T("��������ȷ��ֵ��"));
		return;
	}
	if (rechargeLong < 0) {
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("��ֵʧ�ܣ�����Ϊ����"));
		return;
	}
	//��ȡ��Ƭ���
	long account;
	unsigned char pswtype = 0x0A;
	unsigned char psw[8];
	int len_chpwd = 0;
	CString pwd = _T("FFFFFFFFFFFF");
	//��Կ����ת��
	HexCString2UnsignedCharStar(pwd, psw, &len_chpwd);
	int flag1 = read_account(int(15), int(0), pswtype, psw, &account); // ��ȡ����Ǯ�����	
	
	CString strRead = returnValueMean(flag1);
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(strRead);
	if (flag1 < 0) {
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("�����ֵ������ȡʧ�ܣ�"));
		return;
	}

	
	long accountSum = rechargeLong + account;
	int flag = write_account(int(15), int(0), pswtype, psw, accountSum);//�����д�����Ǯ��
	//�ж��Ƿ�д��ɹ�
	CString str = returnValueMean(flag);
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(str);

	CString Filename = _T("C://record.txt");
	CRecordHelper helper(Filename);
	CString vid = GetCardUID();
	CString con = _T("��ֵ");
	CString result;
	//��ʾ��ֵ������
	if (flag == 0) {//��ֵ�ɹ�
		this->m_EMoneyStatus = true;
		CString remainingAfterRE;
		remainingAfterRE.Format(_T("%ld"), accountSum);//long----->CString
		((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(remainingAfterRE);
		//�����ֵ�ɹ���¼���ļ�
		result = "successful";
		//saveRecharges(CString vid, CString account, long Remainings, CString con, CString result);
		helper.saveRecharges(vid, recharge, accountSum, con, result);
	}
	else {//��ֵʧ��,����
		this->m_EMoneyStatus = false;
		CString remainingAfterRE;
		remainingAfterRE.Format(_T("%ld"), account);//long----->CString
		((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(remainingAfterRE);
		result = "failed";
		helper.saveRecharges(vid, recharge, account, con, result);
	}
	
}

//���Ѻ���
void CAppDevp::OnClickedButton64()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����ʾ����Ϊ��
	((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT62))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T(""));

	//�����ѵı༭���ȡֵCString
	CString consumption;
	((CEdit*)GetDlgItem(IDC_EDIT63))->GetWindowText(consumption);
	if (consumption.IsEmpty()) {
		//((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("��������ȷ���ѽ�"));
		MessageBox(_T("��������ȷ���ѽ�"));
		return;
	}
	//��ȡ���
	long account;
	unsigned char pswtype = 0x0A;//��Կ����
	unsigned char psw[8];
	int len_chpwd = 0;
	CString pwd = _T("FFFFFFFFFFFF");
	//��Կ����ת��
	HexCString2UnsignedCharStar(pwd, psw, &len_chpwd);

	int flag = read_account(int(15), int(0), pswtype, psw, &account);// ��ȡ����Ǯ�����	
	CString remainingBeforeConsum;
	remainingBeforeConsum.Format(_T("%ld"), account);//long----->CString
	CString strRead = returnValueMean(flag);
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(strRead);
	//ָ���ļ������¼
	CString Filename = _T("C://record.txt");
	CRecordHelper helper(Filename);
	CString vid = GetCardUID();
	CString con = _T("����");
	CString result;

	if (flag < 0) {//��ȡ���ʧ��ֱ�ӽ�������
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("�������ѣ�����ȡʧ�ܣ�"));
		this->m_EMoneyStatus = false;
		return;
	}
	//�������ѵļ���
	long consumptionLong = _ttol(consumption);//CString -----> long
	if (consumptionLong < 0) {
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("����ʧ�ܣ�����Ϊ����"));
		MessageBox(_T("���ѽ���Ϊ������������ȷ���ѽ�"));
		this->m_EMoneyStatus = false;
	}
	else if (consumptionLong > account) {
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("����ʧ�ܣ����㣡"));
		MessageBox(_T("���㣡"));
		((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(remainingBeforeConsum);
		this->m_EMoneyStatus = false;

	}
	else {
		long remain = account - consumptionLong;
		int flag = write_account(int(15), int(0), pswtype, psw, remain);//�����д�����Ǯ��
		//�ж��Ƿ�д��ɹ�
		CString str = returnValueMean(flag);
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(str);
		//��ʾ���Ѻ�����
		CString remainingAfterConsum;
		remainingAfterConsum.Format(_T("%ld"), remain);//long----->CString
		((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(remainingAfterConsum);
		this->m_EMoneyStatus = true;

		result = _T("successful");
		helper.saveConsumptions(vid, consumption, remain, con, result);

		return;
	}

	result = _T("failed");
	helper.saveConsumptions(vid, consumption, account, con, result);
	//this->m_EMoneyStatus = false;
}


MYSQL mysql;

// �������ݿ�
boolean CAppDevp::ConnectSql()
{
	mysql_init(&mysql);  //��ʼ��
	mysql_query(&mysql, "Set names GBK");

	char *URL = "localhost";
	char *username = "root";
	char *password = "1234567890";
	char *DBname = "NetManage";

	//�������ݿ�
	if (mysql_real_connect(&mysql, "localhost", "root", "1234567890", "NetManage", 3306, NULL, 0)){
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("���ݿ����ӳɹ�"));
		return true;
	}
	else{
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("���ݿ�����ʧ��"));
		return false;
	}

}

//��ѯ������ flag ��ʾ���ز�ѯ����еĵڼ�������
CString CAppDevp::Query(char *sql, int flag)
{
	mysql_query(&mysql, "Set names GBK");

	MYSQL_RES *result;
	MYSQL_ROW row;
	mysql_query(&mysql, sql);  //��ѯ
	result = mysql_store_result(&mysql);  //��ѯ���
	row = mysql_fetch_row(result);   //һ�в�ѯ���
	if (row != NULL){
		char k[20];
		strcpy_s(k, row[flag]);  //�õ����ݣ� ����k��
		CString str1(k);
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("��ѯ�ɹ�"));

		return (str1);

	}
	else{

		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("��ѯʧ��") + CString(mysql_error(&mysql)));
		return _T("");
	}

}

//�������
boolean CAppDevp::Insert(char *sql_insert)
{
	mysql_query(&mysql, "Set names GBK");

	if (!mysql_query(&mysql, (char*)(sql_insert)))  //����
	{
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("����ɹ�"));
		return true;
	}
	else{
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("����ʧ��") + CString(mysql_error(&mysql)));
		return false;
	}
}

//���²���
boolean CAppDevp::Update(char* sql)
{
	mysql_query(&mysql, "Set names GBK");

	if (!mysql_query(&mysql, sql))  //����
	{
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("���³ɹ�"));
		return true;
	}
	else{
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("����ʧ��") + CString(mysql_error(&mysql)));
		return false;
	}
}

//ɾ������
boolean CAppDevp::Delete(char* sql_del)
{
	mysql_query(&mysql, "Set names GBK");

	if (!mysql_query(&mysql, sql_del))  //ɾ��
	{
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("ɾ���ɹ�"));
		return true;
	}
	else{

		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("ɾ��ʧ��") + CString(mysql_error(&mysql)));
		return false;
	}
}

//��������¼�������ݿ���
void CAppDevp::insertRecord(CString contents, char* ID)
{
	char recor[100] = { '\0' };
	WideCharToMultiByte(CP_OEMCP, NULL, contents, -1, recor, 100, NULL, FALSE);
	TRACE(recor);

	//�����������
	char sql_insertk[200];
	char *sql3 = "insert into Record values('";
	strcpy_s(sql_insertk, sql3);
	strcat_s(sql_insertk, ID);
	strcat_s(sql_insertk, "', '");
	strcat_s(sql_insertk, recor);
	strcat_s(sql_insertk, "')");
	boolean f = Insert(sql_insertk);  //����
	//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("����") +CString(mysql_error(&mysql)));
}

// ��ѯ������¼����ʾ����
void CAppDevp::queryRecord(char *ID)
{
	char record[500000] = { '\0' };

	MYSQL_RES *result_;
	MYSQL_ROW row;
	char sql_query[200];
	char *queryk = "select * from Record where ID = '";
	strcpy_s(sql_query, queryk);
	strcat_s(sql_query, ID);
	strcat_s(sql_query, "'");
	mysql_query(&mysql, sql_query);  //��ѯ
	result_ = mysql_store_result(&mysql);  //��ѯ���
	while (row = mysql_fetch_row(result_)){
		//row = mysql_fetch_row(result_);
		if (row != NULL){
			strcat_s(record, row[1]);
		}
	}

	((CEdit*)GetDlgItem(IDC_EDIT81))->SetWindowText(CStringW(CString(record)));  //��ʾ
}



//��ʼ�ϻ�
void CAppDevp::OnClickedButton71()
{
	ConnectSql();  //�������ݿ�
	

	char *_UID = "3058d70e";


	//�����ѯ��ʱ�û������
	char sql_query1[255];
	char * sql1 = "select * from OnTable where UID = '";
	strcpy_s(sql_query1, sql1);
	strcat_s(sql_query1, _UID);
	strcat_s(sql_query1, "'");

	CString query1 = Query(sql_query1, 0);   //��ѯ��ʱ�û��ϻ������Ƿ��Ѵ��ڸ��û�

	//��ȡ��ǰʱ��
	CTime curTime = CTime::GetCurrentTime();

	boolean flag1 = false;
	if (query1 == ""){   //���û�����δ�ϻ�
		
		//�����ѯ�û������
		char sql_query2[255];
		char * sql2 = "select * from RemainTimeTable where UID = '";
		strcpy_s(sql_query2, sql2);
		strcat_s(sql_query2, _UID);
		strcat_s(sql_query2, "'");

		CString query2 = Query(sql_query2, 1);   //��ѯ�û����и��û��� �õ���ʱ
		char remaintime[20] = { '\0' };          
		WideCharToMultiByte(CP_OEMCP, NULL, query2, -1, remaintime, 20, NULL, FALSE); //��CString תΪchar *

		//����ʱ��CString תΪchar *
		CString curT = curTime.Format("%Y/%m/%d %H:%M:%S");
		char curtime[20] = { '\0' };
		WideCharToMultiByte(CP_OEMCP, NULL, curT, -1, curtime, 20, NULL, FALSE);

		
		//����������ʱ�ϻ��û������
		char sql_insert[255];
		char *sql3 = "insert into OnTable(UID, RemainTime, StartTime, isOvertime) values('";
		strcpy_s(sql_insert, sql3);
		strcat_s(sql_insert, _UID);
		strcat_s(sql_insert, "', '");
		strcat_s(sql_insert, remaintime);
		strcat_s(sql_insert, "','");
		strcat_s(sql_insert, curtime);
		strcat_s(sql_insert, "','");
		strcat_s(sql_insert, "0");
		strcat_s(sql_insert, "')");

		flag1 = Insert(sql_insert);   //�����û����ݲ�����ʱ�ϻ�����
			

		if (flag1){  //�ϻ��ɹ�
			//�����ѯ��䣬 Ϊ�˵õ���ʱ
			char sql_query4[255];
			char * sql5 = "select * from OnTable where UID = '";
			strcpy_s(sql_query4, sql5);
			strcat_s(sql_query4, _UID);
			strcat_s(sql_query4, "'");

			CString remainTime = Query(sql_query4, 1);   //��ѯ�û������Ƿ��Ѵ��ڸ��û�, �õ���ʱ

			//����ʱ��ʾΪʱ������ʽ
			int k = _ttoi(remainTime);
			int h = k / 3600;
			int min = (k - h * 3600) / 60;
			int sec = k - h * 3600 - min * 60;
			CString h_, min_, sec_;   
			h_.Format(_T("%d"), h);
			min_.Format(_T("%d"), min);
			sec_.Format(_T("%d"), sec);

			CString result = _T("�ɹ�");
			CString con = _T("�û��ϻ�");
			CString contents = _T("");

			//��ʽ���
			contents.Format(_T("���ţ�%s\r\nʱ�䣺%s\r\n�����%s\r\n���ݣ�%s\r\n��ʱ��%sʱ%s��%s��\r\n\r\n"), CStringW(_UID), CStringW(curTime.Format("%Y/%m/%d %H:%M:%S")), CStringW(result), CStringW(con), CStringW(h_), CStringW(min_), CStringW(sec_));

			insertRecord(contents, _UID);   //���ϻ���¼������

			((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("�ϻ��ɹ�"));
			m_netStatus = 1;

		}
		else{
			//��ʽ���
			CString contents = _T("");
			contents.Format(_T("���ţ�%s\r\nʱ�䣺%s\r\n�����%s\r\n\r\n"), CStringW(_UID), CStringW(curTime.Format("%Y/%m/%d %H:%M:%S")), CStringW("�ϻ�ʧ��"));
			insertRecord(contents, _UID);//���ϻ���¼������

			((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("�ϻ�ʧ��"));
			m_netStatus = 0;

		}

	}
	else{
		
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("���Ѿ����ϻ��У� �����ٴ��ϻ�"));
		m_netStatus = 0;

	}

}


//�û��˳�
void CAppDevp::OnClickedButton72()
{

	ConnectSql();  //�������ݿ�

	char *_UID = "3058d70e";

	//�����ѯ��ʱ�û������
	//char *_UID = "12678";
	char sql_query[255];
	char * sql1 = "select * from OnTable where UID = '";
	strcpy_s(sql_query, sql1);
	strcat_s(sql_query, _UID);
	strcat_s(sql_query, "'");

	CString query = Query(sql_query, 0);     //����ʱ�û����в�ѯ�û��Ƿ����ϻ�
	CString query_remain = Query(sql_query, 1); //����ʱ�û����в�ѯ�û����ݣ������ʱ
	if (query != ""){        //�û����ϻ���
		//����ɾ�����
		char sql_del[255];
		char * sql2 = "delete from OnTable where UID = '";
		strcpy_s(sql_del, sql2);
		strcat_s(sql_del, _UID);
		strcat_s(sql_del, "'");
		boolean flag = Delete(sql_del);    //���û���Ϣ����ʱ�ϻ�����ɾ���� �û�����

		//��ȡ��ǰʱ��
		CTime curTime = CTime::GetCurrentTime();

		//����ʱ��ʾΪʱ������ʽ
		int k = _ttoi(query_remain);
		int h = k / 3600;
		int min = (k - h * 3600) / 60;
		int sec = k - h * 3600 - min * 60;
		CString h_, min_, sec_;
		h_.Format(_T("%d"), h);  
		min_.Format(_T("%d"), min);
		sec_.Format(_T("%d"), sec);

		if (flag){  //ɾ�������ɹ�
			CString result = _T("�ɹ�");
			CString con = _T("�û��˳�");
			CString contents;

			//��CString תΪchar *
			char query_remain1[20] = { '\0' };
			WideCharToMultiByte(CP_OEMCP, NULL, query_remain, -1, query_remain1, 20, NULL, FALSE);

			//�����û��������䣬 �����û�����ʱ
			char sql_update[255];
			char *sql_up = "update RemainTimeTable set RemainTime = '";         //���±�����ʱ
			strcpy_s(sql_update, sql_up);
			strcat_s(sql_update, query_remain1);
			strcat_s(sql_update, "' where UID = '");
			strcat_s(sql_update, _UID);
			strcat_s(sql_update, "'");

			boolean flag1 = Update(sql_update);  //����

			//��ʽ���
			contents.Format(_T("���ţ�%s\r\nʱ�䣺%s\r\n�����%s\r\n���ݣ�%s\r\n��ʱ��%sʱ%s��%s��\r\n\r\n"), CStringW(_UID), CStringW(curTime.Format("%Y/%m/%d %H:%M:%S")), CStringW(result), CStringW(con), h_, min_, sec_);
			insertRecord(contents, _UID);  //�����˳���¼

			((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("�û��ɹ��˳�"));
			m_netStatus = 1;

		}
		else{
			//��ʽ���
			CString contents;
			contents.Format(_T("���ţ�%s\r\nʱ�䣺%s\r\n�����%s\r\n��ʱ��%sʱ%s��%s��\r\n\r\n"), CStringW(_UID), CStringW(curTime.Format("%Y/%m/%d %H:%M:%S")), CStringW("�˳�ʧ��"), h_, min_, sec_);
			insertRecord(contents, _UID);  //�����˳���¼
			((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("�˳�ʧ��"));
			m_netStatus = 0;

		}
	}
	else{
		
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("�˳�ʧ�ܣ� �����ϻ���¼"));
		m_netStatus = 0;
	}
}

//��ʱĬ�ϳ�ʼ��
void CAppDevp::OnClickedButton73()
{
	ConnectSql();  //�������ݿ�
	
	
	char *_UID = "3058d70e";

	//char *_UID = "12678";

	//�����ѯ��ʱ�����
	char sql_query[255];
	char * sql1 = "select * from OnTable where UID = '";
	strcpy_s(sql_query, sql1);
	strcat_s(sql_query, _UID);
	strcat_s(sql_query, "'");

	CString h, min, sec;  //��������ж�ȡ��ʱ��Ϣ
	((CEdit*)GetDlgItem(IDC_EDIT71))->GetWindowText(h);
	((CEdit*)GetDlgItem(IDC_EDIT72))->GetWindowText(min);
	((CEdit*)GetDlgItem(IDC_EDIT73))->GetWindowText(sec);


	if ((!h.IsEmpty()) && (!min.IsEmpty()) && (!sec.IsEmpty()) )
	{
		//��ʱ����int��ʽ
		int h_ = _ttoi(h), min_ = _ttoi(min), sec_ = _ttoi(sec);
		int s = h_ * 3600 + min_ * 60 + sec_;  //����������
		char ss[20];
		_itoa_s(s, ss, 20, 10);

		
		//�����û��������䣬 ��ʱ��ʼ��
		char sql_update1[255];
		char * sql2 = "update RemainTimeTable set RemainTime = '";
		strcpy_s(sql_update1, sql2);
		strcat_s(sql_update1, ss);
		strcat_s(sql_update1, "'");
		strcat_s(sql_update1, "where UID = '");
		strcat_s(sql_update1, _UID);
		strcat_s(sql_update1, "'");         //�����û�������ʱ����ʱ��ʼ��
		boolean flag1 = Update(sql_update1);

		CString query = Query(sql_query, 0); //����ʱ�û����в�ѯ�û�
		if (query != ""){  //�û����ϻ���

			char sql_update2[255];
			char * sql3 = "update OnTable set RemainTime = '";
			strcpy_s(sql_update2, sql3);
			strcat_s(sql_update2, ss);
			strcat_s(sql_update2, "'");
			strcat_s(sql_update2, "where UID = '");
			strcat_s(sql_update2, _UID);
			strcat_s(sql_update2, "'");       //������ʱ�û�������ʱ����ʱ��ʼ��
			boolean flag2 = Update(sql_update2);
			if (flag2) ((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("��ʼ����ʱ�ɹ�"));
				m_netStatus = 1;
		}
		
	}
	else{
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("�����������ݣ��ٳ�ʼ����ʱ"));
		m_netStatus = 0;
	}

	

}


//��ѯ��ʱ
void CAppDevp::OnClickedButton74()
{
	ConnectSql();  //�������ݿ�
	
	char *_UID = "3058d70e";

	//�����ѯ��ʱ��䣬 ����ʱ�û�����
	
	//char *_UID = "12678";
	char sql_query[255];
	char * sql1 = "select * from OnTable where UID = '";
	strcpy_s(sql_query, sql1);
	strcat_s(sql_query, _UID);
	strcat_s(sql_query, "'");

	CString query = Query(sql_query, 1);  //��ѯ
	if (query != "")
	{
		//����ʱ��ʾΪʱ������ʽ
		int k = _ttoi(query);
		int h = k / 3600;
		int min = (k - h * 3600) / 60;
		int sec = k - h * 3600 - min * 60;
		CString h_, min_, sec_;
		h_.Format(_T("%d"), h);
		min_.Format(_T("%d"), min);
		sec_.Format(_T("%d"), sec);
		((CEdit*)GetDlgItem(IDC_EDIT71))->SetWindowText(h_);  
		((CEdit*)GetDlgItem(IDC_EDIT72))->SetWindowText(min_);
		((CEdit*)GetDlgItem(IDC_EDIT73))->SetWindowText(sec_);
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("��ѯ�ɹ�"));
		m_netStatus = 1;
	}
	else
	{
		((CEdit*)GetDlgItem(IDC_EDIT71))->SetWindowText(_T(""));
		((CEdit*)GetDlgItem(IDC_EDIT72))->SetWindowText(_T(""));
		((CEdit*)GetDlgItem(IDC_EDIT73))->SetWindowText(_T(""));
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("��δ�ϻ���¼�� ���ܲ�ѯ"));
		m_netStatus = 0;
	}

}

//�����ʷ��¼
void CAppDevp::OnClickedButton81()
{
	
	char *_UID = "3058d70e";

	//char *_UID = "12678";

	char sql_del1[50];
	char *sql_del = "delete from Record where ID = '";
	strcpy_s(sql_del1, sql_del);
	strcat_s(sql_del1, _UID);
	strcat_s(sql_del1, "'");
	if (!mysql_query(&mysql, sql_del1))  //ɾ��
	{
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("ɾ�����¼�ɹ�"));
		m_netStatus = 1;
		queryRecord(_UID);
	}
	else{

		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("ɾ�����¼ʧ��") + CString(mysql_error(&mysql)));
		m_netStatus = 0;

	}
}

//��ȡ����ʾ��ʷ��¼
void CAppDevp::OnClickedButton82()
{
	
	//��ȡ��ƬID
	char *_UID = "3058d70e";
	
	//char *_UID = "12678";

	queryRecord(_UID);
	
}



HBRUSH CAppDevp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID()) {
	case IDC_EDIT64:
		if (this->m_EMoneyStatus)
			pDC->SetTextColor(BLUE);//�����ɹ�����Ϊ��
		else
			pDC->SetTextColor(RED);//ʧ������Ϊ�죬RED,BLUE,BLACK��ǰ�涼�ж���
		break;
	case IDC_EDIT74:
		if (this->m_netStatus)
			pDC->SetTextColor(BLUE);//�����ɹ�����Ϊ��
		else
			pDC->SetTextColor(RED);//ʧ������Ϊ�죬RED,BLUE,BLACK��ǰ�涼�ж���
		break;
	default:
		pDC->SetTextColor(BLACK);
		break;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//��ʱ����Ӧ����
void CAppDevp::OnTimer(UINT_PTR nIDEvent)
{
	ConnectSql();  //�������ݿ�

	switch (nIDEvent) {
	case IDTIMER1:
	{
		//������ʱ�û��ϻ���������
		char *sql_update2 = "update OnTable set RemainTime = RemainTime - 1";         //������ʱ�û��ϻ�������ʱ
		boolean flag2 = Update(sql_update2);

		MYSQL_RES *result;
		MYSQL_ROW row;
		char *queryk = "select * from OnTable";
		mysql_query(&mysql, queryk);  //��ѯ�����û���ʱ������ʱΪ0��ǿ������
		result = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(result)){

			if (row != NULL){
				int k = atoi(row[1]);
				if (k <= 0){          //�û���ʱ�Ѿ�Ϊ0��ǿ������
					//����ɾ�����
					char sql_del[255];
					char * sql2 = "delete from OnTable where UID = '";
					strcpy_s(sql_del, sql2);
					strcat_s(sql_del, row[0]);
					strcat_s(sql_del, "'");
					boolean flag = Delete(sql_del);    //���û���Ϣ����ʱ�ϻ�����ɾ��

					//��ȡ��ǰʱ��
					CTime curTime = CTime::GetCurrentTime();

					//�����û���������
					char sql_update[255];
					char *sql_up = "update RemainTimeTable set RemainTime = '";         //���±�����ʱ
					strcpy_s(sql_update, sql_up);
					strcat_s(sql_update, "'0'");
					strcat_s(sql_update, "' where UID = '");
					strcat_s(sql_update, row[0]);
					strcat_s(sql_update, "'");

					boolean flag1 = Update(sql_update);

					CString contents;
					//��ʽ���
					contents.Format(_T("���ţ�%s\r\nʱ�䣺%s\r\n���ݣ�%s\r\n\r\n"), CStringW(row[0]), CStringW(curTime.Format("%Y/%m/%d %H:%M:%S")), CStringW("ǿ���˳��� ������ʱ��Ϊ0"));

					insertRecord(contents, row[0]);
					((CEdit*)GetDlgItem(IDC_EDIT71))->SetWindowText(_T("0"));
					((CEdit*)GetDlgItem(IDC_EDIT72))->SetWindowText(_T("0"));
					((CEdit*)GetDlgItem(IDC_EDIT73))->SetWindowText(_T("0"));
					((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("�û���ǿ���˳�"));
				}
			}
		}

		break;
	}

	default:
	{
		break;
	}
	}

	CDialogEx::OnTimer(nIDEvent);
}
