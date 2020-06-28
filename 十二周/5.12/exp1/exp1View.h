
// exp1View.h : Cexp1View 类的接口
//

#pragma once

class Cexp1Set;

class Cexp1View : public CRecordView
{
protected: // 仅从序列化创建
	Cexp1View();
	DECLARE_DYNCREATE(Cexp1View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_EXP1_FORM };
#endif
	Cexp1Set* m_pSet;

// 特性
public:
	Cexp1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~Cexp1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	CRect rect;
	CString picturePath;
	afx_msg void OnRecordPrev();
	afx_msg void OnRecordNext();
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnRecordFirst();
	afx_msg void OnRecordLast();
};

#ifndef _DEBUG  // exp1View.cpp 中的调试版本
inline Cexp1Doc* Cexp1View::GetDocument() const
   { return reinterpret_cast<Cexp1Doc*>(m_pDocument); }
#endif

