// Debugger.cpp : 实现文件
//

#pragma comment(lib,"./libs/ZM124U.lib");
#include "./libs/ZM124U.h"
#include "stdafx.h"
#include "MFCApplication1.h"
#include "Debugger.h"
#include "afxdialogex.h"


// CDebugger 对话框
#define RED RGB(255, 0, 0)
#define BLUE RGB(0, 0, 255)
#define BLACK RGB(0, 0, 0)
IMPLEMENT_DYNAMIC(CDebugger, CDialogEx)

CDebugger::CDebugger(CWnd* pParent /*=NULL*/)
: CDialogEx(CDebugger::IDD, pParent)
//, m_DebuggerRadio51(0)//默认为第一个radio
{

}

CDebugger::~CDebugger()
{
}

void CDebugger::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT11, m_DebuggerEdit11);
	DDX_Control(pDX, IDC_EDIT21, m_DebuggerEdit21);
	DDX_Control(pDX, IDC_EDIT22, m_DebuggerEdit22);
	DDX_Control(pDX, IDC_EDIT23, m_DebuggerEdit23);
	DDX_Control(pDX, IDC_EDIT31, m_DebuggerEdit31);
	DDX_Control(pDX, IDC_EDIT32, m_DebuggerEdit32);
	DDX_Control(pDX, IDC_EDIT33, m_DebuggerEdit33);
	DDX_Control(pDX, IDC_EDIT41, m_DebuggerEdit41);
	DDX_Control(pDX, IDC_EDIT42, m_DebuggerEdit42);
	DDX_Control(pDX, IDC_EDIT43, m_DebuggerEdit43);
	DDX_Control(pDX, IDC_EDIT44, m_DebuggerEdit44);
	DDX_Control(pDX, IDC_EDIT45, m_DebuggerEdit45);
	DDX_Control(pDX, IDC_EDIT46, m_DebuggerEdit46);
	DDX_Control(pDX, IDC_EDIT47, m_DebuggerEdit47);
	DDX_Control(pDX, IDC_EDIT51, m_DebuggerEdit51);
	DDX_Control(pDX, IDC_COMBO41, m_DebuggerCombo41);
	DDX_Control(pDX, IDC_COMBO42, m_DebuggerCombo42);
	DDX_Radio(pDX, IDC_RADIO51, m_DebuggerRadio51);
}


BEGIN_MESSAGE_MAP(CDebugger, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON11, &CDebugger::OnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON21, &CDebugger::OnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CDebugger::OnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON31, &CDebugger::OnClickedButton31)
	ON_BN_CLICKED(IDC_BUTTON41, &CDebugger::OnClickedButton41)
	ON_BN_CLICKED(IDC_BUTTON42, &CDebugger::OnClickedButton42)
	ON_BN_CLICKED(IDC_BUTTON43, &CDebugger::OnClickedButton43)
	ON_BN_CLICKED(IDC_BUTTON51, &CDebugger::OnClickedButton51)
	ON_BN_CLICKED(IDC_RADIO51, &CDebugger::OnClickedRadio51)
	ON_BN_CLICKED(IDC_RADIO52, &CDebugger::OnClickedRadio52)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

//首先是CString转char*
void CDebugger::CStringToChar(const CString& str, char* character, int str_len) {
	int i;
	for (i = 0; i < str_len; i++) {
		character[i] = str[i];
	}
	character[i] = '\0';
	return;
}
//CString转unsigned char *,具体步骤还是参照PPT上代码
void CDebugger::HexStr2CharArray(const CString& hexStr, unsigned char* asc, int* asc_len){
	*asc_len = 0;
	int len = hexStr.GetLength();

	char temp[200];
	char tmp[3] = { 0 };
	char* Hex;
	unsigned char* p;

	CStringToChar(hexStr, temp, len);
	Hex = temp;
	p = asc;

	while (*Hex != '\0') {
		tmp[0] = *Hex;
		Hex++;
		tmp[1] = *Hex;
		Hex++;
		tmp[2] = '\0';
		*p = (unsigned char)strtol(tmp, NULL, 16);
		p++;
		(*asc_len)++;
	}
	*p = '\0';
	return;
}



// CDebugger 消息处理程序


void CDebugger::OnClickedButton11()//开启设备
{
	CString stainfo;
	int sta = IDD_PowerOn();//开启设备函数
	if (sta == 0)	isDeviceOpen = true;//表示开启设备成功
	else isDeviceOpen = false;//表示开启设备失败
	switch(sta){//判断执行状态
	case 0: stainfo = "执行成功";
	case -1: stainfo = "卡片类型不对";
	case -2: stainfo = "无卡";
	case -3: stainfo = "有卡未上电";
	case -4: stainfo = "卡片无应答";
	case -5: stainfo = "BCC校验错误";
	case -6: stainfo = "接收超时";
	case -7: stainfo = "执行失败";
	case -8: stainfo = "卡片位置错误";
	case -9: stainfo = "设置失败";
	case -11: stainfo = "读卡器连接错误";
	case -12: stainfo = "未建立连接（没有执行打开设备函数）";
	case -13: stainfo = "（动态库）不支持该命令";
	case -14: stainfo = "（发给动态库的）命令参数错误";
	case -15: stainfo = "信息校验和出错";
	case -16: stainfo = "卡片上电失败";
	case -17: stainfo = "卡片复位失败";
	case -18: stainfo = "卡片下电失败";
	}
	m_DebuggerEdit11.SetWindowText(stainfo);//将执行状态写入编辑框内
}


void CDebugger::OnClickedButton21()//获取版本号
{
	unsigned char resp[1024];
	int resp_len;
	int sta = Reader_Version(resp, &resp_len);//获取版本信息函数
	CString verinfo, ver;
	if (sta == 0){//获取信息成功
		verinfo.Empty();
		for (int i = 0; i < resp_len; i++){
			ver.Format(_T("%c"), resp[i]);//转换为ASCII字符串
			verinfo += ver;
		}
		CString tmp;
		tmp.Format(_T("%s"), "成功");
		m_DebuggerEdit21.SetWindowText(verinfo);//写入编辑框
		m_DebuggerEdit23.SetWindowText(tmp);
		canSetLED = true;
	} 
	canSetLED = false;
}


void CDebugger::OnClickedButton22()//获取UID号
{
	// TODO:  在此添加控件通知处理程序代码
	unsigned char uid[1024];
	int uid_len;
	int sta = find_14443(uid, &uid_len); //获取卡片UID函数
	CString uid_cst, cst;
	if (sta == 0){//获取UID成功
		uid_cst.Empty();
		for (int i = 0; i < uid_len; i++)
		{
			cst.Format(_T("%02x"), uid[i]);//转换为16进制字符串
			uid_cst += cst;
		}
		m_DebuggerEdit22.SetWindowText(uid_cst);//uid写入编辑框
		m_DebuggerEdit23.SetWindowText(_T("成功"));//状态框写入
		canGetCardInfo = true;
	}
	else canGetCardInfo = false;

}


void CDebugger::OnClickedButton31()//LED设置
{
	CString dataStr, pointStr;
	char data[1024];
	m_DebuggerEdit31.GetWindowText(dataStr);
	int data_len = dataStr.GetLength();
	CStringToChar(dataStr, data, data_len);
	//strncpy_s(data, (LPSTR)(LPCTSTR)dataStr, sizeof(data));//(LPSTR)(LPCTSTR)dataStr将CString类型变为const char *
	//int data_len = strlen((LPSTR)(LPCTSTR)dataStr);
	m_DebuggerEdit32.GetWindowText(pointStr);
	unsigned char point =(unsigned char)_ttoi(pointStr) + 1;
	int stateNum;
	stateNum = LED(data, data_len, point);//设置 LED 屏显示的数,如果命令执行成功，则返回 0，返回值小于 0 则为状态码，
	CString state;//状态，之后写入编辑框的值
	if (stateNum == 0)	{
		state = "设置成功";
		canSetLED = true;
	}
	else
	{
		state = "设置失败";
		canSetLED = false;
	}
	m_DebuggerEdit33.SetWindowText(state);
}


void CDebugger::OnClickedButton41()//读扇区
{
	UpdateData(TRUE);//更新单选按钮
	CString pwd;
	m_DebuggerEdit51.GetWindowText(pwd);//获取密钥
	if (pwd.IsEmpty()) {
		MessageBox(_T("请输入密钥！"));
		return;
	}
	else if (pwd.GetLength() != 12) {
		MessageBox(_T("密钥长度非法！"));
		return;
	}
	//密钥由CString转unsigned char *
	unsigned char password[8];
	int len_password = 0;
	pwd.MakeUpper();
	HexStr2CharArray(pwd, password, &len_password);
	int sectionNum = ((CComboBox*)GetDlgItem(IDC_COMBO41))->GetCurSel();//获取扇区号
	if (sectionNum == CB_ERR) {
		MessageBox(_T("请选择扇区！"));
		return;
	}
	// 获取块区号
	int blockNum = 0;
	// 读取块
	unsigned char des_data[1024];
	int des_len ;
	/*unsigned char keyType;
	if (m_DebuggerRadio51 == 0)	keyType = 0x0A;
	else if (m_DebuggerRadio51 == 1)	keyType = 0x0B;*/
	for (blockNum = 0; blockNum < 4; blockNum++) {//0-3块数据均读取
		int sta = read_block(sectionNum, blockNum, m_RadioStatus, password, des_data, &des_len);
		if (sta==0) {//读取成功
			// 格式化
			CString block_data, temp;
			block_data.Empty();
			for (int i = 0; i < des_len; i++) {
				temp.Format(_T("%02x"), des_data[i]);//将unsigned char *转换为CString
				block_data += temp;
			}
			// 根据块号设置对应的编辑框
			switch (blockNum) {
			case 0:
				m_DebuggerEdit41.SetWindowText(block_data);
				break;
			case 1:
				m_DebuggerEdit42.SetWindowText(block_data);
				break;
			case 2:
				m_DebuggerEdit43.SetWindowText(block_data);
				break;
			default:
				// 若选择的是块3，则填入编辑框时要将数组拆分成三个部分，第一部分是6个字节，第二部分是4个字节，第三部分是6个字节；
				m_DebuggerEdit45.SetWindowText(block_data.Left(12));
				m_DebuggerEdit46.SetWindowText(block_data.Mid(12, 8));
				m_DebuggerEdit47.SetWindowText(block_data.Right(12));
				break;

			}
			// 更新状态栏为成功
			canIO = true;
			m_DebuggerEdit44.SetWindowText(_T("读取扇区成功"));
		}
		else {
			// 置空全部，更新状态栏为失败
			m_DebuggerEdit41.SetWindowText(_T(""));
			m_DebuggerEdit42.SetWindowText(_T(""));
			m_DebuggerEdit43.SetWindowText(_T(""));
			m_DebuggerEdit45.SetWindowText(_T(""));
			m_DebuggerEdit46.SetWindowText(_T(""));
			m_DebuggerEdit47.SetWindowText(_T(""));
			canIO = false;
			CString stainfo;
			switch (sta){//判断执行状态
			//case 0: stainfo = "执行成功";
			case -1: stainfo = "卡片类型不对";
			case -2: stainfo = "无卡";
			case -3: stainfo = "有卡未上电";
			case -4: stainfo = "卡片无应答";
			case -5: stainfo = "BCC校验错误";
			case -6: stainfo = "接收超时";
			case -7: stainfo = "执行失败";
			case -8: stainfo = "卡片位置错误";
			case -9: stainfo = "设置失败";
			case -11: stainfo = "读卡器连接错误";
			case -12: stainfo = "未建立连接（没有执行打开设备函数）";
			case -13: stainfo = "（动态库）不支持该命令";
			case -14: stainfo = "（发给动态库的）命令参数错误";
			case -15: stainfo = "信息校验和出错";
			case -16: stainfo = "卡片上电失败";
			case -17: stainfo = "卡片复位失败";
			case -18: stainfo = "卡片下电失败";
			}
			m_DebuggerEdit44.SetWindowText(stainfo);
			//m_DebuggerEdit44.SetWindowText(_T("读取扇区异常"));
		}
	}
	return;
}


void CDebugger::OnClickedButton42()//读块
{
	UpdateData(TRUE);
	/*if (m_DebuggerRadio51 != 0&&m_DebuggerRadio51!=1) {
	MessageBox(_T("请选择密钥类型！"));
	return;
	}*/
	CString pwd;
	m_DebuggerEdit51.GetWindowText(pwd);
	if (pwd.IsEmpty()) {
		MessageBox(_T("请输入密钥！"));
		return;
	}
	else if (pwd.GetLength() != 12) {
		MessageBox(_T("密钥长度非法！"));
		return;
	}
	unsigned char password[8];
	int len_password = 0;
	pwd.MakeUpper();
	HexStr2CharArray(pwd, password, &len_password);
	//获取扇区
	int sectionNum = ((CComboBox*)GetDlgItem(IDC_COMBO41))->GetCurSel();
	if (sectionNum == CB_ERR) {
		MessageBox(_T("请选择扇区！"));
		return;
	}
	// 获取块区号
	int blockNum = ((CComboBox*)GetDlgItem(IDC_COMBO42))->GetCurSel();
	if (blockNum == CB_ERR) {
		MessageBox(_T("请选择块区"));
		return;
	}
	// 读取块
	unsigned char des_data[1024];
	int des_len ;
	/*unsigned char keyType;
	if (m_DebuggerRadio51 == 0)	keyType = 0x0A;
	else if (m_DebuggerRadio51 == 1)	keyType = 0x0B;*/
	if (read_block(sectionNum, blockNum, m_RadioStatus, password, des_data, &des_len) == IFD_OK) {
		// 格式化
		CString block_data, temp;
		block_data.Empty();
		for (int i = 0; i < des_len; i++) {
			temp.Format(_T("%02x"), des_data[i]);//unsigned char*转为CString
			block_data += temp;
		}
		// 根据块号设置对应编辑框，同时清空其他编辑框
		switch (blockNum) {
		case 0:
			m_DebuggerEdit41.SetWindowText(block_data);
			m_DebuggerEdit42.SetWindowText(_T(""));
			m_DebuggerEdit43.SetWindowText(_T(""));
			break;
		case 1:
			m_DebuggerEdit42.SetWindowText(block_data);
			m_DebuggerEdit41.SetWindowText(_T(""));
			m_DebuggerEdit43.SetWindowText(_T(""));
			break;
		case 2:
			m_DebuggerEdit41.SetWindowText(_T(""));
			m_DebuggerEdit42.SetWindowText(_T(""));
			m_DebuggerEdit43.SetWindowText(block_data);
			break;
		default:
			m_DebuggerEdit45.SetWindowText(block_data.Left(12));
			m_DebuggerEdit46.SetWindowText(block_data.Mid(12, 8));
			m_DebuggerEdit47.SetWindowText(block_data.Right(12));
			break;
		}
		// 更新状态栏为成功
		canIO = true;
		m_DebuggerEdit44.SetWindowText(_T("读取块成功"));
	}
	else {
		// 置空全部，更新状态栏为失败
		switch (blockNum){
		case 0:
			m_DebuggerEdit41.SetWindowText(_T(""));
			break;
		case 1:
			m_DebuggerEdit42.SetWindowText(_T(""));
			break;
		case 2:
			m_DebuggerEdit43.SetWindowText(_T(""));
			break;
		default:
			m_DebuggerEdit45.SetWindowText(_T(""));
			m_DebuggerEdit46.SetWindowText(_T(""));
			m_DebuggerEdit47.SetWindowText(_T(""));
			break;
		}
		canIO = false;
		m_DebuggerEdit44.SetWindowText(_T("读取块异常"));
	}
}


void CDebugger::OnClickedButton43()//写块
{
	UpdateData(TRUE);
	/*if (m_DebuggerRadio51 != 0&&m_DebuggerRadio51!=1) {
	MessageBox(_T("请选择密钥类型！"));
	return;
	}*/
	CString pwd;
	m_DebuggerEdit51.GetWindowText(pwd);
	if (pwd.IsEmpty()) {
		MessageBox(_T("请输入密钥！"));
		return;
	}
	else if (pwd.GetLength() != 12) {
		MessageBox(_T("密钥长度非法！"));
		return;
	}
	unsigned char password[8];
	int len_password = 0;
	pwd.MakeUpper();
	HexStr2CharArray(pwd, password, &len_password);
	//获取扇区号
	int sectionNum = ((CComboBox*)GetDlgItem(IDC_COMBO41))->GetCurSel();
	if (sectionNum == CB_ERR) {
		MessageBox(_T("请选择扇区！"));
		return;
	}
	// 获取块区号
	int blockNum = ((CComboBox*)GetDlgItem(IDC_COMBO42))->GetCurSel();
	if (blockNum == CB_ERR) {
		MessageBox(_T("请选择块区"));
		return;
	}
	// 根据块号获取内容
	CString block_data;
	if (blockNum == 0) {
		m_DebuggerEdit41.GetWindowText(block_data);
		if (block_data.GetLength() % 2 == 1)	block_data = _T("0") + block_data;//若是字符串长度为奇数，要在字符串的最前面补“0”
	}
	else if (blockNum == 1) {
		m_DebuggerEdit42.GetWindowText(block_data);
		if (block_data.GetLength() % 2 == 1)	block_data = _T("0") + block_data;
	}
	else if (blockNum == 2) {
		m_DebuggerEdit43.GetWindowText(block_data);
		if (block_data.GetLength() % 2 == 1)	block_data = _T("0") + block_data;
	}
	else if (blockNum == 3) {
		m_DebuggerEdit45.GetWindowText(block_data);
		if (block_data.GetLength() < 12) {
			for (int i = block_data.GetLength(); i<12; i++) {
				block_data = _T("0") + block_data;
			}
		}
		CString tmp;
		m_DebuggerEdit46.GetWindowText(tmp);
		block_data = block_data + tmp;
		CString tmp1;
		m_DebuggerEdit47.GetWindowText(tmp1);
		block_data = block_data + tmp1;//选择块3，则要将块3的三段数据拼接起来
	}

	if (block_data.GetLength() > 32) {
		MessageBox(_T("写入信息数据过长"));
		return;
	}

	// 类型转换
	//unsigned char* src_data = (unsigned char*)(LPCTSTR)block_data;
	//int len_data = sizeof(src_data);
	//类型转换
	unsigned char src_data[200];
	int len_data = 0;
	HexStr2CharArray(block_data, src_data, &len_data);
	/*unsigned char keyType;
	if (m_DebuggerRadio51 == 0)	keyType = 0x0A;
	else if (m_DebuggerRadio51 == 1)	keyType = 0x0B;*/
	// 写入块
	if (write_block(blockNum, sectionNum, m_RadioStatus, password, src_data, len_data) == IFD_OK) {
		canIO = true;
		m_DebuggerEdit44.SetWindowText(_T("写入块成功"));
	}
	else {
		canIO = false;
		m_DebuggerEdit44.SetWindowText(_T("写入块失败"));
	}
}


void CDebugger::OnClickedButton51()//获取默认密码
{
	CString key;
	key = "FFFFFFFFFFFF"; //默认密码
	m_DebuggerEdit51.SetWindowText(key); //写入编辑框
}


void CDebugger::OnClickedRadio51()//单选1密钥设置
{
	UpdateData(TRUE);
	m_RadioStatus = 0x0A;
}

void CDebugger::OnClickedRadio52()//单选1密钥设置
{
	UpdateData(TRUE);
	m_RadioStatus = 0x0B;
}


HBRUSH CDebugger::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID()) {
	case IDC_EDIT11:
		if (this->isDeviceOpen)
			pDC->SetTextColor(BLUE);//开启成功字体为蓝
		else
			pDC->SetTextColor(RED);//失败字体为红，RED,BLUE,BLACK在前面都有定义
		break;
	case IDC_EDIT23:
		if (this->canGetCardInfo)
			pDC->SetTextColor(BLUE);
		else
			pDC->SetTextColor(RED);
		break;
	case IDC_EDIT33:
		if (this->canSetLED)
			pDC->SetTextColor(BLUE);
		else
			pDC->SetTextColor(RED);
		break;
	case IDC_EDIT44:			if (this->canIO)
		pDC->SetTextColor(BLUE);
									else
										pDC->SetTextColor(RED);
		break;
	default:
		pDC->SetTextColor(BLACK);
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
