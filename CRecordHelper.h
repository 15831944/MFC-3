#pragma once

#define TIMEFORMAT _T("%Y/%m/%d %H:%M:%S")

class CRecordHelper
{
	//DECLARE_DYNAMIC(CRecordHelper)
public:
	CRecordHelper(CString saveFileName);
	~CRecordHelper(){};

	//����Ǯ����ֵ�����Ѳ�����¼����
	void saveRecharges(CString vid, CString account, long Remainings, CString con, CString result);
	void saveConsumptions(CString vid, CString account, long Remainings, CString con, CString result);

	//��record.txt���ؼ�¼��ʾ���༭��
	CString LoadRecords(void);

	//�����ʷ��¼
	BOOL EmptyRecords(void);

private:
	//������ʷ��¼�ļ���
	CString mSaveFile;

};
