// ������������������������������������������\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\��װ��ʷ��¼����������
#include "stdafx.h"
#include "CRecordHelper.h"

//IMPLEMENT_DYNAMIC

CRecordHelper::CRecordHelper(CString saveFileName)
{
	mSaveFile = saveFileName;
}

void CRecordHelper::saveRecharges(CString vid, CString account, long Remainings, CString con, CString result)
{
	//���ļ�
	CFile mFile(this->mSaveFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	//��ȡ��ǰʱ��
	CTime curTime = CTime::GetCurrentTime();
	//��ʽ���
	CString contents;
	contents.Format(_T("���ţ�%s\r\nʱ�䣺%s\r\n�����%s\r\n���ݣ�%s\r\n��%s\r\n��%d\r\n\r\n"), LPCTSTR(vid), LPCTSTR(curTime.Format(TIMEFORMAT)), LPCTSTR(result), LPCTSTR(con), LPCTSTR(account), Remainings);

	//ָ���ļ�ĩβ��д��
	mFile.SeekToEnd();
	mFile.Write(contents, wcslen(contents)*sizeof(wchar_t));
	mFile.Close();
}

void CRecordHelper::saveConsumptions(CString vid, CString account, long Remainings, CString con, CString result)
{
	//���ļ�
	CFile mFile(this->mSaveFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	//��ȡ��ǰʱ��
	CTime curTime = CTime::GetCurrentTime();
	//��ʽ���
	CString contents;
	contents.Format(_T("���ţ�%s\r\nʱ�䣺%s\r\n�����%s\r\n���ݣ�%s\r\n��%s\r\n��%d\r\n\r\n"), LPCTSTR(vid), LPCTSTR(curTime.Format(TIMEFORMAT)), LPCTSTR(result), LPCTSTR(con), LPCTSTR(account), Remainings);

	//ָ���ļ�ĩβ��д��
	mFile.SeekToEnd();
	mFile.Write(contents, wcslen(contents)*sizeof(wchar_t));
	mFile.Close();
}

//��ȡ�ļ���¼
CString CRecordHelper::LoadRecords(void)
{
	//���ļ�
	CStdioFile mFile(this->mSaveFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead);
	//ָ��ͷ��ѭ������
	mFile.SeekToBegin();
	CString contents, line, multiLine;
	contents.Empty();
	multiLine.Empty();

	//����ֶζ���
	while (mFile.ReadString(line)){
		line.Trim();
		if (line.IsEmpty()){
			contents = multiLine + _T("\r\n") + contents;
			multiLine.Empty();

		}
		else{
			multiLine += (line + _T("\r\n"));
		}
	}

	contents = multiLine + _T("\r\n") + contents;
	mFile.Close();
	return contents;
}

BOOL CRecordHelper::EmptyRecords()
{
	//����ļ�
	CFile mFile(this->mSaveFile, CFile::modeCreate | CFile::modeReadWrite);
	mFile.Close();
	return true;
}
