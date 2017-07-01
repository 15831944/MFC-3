// Debugger.cpp : ʵ���ļ�
//

#pragma comment(lib,"./libs/ZM124U.lib");
#include "./libs/ZM124U.h"
#include "stdafx.h"
#include "MFCApplication1.h"
#include "Debugger.h"
#include "afxdialogex.h"


// CDebugger �Ի���
#define RED RGB(255, 0, 0)
#define BLUE RGB(0, 0, 255)
#define BLACK RGB(0, 0, 0)
IMPLEMENT_DYNAMIC(CDebugger, CDialogEx)

CDebugger::CDebugger(CWnd* pParent /*=NULL*/)
: CDialogEx(CDebugger::IDD, pParent)
//, m_DebuggerRadio51(0)//Ĭ��Ϊ��һ��radio
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

//������CStringתchar*
void CDebugger::CStringToChar(const CString& str, char* character, int str_len) {
	int i;
	for (i = 0; i < str_len; i++) {
		character[i] = str[i];
	}
	character[i] = '\0';
	return;
}
//CStringתunsigned char *,���岽�軹�ǲ���PPT�ϴ���
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



// CDebugger ��Ϣ�������


void CDebugger::OnClickedButton11()//�����豸
{
	CString stainfo;
	int sta = IDD_PowerOn();//�����豸����
	if (sta == 0)	isDeviceOpen = true;//��ʾ�����豸�ɹ�
	else isDeviceOpen = false;//��ʾ�����豸ʧ��
	switch(sta){//�ж�ִ��״̬
	case 0: stainfo = "ִ�гɹ�";
	case -1: stainfo = "��Ƭ���Ͳ���";
	case -2: stainfo = "�޿�";
	case -3: stainfo = "�п�δ�ϵ�";
	case -4: stainfo = "��Ƭ��Ӧ��";
	case -5: stainfo = "BCCУ�����";
	case -6: stainfo = "���ճ�ʱ";
	case -7: stainfo = "ִ��ʧ��";
	case -8: stainfo = "��Ƭλ�ô���";
	case -9: stainfo = "����ʧ��";
	case -11: stainfo = "���������Ӵ���";
	case -12: stainfo = "δ�������ӣ�û��ִ�д��豸������";
	case -13: stainfo = "����̬�⣩��֧�ָ�����";
	case -14: stainfo = "��������̬��ģ������������";
	case -15: stainfo = "��ϢУ��ͳ���";
	case -16: stainfo = "��Ƭ�ϵ�ʧ��";
	case -17: stainfo = "��Ƭ��λʧ��";
	case -18: stainfo = "��Ƭ�µ�ʧ��";
	}
	m_DebuggerEdit11.SetWindowText(stainfo);//��ִ��״̬д��༭����
}


void CDebugger::OnClickedButton21()//��ȡ�汾��
{
	unsigned char resp[1024];
	int resp_len;
	int sta = Reader_Version(resp, &resp_len);//��ȡ�汾��Ϣ����
	CString verinfo, ver;
	if (sta == 0){//��ȡ��Ϣ�ɹ�
		verinfo.Empty();
		for (int i = 0; i < resp_len; i++){
			ver.Format(_T("%c"), resp[i]);//ת��ΪASCII�ַ���
			verinfo += ver;
		}
		CString tmp;
		tmp.Format(_T("%s"), "�ɹ�");
		m_DebuggerEdit21.SetWindowText(verinfo);//д��༭��
		m_DebuggerEdit23.SetWindowText(tmp);
		canSetLED = true;
	} 
	canSetLED = false;
}


void CDebugger::OnClickedButton22()//��ȡUID��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	unsigned char uid[1024];
	int uid_len;
	int sta = find_14443(uid, &uid_len); //��ȡ��ƬUID����
	CString uid_cst, cst;
	if (sta == 0){//��ȡUID�ɹ�
		uid_cst.Empty();
		for (int i = 0; i < uid_len; i++)
		{
			cst.Format(_T("%02x"), uid[i]);//ת��Ϊ16�����ַ���
			uid_cst += cst;
		}
		m_DebuggerEdit22.SetWindowText(uid_cst);//uidд��༭��
		m_DebuggerEdit23.SetWindowText(_T("�ɹ�"));//״̬��д��
		canGetCardInfo = true;
	}
	else canGetCardInfo = false;

}


void CDebugger::OnClickedButton31()//LED����
{
	CString dataStr, pointStr;
	char data[1024];
	m_DebuggerEdit31.GetWindowText(dataStr);
	int data_len = dataStr.GetLength();
	CStringToChar(dataStr, data, data_len);
	//strncpy_s(data, (LPSTR)(LPCTSTR)dataStr, sizeof(data));//(LPSTR)(LPCTSTR)dataStr��CString���ͱ�Ϊconst char *
	//int data_len = strlen((LPSTR)(LPCTSTR)dataStr);
	m_DebuggerEdit32.GetWindowText(pointStr);
	unsigned char point =(unsigned char)_ttoi(pointStr) + 1;
	int stateNum;
	stateNum = LED(data, data_len, point);//���� LED ����ʾ����,�������ִ�гɹ����򷵻� 0������ֵС�� 0 ��Ϊ״̬�룬
	CString state;//״̬��֮��д��༭���ֵ
	if (stateNum == 0)	{
		state = "���óɹ�";
		canSetLED = true;
	}
	else
	{
		state = "����ʧ��";
		canSetLED = false;
	}
	m_DebuggerEdit33.SetWindowText(state);
}


void CDebugger::OnClickedButton41()//������
{
	UpdateData(TRUE);//���µ�ѡ��ť
	CString pwd;
	m_DebuggerEdit51.GetWindowText(pwd);//��ȡ��Կ
	if (pwd.IsEmpty()) {
		MessageBox(_T("��������Կ��"));
		return;
	}
	else if (pwd.GetLength() != 12) {
		MessageBox(_T("��Կ���ȷǷ���"));
		return;
	}
	//��Կ��CStringתunsigned char *
	unsigned char password[8];
	int len_password = 0;
	pwd.MakeUpper();
	HexStr2CharArray(pwd, password, &len_password);
	int sectionNum = ((CComboBox*)GetDlgItem(IDC_COMBO41))->GetCurSel();//��ȡ������
	if (sectionNum == CB_ERR) {
		MessageBox(_T("��ѡ��������"));
		return;
	}
	// ��ȡ������
	int blockNum = 0;
	// ��ȡ��
	unsigned char des_data[1024];
	int des_len ;
	/*unsigned char keyType;
	if (m_DebuggerRadio51 == 0)	keyType = 0x0A;
	else if (m_DebuggerRadio51 == 1)	keyType = 0x0B;*/
	for (blockNum = 0; blockNum < 4; blockNum++) {//0-3�����ݾ���ȡ
		int sta = read_block(sectionNum, blockNum, m_RadioStatus, password, des_data, &des_len);
		if (sta==0) {//��ȡ�ɹ�
			// ��ʽ��
			CString block_data, temp;
			block_data.Empty();
			for (int i = 0; i < des_len; i++) {
				temp.Format(_T("%02x"), des_data[i]);//��unsigned char *ת��ΪCString
				block_data += temp;
			}
			// ���ݿ�����ö�Ӧ�ı༭��
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
				// ��ѡ����ǿ�3��������༭��ʱҪ�������ֳ��������֣���һ������6���ֽڣ��ڶ�������4���ֽڣ�����������6���ֽڣ�
				m_DebuggerEdit45.SetWindowText(block_data.Left(12));
				m_DebuggerEdit46.SetWindowText(block_data.Mid(12, 8));
				m_DebuggerEdit47.SetWindowText(block_data.Right(12));
				break;

			}
			// ����״̬��Ϊ�ɹ�
			canIO = true;
			m_DebuggerEdit44.SetWindowText(_T("��ȡ�����ɹ�"));
		}
		else {
			// �ÿ�ȫ��������״̬��Ϊʧ��
			m_DebuggerEdit41.SetWindowText(_T(""));
			m_DebuggerEdit42.SetWindowText(_T(""));
			m_DebuggerEdit43.SetWindowText(_T(""));
			m_DebuggerEdit45.SetWindowText(_T(""));
			m_DebuggerEdit46.SetWindowText(_T(""));
			m_DebuggerEdit47.SetWindowText(_T(""));
			canIO = false;
			CString stainfo;
			switch (sta){//�ж�ִ��״̬
			//case 0: stainfo = "ִ�гɹ�";
			case -1: stainfo = "��Ƭ���Ͳ���";
			case -2: stainfo = "�޿�";
			case -3: stainfo = "�п�δ�ϵ�";
			case -4: stainfo = "��Ƭ��Ӧ��";
			case -5: stainfo = "BCCУ�����";
			case -6: stainfo = "���ճ�ʱ";
			case -7: stainfo = "ִ��ʧ��";
			case -8: stainfo = "��Ƭλ�ô���";
			case -9: stainfo = "����ʧ��";
			case -11: stainfo = "���������Ӵ���";
			case -12: stainfo = "δ�������ӣ�û��ִ�д��豸������";
			case -13: stainfo = "����̬�⣩��֧�ָ�����";
			case -14: stainfo = "��������̬��ģ������������";
			case -15: stainfo = "��ϢУ��ͳ���";
			case -16: stainfo = "��Ƭ�ϵ�ʧ��";
			case -17: stainfo = "��Ƭ��λʧ��";
			case -18: stainfo = "��Ƭ�µ�ʧ��";
			}
			m_DebuggerEdit44.SetWindowText(stainfo);
			//m_DebuggerEdit44.SetWindowText(_T("��ȡ�����쳣"));
		}
	}
	return;
}


void CDebugger::OnClickedButton42()//����
{
	UpdateData(TRUE);
	/*if (m_DebuggerRadio51 != 0&&m_DebuggerRadio51!=1) {
	MessageBox(_T("��ѡ����Կ���ͣ�"));
	return;
	}*/
	CString pwd;
	m_DebuggerEdit51.GetWindowText(pwd);
	if (pwd.IsEmpty()) {
		MessageBox(_T("��������Կ��"));
		return;
	}
	else if (pwd.GetLength() != 12) {
		MessageBox(_T("��Կ���ȷǷ���"));
		return;
	}
	unsigned char password[8];
	int len_password = 0;
	pwd.MakeUpper();
	HexStr2CharArray(pwd, password, &len_password);
	//��ȡ����
	int sectionNum = ((CComboBox*)GetDlgItem(IDC_COMBO41))->GetCurSel();
	if (sectionNum == CB_ERR) {
		MessageBox(_T("��ѡ��������"));
		return;
	}
	// ��ȡ������
	int blockNum = ((CComboBox*)GetDlgItem(IDC_COMBO42))->GetCurSel();
	if (blockNum == CB_ERR) {
		MessageBox(_T("��ѡ�����"));
		return;
	}
	// ��ȡ��
	unsigned char des_data[1024];
	int des_len ;
	/*unsigned char keyType;
	if (m_DebuggerRadio51 == 0)	keyType = 0x0A;
	else if (m_DebuggerRadio51 == 1)	keyType = 0x0B;*/
	if (read_block(sectionNum, blockNum, m_RadioStatus, password, des_data, &des_len) == IFD_OK) {
		// ��ʽ��
		CString block_data, temp;
		block_data.Empty();
		for (int i = 0; i < des_len; i++) {
			temp.Format(_T("%02x"), des_data[i]);//unsigned char*תΪCString
			block_data += temp;
		}
		// ���ݿ�����ö�Ӧ�༭��ͬʱ��������༭��
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
		// ����״̬��Ϊ�ɹ�
		canIO = true;
		m_DebuggerEdit44.SetWindowText(_T("��ȡ��ɹ�"));
	}
	else {
		// �ÿ�ȫ��������״̬��Ϊʧ��
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
		m_DebuggerEdit44.SetWindowText(_T("��ȡ���쳣"));
	}
}


void CDebugger::OnClickedButton43()//д��
{
	UpdateData(TRUE);
	/*if (m_DebuggerRadio51 != 0&&m_DebuggerRadio51!=1) {
	MessageBox(_T("��ѡ����Կ���ͣ�"));
	return;
	}*/
	CString pwd;
	m_DebuggerEdit51.GetWindowText(pwd);
	if (pwd.IsEmpty()) {
		MessageBox(_T("��������Կ��"));
		return;
	}
	else if (pwd.GetLength() != 12) {
		MessageBox(_T("��Կ���ȷǷ���"));
		return;
	}
	unsigned char password[8];
	int len_password = 0;
	pwd.MakeUpper();
	HexStr2CharArray(pwd, password, &len_password);
	//��ȡ������
	int sectionNum = ((CComboBox*)GetDlgItem(IDC_COMBO41))->GetCurSel();
	if (sectionNum == CB_ERR) {
		MessageBox(_T("��ѡ��������"));
		return;
	}
	// ��ȡ������
	int blockNum = ((CComboBox*)GetDlgItem(IDC_COMBO42))->GetCurSel();
	if (blockNum == CB_ERR) {
		MessageBox(_T("��ѡ�����"));
		return;
	}
	// ���ݿ�Ż�ȡ����
	CString block_data;
	if (blockNum == 0) {
		m_DebuggerEdit41.GetWindowText(block_data);
		if (block_data.GetLength() % 2 == 1)	block_data = _T("0") + block_data;//�����ַ�������Ϊ������Ҫ���ַ�������ǰ�油��0��
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
		block_data = block_data + tmp1;//ѡ���3����Ҫ����3����������ƴ������
	}

	if (block_data.GetLength() > 32) {
		MessageBox(_T("д����Ϣ���ݹ���"));
		return;
	}

	// ����ת��
	//unsigned char* src_data = (unsigned char*)(LPCTSTR)block_data;
	//int len_data = sizeof(src_data);
	//����ת��
	unsigned char src_data[200];
	int len_data = 0;
	HexStr2CharArray(block_data, src_data, &len_data);
	/*unsigned char keyType;
	if (m_DebuggerRadio51 == 0)	keyType = 0x0A;
	else if (m_DebuggerRadio51 == 1)	keyType = 0x0B;*/
	// д���
	if (write_block(blockNum, sectionNum, m_RadioStatus, password, src_data, len_data) == IFD_OK) {
		canIO = true;
		m_DebuggerEdit44.SetWindowText(_T("д���ɹ�"));
	}
	else {
		canIO = false;
		m_DebuggerEdit44.SetWindowText(_T("д���ʧ��"));
	}
}


void CDebugger::OnClickedButton51()//��ȡĬ������
{
	CString key;
	key = "FFFFFFFFFFFF"; //Ĭ������
	m_DebuggerEdit51.SetWindowText(key); //д��༭��
}


void CDebugger::OnClickedRadio51()//��ѡ1��Կ����
{
	UpdateData(TRUE);
	m_RadioStatus = 0x0A;
}

void CDebugger::OnClickedRadio52()//��ѡ1��Կ����
{
	UpdateData(TRUE);
	m_RadioStatus = 0x0B;
}


HBRUSH CDebugger::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID()) {
	case IDC_EDIT11:
		if (this->isDeviceOpen)
			pDC->SetTextColor(BLUE);//�����ɹ�����Ϊ��
		else
			pDC->SetTextColor(RED);//ʧ������Ϊ�죬RED,BLUE,BLACK��ǰ�涼�ж���
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
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
