#pragma once

#define TIMEFORMAT _T("%Y/%m/%d %H:%M:%S")

class CRecordHelper
{
	//DECLARE_DYNAMIC(CRecordHelper)
public:
	CRecordHelper(CString saveFileName);
	~CRecordHelper(){};

	//电子钱包充值，消费操作记录保存
	void saveRecharges(CString vid, CString account, long Remainings, CString con, CString result);
	void saveConsumptions(CString vid, CString account, long Remainings, CString con, CString result);

	//从record.txt加载记录显示到编辑框
	CString LoadRecords(void);

	//清空历史记录
	BOOL EmptyRecords(void);

private:
	//保存历史记录文件名
	CString mSaveFile;

};
