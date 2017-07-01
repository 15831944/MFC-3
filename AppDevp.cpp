// AppDevp.cpp : 实现文件
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
	case 0: state = "成功"; break;
	case -1: state = "卡片类型不对"; break;
	case -2: state = "无卡"; break;
	case -3: state = "有卡未上电"; break;
	case -4: state = "卡片无应答"; break;
	case -5: state = "BCC校验错误"; break;
	case -6: state = "接收超时"; break;
	case -7: state = "执行失败"; break;
	case -8: state = "卡片位置错误"; break;
	case -9: state = "设置失败"; break;
	case -11: state = "读卡器连接错误"; break;
	case -12: state = "未建立连接（没有执行打开设备函数）"; break;
	case -13: state = "（动态库）不支持该命令"; break;
	case -14: state = "（发给动态库的）命令参数错误"; break;
	case -15: state = "信息校验和出错"; break;
	case -16: state = "卡片上电失败"; break;
	case -17: state = "卡片复位失败"; break;
	case -18: state = "卡片下电失败"; break;
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
//秘钥类型转换
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
		//	TRACE("\n %s  ",tmp); //输出失败
		p++;
		(*asc_len)++;
	}
	*p = '\0';
	return;
}
// CAppDevp 对话框

IMPLEMENT_DYNAMIC(CAppDevp, CDialogEx)

CAppDevp::CAppDevp(CWnd* pParent /*=NULL*/)
: CDialogEx(CAppDevp::IDD, pParent)
{
	SetTimer(IDTIMER1, 1000, NULL);   //开启定时器
}

CAppDevp::~CAppDevp()
{
	KillTimer(IDTIMER1);  //关闭定时器
}

void CAppDevp::DoDataExchange(CDataExchange* pDX)
{
	//SetTimer(IDTIMER1, 1000, NULL);   //开启定时器

	ConnectSql();  //连接数据库
	
	//获取卡片ID
	//CString UID = GetCardUID();
	//char _UID[20] = { '\0' };
	//WideCharToMultiByte(CP_OEMCP, NULL, UID, -1, _UID, 20, NULL, FALSE); //将CString 转为char *
	char *_UID = "3058d70e";

	//创造查询临时用户表语句
	char sql_query1[255];
	char * sql1 = "select * from RemainTimeTable where UID = '";
	strcpy_s(sql_query1, sql1);
	strcat_s(sql_query1, _UID);
	strcat_s(sql_query1, "'");

	CString query1 = Query(sql_query1, 0);   //查询用户上机表中是否已存在该用户
	if (query1 == _T(""))
	{
		//创建插入用户表语句
		char sql_insert1[255];
		char * sql3 = "insert into RemainTimeTable(UID, RemainTime) values('";
		strcpy_s(sql_insert1, sql3);
		strcat_s(sql_insert1, _UID);
		strcat_s(sql_insert1, "', '");
		strcat_s(sql_insert1, defaultRemainTime);
		strcat_s(sql_insert1, "')");
		boolean flag = Insert(sql_insert1);   //将该用户数据插入用户表中
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

//获取UID
CString CAppDevp::GetCardUID() {
	CString uid, temp;
	unsigned char buffer[1024];
	int bufferLength;
	//成功获取
	int flag = find_14443(buffer, &bufferLength);
	if (flag == IFD_OK) {
		uid.Empty();
		for (int i = 0; i < bufferLength; i++) {
			//将获得的UID数据转化为16进制
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

// CAppDevp 消息处理程序

//钱包初始化，用户在余额编辑框中输入金额，CString类型，要转换为long类型保存，
void CAppDevp::OnClickedButton61()
{
	// TODO:  在此添加控件通知处理程序代码
	//将显示框置为空
	((CEdit*)GetDlgItem(IDC_EDIT62))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT63))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T(""));

	CString remainings;// = _T("12");
	((CEdit*)GetDlgItem(IDC_EDIT61))->GetWindowText(remainings);//从余额的编辑框获取值CString
	TRACE(L"\n\n输入初始化金额是%s\n", remainings);//\r\n输出

	if (remainings.IsEmpty()) {
		this->m_EMoneyStatus = false;//这一个参数用来做什么    ???????????????????
		//((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("请输入正确金额！"));
		MessageBox(_T("请输入正确的初始化金额！"));
		return;
	}
	long account = _ttol(remainings);//CString转为long型
	if (account < 0) {
		this->m_EMoneyStatus = false;//这一个参数用来做什么    ???????????????????
		MessageBox(_T("零钱不能小于0，请输入正确的初始化金额！"));
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
	//秘钥类型转换
	HexCString2UnsignedCharStar(pwd, psw, &len_chpwd);
	//输出查看类型转换是否正确
	TRACE(" \n %s", psw);
	TRACE(" \n\n 类型转换输出完毕\n\n");
	//int write_account(int page, int block, unsigned char pswtype, unsigned char *psw, LONG account);
	int flag = write_account(sectionNum, blockNum, pswtype, psw, account);//将金额写入电子钱包
	//TRACE(L"\n\nflag%d\n", flag);//\r\n输出												//判断写入是否成功
	CString str = returnValueMean(flag);
	if (flag == 0) {
		this->m_EMoneyStatus = true;
	}
	else{
		this->m_EMoneyStatus = false;
	}
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(str);
	
}

// 查询余额处理函数
void CAppDevp::OnClickedButton62()
{
	// TODO:  在此添加控件通知处理程序代码
	//将显示框置为空
	((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT62))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT63))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T(""));

	unsigned char pswtype = 0x0A;
	unsigned char psw[8];
	int len_chpwd = 0;
	CString pwd = _T("FFFFFFFFFFFF");
	//秘钥类型转换
	HexCString2UnsignedCharStar(pwd, psw, &len_chpwd);
	long account;
	int flag = read_account(int(15), int(0), pswtype, psw, &account);//读取电子钱包余额
	CString strState = returnValueMean(flag);
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(strState);//状态栏显示查询状态
	if (flag == 0) {
		this->m_EMoneyStatus = true;
		CString str;
		str.Format(_T("%ld"), account);//long型转为CString
		((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(str);//查询到的余额显示到余额框
		return;
	}
	this->m_EMoneyStatus = false;
}

//充值
void CAppDevp::OnClickedButton63()
{
	// TODO:  在此添加控件通知处理程序代码
	//将显示框置为空
	((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT63))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T(""));

	//读取充值栏，为空则return
	CString recharge;
	((CEdit*)GetDlgItem(IDC_EDIT62))->GetWindowText(recharge);//从余额的编辑框获取值CString
	long rechargeLong = _ttol(recharge);//CString--->long
	if (recharge.IsEmpty()) {
		//((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("请输入正确充值金额！"));
		MessageBox(_T("请输入正确充值金额！"));
		return;
	}
	if (rechargeLong < 0) {
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("充值失败，金额不能为负！"));
		return;
	}
	//读取卡片余额
	long account;
	unsigned char pswtype = 0x0A;
	unsigned char psw[8];
	int len_chpwd = 0;
	CString pwd = _T("FFFFFFFFFFFF");
	//秘钥类型转换
	HexCString2UnsignedCharStar(pwd, psw, &len_chpwd);
	int flag1 = read_account(int(15), int(0), pswtype, psw, &account); // 读取电子钱包余额	
	
	CString strRead = returnValueMean(flag1);
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(strRead);
	if (flag1 < 0) {
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("步骤充值，余额读取失败！"));
		return;
	}

	
	long accountSum = rechargeLong + account;
	int flag = write_account(int(15), int(0), pswtype, psw, accountSum);//将金额写入电子钱包
	//判断是否写入成功
	CString str = returnValueMean(flag);
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(str);

	CString Filename = _T("C://record.txt");
	CRecordHelper helper(Filename);
	CString vid = GetCardUID();
	CString con = _T("充值");
	CString result;
	//显示充值后的余额
	if (flag == 0) {//充值成功
		this->m_EMoneyStatus = true;
		CString remainingAfterRE;
		remainingAfterRE.Format(_T("%ld"), accountSum);//long----->CString
		((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(remainingAfterRE);
		//保存充值成功记录到文件
		result = "successful";
		//saveRecharges(CString vid, CString account, long Remainings, CString con, CString result);
		helper.saveRecharges(vid, recharge, accountSum, con, result);
	}
	else {//充值失败,余额不变
		this->m_EMoneyStatus = false;
		CString remainingAfterRE;
		remainingAfterRE.Format(_T("%ld"), account);//long----->CString
		((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(remainingAfterRE);
		result = "failed";
		helper.saveRecharges(vid, recharge, account, con, result);
	}
	
}

//消费函数
void CAppDevp::OnClickedButton64()
{
	// TODO:  在此添加控件通知处理程序代码
	//将显示框置为空
	((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT62))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T(""));

	//从消费的编辑框获取值CString
	CString consumption;
	((CEdit*)GetDlgItem(IDC_EDIT63))->GetWindowText(consumption);
	if (consumption.IsEmpty()) {
		//((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("请输入正确消费金额！"));
		MessageBox(_T("请输入正确消费金额！"));
		return;
	}
	//读取余额
	long account;
	unsigned char pswtype = 0x0A;//秘钥类型
	unsigned char psw[8];
	int len_chpwd = 0;
	CString pwd = _T("FFFFFFFFFFFF");
	//秘钥类型转换
	HexCString2UnsignedCharStar(pwd, psw, &len_chpwd);

	int flag = read_account(int(15), int(0), pswtype, psw, &account);// 读取电子钱包余额	
	CString remainingBeforeConsum;
	remainingBeforeConsum.Format(_T("%ld"), account);//long----->CString
	CString strRead = returnValueMean(flag);
	((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(strRead);
	//指定文件保存记录
	CString Filename = _T("C://record.txt");
	CRecordHelper helper(Filename);
	CString vid = GetCardUID();
	CString con = _T("消费");
	CString result;

	if (flag < 0) {//读取余额失败直接结束函数
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("步骤消费，余额读取失败！"));
		this->m_EMoneyStatus = false;
		return;
	}
	//进行消费的计算
	long consumptionLong = _ttol(consumption);//CString -----> long
	if (consumptionLong < 0) {
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("消费失败，金额不能为负！"));
		MessageBox(_T("消费金额不能为负，请输入正确消费金额！"));
		this->m_EMoneyStatus = false;
	}
	else if (consumptionLong > account) {
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(_T("消费失败，余额不足！"));
		MessageBox(_T("余额不足！"));
		((CEdit*)GetDlgItem(IDC_EDIT61))->SetWindowText(remainingBeforeConsum);
		this->m_EMoneyStatus = false;

	}
	else {
		long remain = account - consumptionLong;
		int flag = write_account(int(15), int(0), pswtype, psw, remain);//将金额写入电子钱包
		//判断是否写入成功
		CString str = returnValueMean(flag);
		((CEdit*)GetDlgItem(IDC_EDIT64))->SetWindowText(str);
		//显示消费后的余额
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

// 连接数据库
boolean CAppDevp::ConnectSql()
{
	mysql_init(&mysql);  //初始化
	mysql_query(&mysql, "Set names GBK");

	char *URL = "localhost";
	char *username = "root";
	char *password = "1234567890";
	char *DBname = "NetManage";

	//连接数据库
	if (mysql_real_connect(&mysql, "localhost", "root", "1234567890", "NetManage", 3306, NULL, 0)){
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("数据库连接成功"));
		return true;
	}
	else{
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("数据库连接失败"));
		return false;
	}

}

//查询操作， flag 表示返回查询结果中的第几个数据
CString CAppDevp::Query(char *sql, int flag)
{
	mysql_query(&mysql, "Set names GBK");

	MYSQL_RES *result;
	MYSQL_ROW row;
	mysql_query(&mysql, sql);  //查询
	result = mysql_store_result(&mysql);  //查询结果
	row = mysql_fetch_row(result);   //一行查询结果
	if (row != NULL){
		char k[20];
		strcpy_s(k, row[flag]);  //得到数据， 放入k中
		CString str1(k);
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("查询成功"));

		return (str1);

	}
	else{

		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("查询失败") + CString(mysql_error(&mysql)));
		return _T("");
	}

}

//插入操作
boolean CAppDevp::Insert(char *sql_insert)
{
	mysql_query(&mysql, "Set names GBK");

	if (!mysql_query(&mysql, (char*)(sql_insert)))  //插入
	{
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("插入成功"));
		return true;
	}
	else{
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("插入失败") + CString(mysql_error(&mysql)));
		return false;
	}
}

//更新操作
boolean CAppDevp::Update(char* sql)
{
	mysql_query(&mysql, "Set names GBK");

	if (!mysql_query(&mysql, sql))  //更新
	{
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("更新成功"));
		return true;
	}
	else{
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("更新失败") + CString(mysql_error(&mysql)));
		return false;
	}
}

//删除操作
boolean CAppDevp::Delete(char* sql_del)
{
	mysql_query(&mysql, "Set names GBK");

	if (!mysql_query(&mysql, sql_del))  //删除
	{
		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("删除成功"));
		return true;
	}
	else{

		//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("删除失败") + CString(mysql_error(&mysql)));
		return false;
	}
}

//将操作记录放入数据库中
void CAppDevp::insertRecord(CString contents, char* ID)
{
	char recor[100] = { '\0' };
	WideCharToMultiByte(CP_OEMCP, NULL, contents, -1, recor, 100, NULL, FALSE);
	TRACE(recor);

	//创建插入语句
	char sql_insertk[200];
	char *sql3 = "insert into Record values('";
	strcpy_s(sql_insertk, sql3);
	strcat_s(sql_insertk, ID);
	strcat_s(sql_insertk, "', '");
	strcat_s(sql_insertk, recor);
	strcat_s(sql_insertk, "')");
	boolean f = Insert(sql_insertk);  //插入
	//((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("插入") +CString(mysql_error(&mysql)));
}

// 查询操作记录并显示出来
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
	mysql_query(&mysql, sql_query);  //查询
	result_ = mysql_store_result(&mysql);  //查询结果
	while (row = mysql_fetch_row(result_)){
		//row = mysql_fetch_row(result_);
		if (row != NULL){
			strcat_s(record, row[1]);
		}
	}

	((CEdit*)GetDlgItem(IDC_EDIT81))->SetWindowText(CStringW(CString(record)));  //显示
}



//开始上机
void CAppDevp::OnClickedButton71()
{
	ConnectSql();  //连接数据库
	

	char *_UID = "3058d70e";


	//创造查询临时用户表语句
	char sql_query1[255];
	char * sql1 = "select * from OnTable where UID = '";
	strcpy_s(sql_query1, sql1);
	strcat_s(sql_query1, _UID);
	strcat_s(sql_query1, "'");

	CString query1 = Query(sql_query1, 0);   //查询临时用户上机表中是否已存在该用户

	//获取当前时间
	CTime curTime = CTime::GetCurrentTime();

	boolean flag1 = false;
	if (query1 == ""){   //该用户现在未上机
		
		//创造查询用户表语句
		char sql_query2[255];
		char * sql2 = "select * from RemainTimeTable where UID = '";
		strcpy_s(sql_query2, sql2);
		strcat_s(sql_query2, _UID);
		strcat_s(sql_query2, "'");

		CString query2 = Query(sql_query2, 1);   //查询用户表中该用户， 得到余时
		char remaintime[20] = { '\0' };          
		WideCharToMultiByte(CP_OEMCP, NULL, query2, -1, remaintime, 20, NULL, FALSE); //将CString 转为char *

		//将余时从CString 转为char *
		CString curT = curTime.Format("%Y/%m/%d %H:%M:%S");
		char curtime[20] = { '\0' };
		WideCharToMultiByte(CP_OEMCP, NULL, curT, -1, curtime, 20, NULL, FALSE);

		
		//创建插入临时上机用户表语句
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

		flag1 = Insert(sql_insert);   //将该用户数据插入临时上机表中
			

		if (flag1){  //上机成功
			//创造查询语句， 为了得到余时
			char sql_query4[255];
			char * sql5 = "select * from OnTable where UID = '";
			strcpy_s(sql_query4, sql5);
			strcat_s(sql_query4, _UID);
			strcat_s(sql_query4, "'");

			CString remainTime = Query(sql_query4, 1);   //查询用户表中是否已存在该用户, 得到余时

			//将余时表示为时分秒形式
			int k = _ttoi(remainTime);
			int h = k / 3600;
			int min = (k - h * 3600) / 60;
			int sec = k - h * 3600 - min * 60;
			CString h_, min_, sec_;   
			h_.Format(_T("%d"), h);
			min_.Format(_T("%d"), min);
			sec_.Format(_T("%d"), sec);

			CString result = _T("成功");
			CString con = _T("用户上机");
			CString contents = _T("");

			//格式输出
			contents.Format(_T("卡号：%s\r\n时间：%s\r\n结果：%s\r\n内容：%s\r\n余时：%s时%s分%s秒\r\n\r\n"), CStringW(_UID), CStringW(curTime.Format("%Y/%m/%d %H:%M:%S")), CStringW(result), CStringW(con), CStringW(h_), CStringW(min_), CStringW(sec_));

			insertRecord(contents, _UID);   //将上机记录存起来

			((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("上机成功"));
			m_netStatus = 1;

		}
		else{
			//格式输出
			CString contents = _T("");
			contents.Format(_T("卡号：%s\r\n时间：%s\r\n结果：%s\r\n\r\n"), CStringW(_UID), CStringW(curTime.Format("%Y/%m/%d %H:%M:%S")), CStringW("上机失败"));
			insertRecord(contents, _UID);//将上机记录存起来

			((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("上机失败"));
			m_netStatus = 0;

		}

	}
	else{
		
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("您已经在上机中， 无需再次上机"));
		m_netStatus = 0;

	}

}


//用户退出
void CAppDevp::OnClickedButton72()
{

	ConnectSql();  //连接数据库

	char *_UID = "3058d70e";

	//创造查询临时用户表语句
	//char *_UID = "12678";
	char sql_query[255];
	char * sql1 = "select * from OnTable where UID = '";
	strcpy_s(sql_query, sql1);
	strcat_s(sql_query, _UID);
	strcat_s(sql_query, "'");

	CString query = Query(sql_query, 0);     //在临时用户表中查询用户是否在上机
	CString query_remain = Query(sql_query, 1); //在临时用户表中查询用户数据，获得余时
	if (query != ""){        //用户在上机中
		//创建删除语句
		char sql_del[255];
		char * sql2 = "delete from OnTable where UID = '";
		strcpy_s(sql_del, sql2);
		strcat_s(sql_del, _UID);
		strcat_s(sql_del, "'");
		boolean flag = Delete(sql_del);    //将用户信息从临时上机表中删除， 用户下线

		//获取当前时间
		CTime curTime = CTime::GetCurrentTime();

		//将余时表示为时分秒形式
		int k = _ttoi(query_remain);
		int h = k / 3600;
		int min = (k - h * 3600) / 60;
		int sec = k - h * 3600 - min * 60;
		CString h_, min_, sec_;
		h_.Format(_T("%d"), h);  
		min_.Format(_T("%d"), min);
		sec_.Format(_T("%d"), sec);

		if (flag){  //删除操作成功
			CString result = _T("成功");
			CString con = _T("用户退出");
			CString contents;

			//将CString 转为char *
			char query_remain1[20] = { '\0' };
			WideCharToMultiByte(CP_OEMCP, NULL, query_remain, -1, query_remain1, 20, NULL, FALSE);

			//创建用户表更新语句， 更新用户表余时
			char sql_update[255];
			char *sql_up = "update RemainTimeTable set RemainTime = '";         //更新表中余时
			strcpy_s(sql_update, sql_up);
			strcat_s(sql_update, query_remain1);
			strcat_s(sql_update, "' where UID = '");
			strcat_s(sql_update, _UID);
			strcat_s(sql_update, "'");

			boolean flag1 = Update(sql_update);  //更新

			//格式输出
			contents.Format(_T("卡号：%s\r\n时间：%s\r\n结果：%s\r\n内容：%s\r\n余时：%s时%s分%s秒\r\n\r\n"), CStringW(_UID), CStringW(curTime.Format("%Y/%m/%d %H:%M:%S")), CStringW(result), CStringW(con), h_, min_, sec_);
			insertRecord(contents, _UID);  //保存退出记录

			((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("用户成功退出"));
			m_netStatus = 1;

		}
		else{
			//格式输出
			CString contents;
			contents.Format(_T("卡号：%s\r\n时间：%s\r\n结果：%s\r\n余时：%s时%s分%s秒\r\n\r\n"), CStringW(_UID), CStringW(curTime.Format("%Y/%m/%d %H:%M:%S")), CStringW("退出失败"), h_, min_, sec_);
			insertRecord(contents, _UID);  //保存退出记录
			((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("退出失败"));
			m_netStatus = 0;

		}
	}
	else{
		
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("退出失败， 请先上机登录"));
		m_netStatus = 0;
	}
}

//余时默认初始化
void CAppDevp::OnClickedButton73()
{
	ConnectSql();  //连接数据库
	
	
	char *_UID = "3058d70e";

	//char *_UID = "12678";

	//创造查询临时表语句
	char sql_query[255];
	char * sql1 = "select * from OnTable where UID = '";
	strcpy_s(sql_query, sql1);
	strcat_s(sql_query, _UID);
	strcat_s(sql_query, "'");

	CString h, min, sec;  //从输入框中读取余时信息
	((CEdit*)GetDlgItem(IDC_EDIT71))->GetWindowText(h);
	((CEdit*)GetDlgItem(IDC_EDIT72))->GetWindowText(min);
	((CEdit*)GetDlgItem(IDC_EDIT73))->GetWindowText(sec);


	if ((!h.IsEmpty()) && (!min.IsEmpty()) && (!sec.IsEmpty()) )
	{
		//余时化成int形式
		int h_ = _ttoi(h), min_ = _ttoi(min), sec_ = _ttoi(sec);
		int s = h_ * 3600 + min_ * 60 + sec_;  //化成总秒数
		char ss[20];
		_itoa_s(s, ss, 20, 10);

		
		//创建用户表更新语句， 余时初始化
		char sql_update1[255];
		char * sql2 = "update RemainTimeTable set RemainTime = '";
		strcpy_s(sql_update1, sql2);
		strcat_s(sql_update1, ss);
		strcat_s(sql_update1, "'");
		strcat_s(sql_update1, "where UID = '");
		strcat_s(sql_update1, _UID);
		strcat_s(sql_update1, "'");         //更新用户表中余时，余时初始化
		boolean flag1 = Update(sql_update1);

		CString query = Query(sql_query, 0); //在临时用户表中查询用户
		if (query != ""){  //用户在上机中

			char sql_update2[255];
			char * sql3 = "update OnTable set RemainTime = '";
			strcpy_s(sql_update2, sql3);
			strcat_s(sql_update2, ss);
			strcat_s(sql_update2, "'");
			strcat_s(sql_update2, "where UID = '");
			strcat_s(sql_update2, _UID);
			strcat_s(sql_update2, "'");       //更新临时用户表中余时，余时初始化
			boolean flag2 = Update(sql_update2);
			if (flag2) ((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("初始化余时成功"));
				m_netStatus = 1;
		}
		
	}
	else{
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("请先输入数据，再初始化余时"));
		m_netStatus = 0;
	}

	

}


//查询余时
void CAppDevp::OnClickedButton74()
{
	ConnectSql();  //连接数据库
	
	char *_UID = "3058d70e";

	//创造查询余时语句， 在临时用户表中
	
	//char *_UID = "12678";
	char sql_query[255];
	char * sql1 = "select * from OnTable where UID = '";
	strcpy_s(sql_query, sql1);
	strcat_s(sql_query, _UID);
	strcat_s(sql_query, "'");

	CString query = Query(sql_query, 1);  //查询
	if (query != "")
	{
		//将余时表示为时分秒形式
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
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("查询成功"));
		m_netStatus = 1;
	}
	else
	{
		((CEdit*)GetDlgItem(IDC_EDIT71))->SetWindowText(_T(""));
		((CEdit*)GetDlgItem(IDC_EDIT72))->SetWindowText(_T(""));
		((CEdit*)GetDlgItem(IDC_EDIT73))->SetWindowText(_T(""));
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("您未上机登录， 不能查询"));
		m_netStatus = 0;
	}

}

//清空历史记录
void CAppDevp::OnClickedButton81()
{
	
	char *_UID = "3058d70e";

	//char *_UID = "12678";

	char sql_del1[50];
	char *sql_del = "delete from Record where ID = '";
	strcpy_s(sql_del1, sql_del);
	strcat_s(sql_del1, _UID);
	strcat_s(sql_del1, "'");
	if (!mysql_query(&mysql, sql_del1))  //删除
	{
		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("删除表记录成功"));
		m_netStatus = 1;
		queryRecord(_UID);
	}
	else{

		((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("删除表记录失败") + CString(mysql_error(&mysql)));
		m_netStatus = 0;

	}
}

//读取并显示历史记录
void CAppDevp::OnClickedButton82()
{
	
	//获取卡片ID
	char *_UID = "3058d70e";
	
	//char *_UID = "12678";

	queryRecord(_UID);
	
}



HBRUSH CAppDevp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID()) {
	case IDC_EDIT64:
		if (this->m_EMoneyStatus)
			pDC->SetTextColor(BLUE);//开启成功字体为蓝
		else
			pDC->SetTextColor(RED);//失败字体为红，RED,BLUE,BLACK在前面都有定义
		break;
	case IDC_EDIT74:
		if (this->m_netStatus)
			pDC->SetTextColor(BLUE);//开启成功字体为蓝
		else
			pDC->SetTextColor(RED);//失败字体为红，RED,BLUE,BLACK在前面都有定义
		break;
	default:
		pDC->SetTextColor(BLACK);
		break;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//定时器相应函数
void CAppDevp::OnTimer(UINT_PTR nIDEvent)
{
	ConnectSql();  //连接数据库

	switch (nIDEvent) {
	case IDTIMER1:
	{
		//创建临时用户上机表更新语句
		char *sql_update2 = "update OnTable set RemainTime = RemainTime - 1";         //更新临时用户上机表中余时
		boolean flag2 = Update(sql_update2);

		MYSQL_RES *result;
		MYSQL_ROW row;
		char *queryk = "select * from OnTable";
		mysql_query(&mysql, queryk);  //查询所有用户余时，当余时为0，强制下线
		result = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(result)){

			if (row != NULL){
				int k = atoi(row[1]);
				if (k <= 0){          //用户余时已经为0，强制下线
					//创建删除语句
					char sql_del[255];
					char * sql2 = "delete from OnTable where UID = '";
					strcpy_s(sql_del, sql2);
					strcat_s(sql_del, row[0]);
					strcat_s(sql_del, "'");
					boolean flag = Delete(sql_del);    //将用户信息从临时上机表中删除

					//获取当前时间
					CTime curTime = CTime::GetCurrentTime();

					//创建用户表更新语句
					char sql_update[255];
					char *sql_up = "update RemainTimeTable set RemainTime = '";         //更新表中余时
					strcpy_s(sql_update, sql_up);
					strcat_s(sql_update, "'0'");
					strcat_s(sql_update, "' where UID = '");
					strcat_s(sql_update, row[0]);
					strcat_s(sql_update, "'");

					boolean flag1 = Update(sql_update);

					CString contents;
					//格式输出
					contents.Format(_T("卡号：%s\r\n时间：%s\r\n内容：%s\r\n\r\n"), CStringW(row[0]), CStringW(curTime.Format("%Y/%m/%d %H:%M:%S")), CStringW("强制退出， 您的余时已为0"));

					insertRecord(contents, row[0]);
					((CEdit*)GetDlgItem(IDC_EDIT71))->SetWindowText(_T("0"));
					((CEdit*)GetDlgItem(IDC_EDIT72))->SetWindowText(_T("0"));
					((CEdit*)GetDlgItem(IDC_EDIT73))->SetWindowText(_T("0"));
					((CEdit*)GetDlgItem(IDC_EDIT74))->SetWindowText(_T("用户被强制退出"));
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
