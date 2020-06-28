
// exp1View.cpp : Cexp1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "exp1.h"
#endif

#include "exp1Set.h"
#include "exp1Doc.h"
#include "exp1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cexp1View

IMPLEMENT_DYNCREATE(Cexp1View, CRecordView)

BEGIN_MESSAGE_MAP(Cexp1View, CRecordView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRecordView::OnFilePrintPreview)
	ON_COMMAND(ID_RECORD_PREV, &Cexp1View::OnRecordPrev)
	ON_COMMAND(ID_RECORD_NEXT, &Cexp1View::OnRecordNext)
	ON_COMMAND(ID_RECORD_FIRST, &Cexp1View::OnRecordFirst)
	ON_COMMAND(ID_RECORD_LAST, &Cexp1View::OnRecordLast)
END_MESSAGE_MAP()

// Cexp1View 构造/析构

Cexp1View::Cexp1View()
	: CRecordView(IDD_EXP1_FORM)
	, picturePath(_T(""))
{
	m_pSet = NULL;
	// TODO: 在此处添加构造代码

}

Cexp1View::~Cexp1View()
{
}

void Cexp1View::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// 可以在此处插入 DDX_Field* 函数以将控件“连接”到数据库字段，例如
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// 有关详细信息，请参阅 MSDN 和 ODBC 示例
	DDX_Text(pDX, IDC_EDIT1, m_pSet->column1);
}

BOOL Cexp1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CRecordView::PreCreateWindow(cs);
}

void Cexp1View::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_exp1Set;
	CRecordView::OnInitialUpdate();

}


// Cexp1View 打印

BOOL Cexp1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cexp1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cexp1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// Cexp1View 诊断

#ifdef _DEBUG
void Cexp1View::AssertValid() const
{
	CRecordView::AssertValid();
}

void Cexp1View::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

Cexp1Doc* Cexp1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cexp1Doc)));
	return (Cexp1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cexp1View 数据库支持
CRecordset* Cexp1View::OnGetRecordset()
{

	return m_pSet;
}



// Cexp1View 消息处理程序


void Cexp1View::OnRecordPrev()
{
	m_pSet->MovePrev();

	if (m_pSet->IsBOF())
		m_pSet->MoveFirst();

	//nowPath = m_pSet->column2;
	InvalidateRect(&rect, true);
	RedrawWindow();
	UpdateData(false);	
}


void Cexp1View::OnRecordNext()
{
	// TODO: 在此添加命令处理程序代码
	m_pSet->MoveNext();
	if (m_pSet->IsEOF())
		m_pSet->MoveLast();

	//nowPath = m_pSet->column2;
	InvalidateRect(&rect, true);
	RedrawWindow();
	UpdateData(false);
	// TODO: 在此添加命令处理程序代码
}


void Cexp1View::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 在此添加专用代码和/或调用基类

	CRecordView::OnPrint(pDC, pInfo);
}


void Cexp1View::OnDraw(CDC* /*pDC*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	CWnd *pWnd = GetDlgItem(IDC_STATIC);//IDC_picture为picture控件ID
	pWnd->GetClientRect(&rect);//rc为控件的大小

	CImage img;
	CString s=CString("C:\\Users\\Coisini\\Desktop\\mix\\");
	s += m_pSet->column1;
	
	img.Load(s);
	CDC* pDC = GetDlgItem(IDC_STATIC)->GetDC();


	if (!img.IsNull())
	{


		int w, h, sx, sy;
		float r_ratio = 1.0*rect.Width() / rect.Height();
		float img_ratio = 1.0*img.GetWidth() / img.GetHeight();
		if (r_ratio > img_ratio)
		{
			h = rect.Height();
			w = img_ratio*h;
			sx = (rect.Width() - w) / 2;
			sy = 0;
		}
		else
		{
			w = rect.Width();
			h = w / img_ratio;
			sx = 0;
			sy = (rect.Height() - h) / 2;
		}

		img.Draw(pDC->m_hDC, sx, sy, w, h);
	}//Null

	else
	{

		pDC->TextOutW(20, 20, _T("图片不存在"));
	}
	img.Destroy();
	ReleaseDC(pDC);//释放DC 注意获取后必须释放
}


void Cexp1View::OnRecordFirst()
{
	// TODO: 在此添加命令处理程序代码
	m_pSet->MoveFirst();

	//nowPath = m_pSet->column2;
	InvalidateRect(&rect, true);
	RedrawWindow();
	UpdateData(false);
}


void Cexp1View::OnRecordLast()
{
	// TODO: 在此添加命令处理程序代码
	m_pSet->MoveLast();

	//nowPath = m_pSet->column2;
	InvalidateRect(&rect, true);
	RedrawWindow();
	UpdateData(false);
}
