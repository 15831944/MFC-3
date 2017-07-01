// 、、、、、、、、、、、、、、、、、、、、、\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\封装历史记录操作辅助类
#include "stdafx.h"
#include "CRecordHelper.h"

//IMPLEMENT_DYNAMIC

CRecordHelper::CRecordHelper(CString saveFileName)
{
	mSaveFile = saveFileName;
}

void CRecordHelper::saveRecharges(CString vid, CString account, long Remainings, CString con, CString result)
{
	//打开文件
	CFile mFile(this->mSaveFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	//获取当前时间
	CTime curTime = CTime::GetCurrentTime();
	//格式输出
	CString contents;
	contents.Format(_T("卡号：%s\r\n时间：%s\r\n结果：%s\r\n内容：%s\r\n金额：%s\r\n余额：%d\r\n\r\n"), LPCTSTR(vid), LPCTSTR(curTime.Format(TIMEFORMAT)), LPCTSTR(result), LPCTSTR(con), LPCTSTR(account), Remainings);

	//指向文件末尾并写入
	mFile.SeekToEnd();
	mFile.Write(contents, wcslen(contents)*sizeof(wchar_t));
	mFile.Close();
}

void CRecordHelper::saveConsumptions(CString vid, CString account, long Remainings, CString con, CString result)
{
	//打开文件
	CFile mFile(this->mSaveFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	//获取当前时间
	CTime curTime = CTime::GetCurrentTime();
	//格式输出
	CString contents;
	contents.Format(_T("卡号：%s\r\n时间：%s\r\n结果：%s\r\n内容：%s\r\n金额：%s\r\n余额：%d\r\n\r\n"), LPCTSTR(vid), LPCTSTR(curTime.Format(TIMEFORMAT)), LPCTSTR(result), LPCTSTR(con), LPCTSTR(account), Remainings);

	//指向文件末尾并写入
	mFile.SeekToEnd();
	mFile.Write(contents, wcslen(contents)*sizeof(wchar_t));
	mFile.Close();
}

//读取文件记录
CString CRecordHelper::LoadRecords(void)
{
	//打开文件
	CStdioFile mFile(this->mSaveFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead);
	//指向开头并循环读入
	mFile.SeekToBegin();
	CString contents, line, multiLine;
	contents.Empty();
	multiLine.Empty();

	//倒序分段读入
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
	//清空文件
	CFile mFile(this->mSaveFile, CFile::modeCreate | CFile::modeReadWrite);
	mFile.Close();
	return true;
}
