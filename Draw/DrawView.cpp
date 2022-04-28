
// DrawView.cpp: CDrawView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FREE, &CDrawView::OnFree)
	ON_COMMAND(ID_LINE, &CDrawView::OnLine)
	ON_COMMAND(ID_RECT, &CDrawView::OnRect)
	ON_COMMAND(ID_ELLIPSE, &CDrawView::OnEllipse)
END_MESSAGE_MAP()

// CDrawView 생성/소멸

CDrawView::CDrawView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	mObjType = 0;
}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDrawView 그리기

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
/*	CPen p;
	COLORREF col;
	col = RGB(255, 0, 0);
	p.CreatePen(PS_SOLID, 5, col);
	pDC->SelectObject(&p);
	pDC->Rectangle(100, 100, 300, 200);*/

	CPoint t1, t2;
	for (int i = 0; i < pDoc->mObjCnt; i++) {
		for (int j = 0; j < pDoc->mObj[i].pt_cnt - 1; j++) {
			t1.x = pDoc->mObj[i].pt->x[j];
			t1.y = pDoc->mObj[i].pt->y[j];
			t2.x = pDoc->mObj[i].pt->x[j+1];
			t2.y = pDoc->mObj[i].pt->y[j+1];
			DrawPT(t1, t2, pDoc->mObj[i].ob_type);
		}
	}
}


// CDrawView 진단

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView 메시지 처리기

CPoint mp, mp_r;
void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mp = point;
	if (mObjType == 0) {
		CDrawDoc* pd = GetDocument();
		pd->mObj[pd->mObjCnt].pt = (PT *)malloc(sizeof(PT));
	}
	CView::OnLButtonDown(nFlags, point);
}


void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDrawDoc* pd = GetDocument();
	pd->mObj[pd->mObjCnt].ob_type = mObjType;
	pd->mObj[pd->mObjCnt].pt_cnt = pd->mPTCnt;
	if (pd->mObjCnt < 100) pd->mObjCnt++;
	if (pd->mPTCnt < 1000) pd->mPTCnt = 0;
	CView::OnLButtonUp(nFlags, point);
}
void CDrawView::DrawPT(CPoint p1, CPoint p2, int opt)
{
	CClientDC  dc(this);
	CPen p;
	if (opt == 1) {
		p.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	}
	dc.SelectObject(&p);
	dc.MoveTo(p1);
	dc.LineTo(p2);
}

void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDrawDoc* pd = GetDocument();
	if (nFlags & MK_LBUTTON) {
		if (mObjType == 0) {
			DrawPT(mp, point, 0);
			mp = point;
			pd->mObj[pd->mObjCnt].pt->x[pd->mPTCnt] = point.x;
			pd->mObj[pd->mObjCnt].pt->y[pd->mPTCnt] = point.y;
			pd->mPTCnt++;
		}
	}
/*	else if (nFlags & MK_RBUTTON) {
		DrawPT(mp_r, point, 1);
		mp_r = point;
		pd->pt[pd->LineCnt].x[pd->PTCnt] = point.x;
		pd->pt[pd->LineCnt].y[pd->PTCnt] = point.y;
		pd->PTCnt++;
	}*/
	CView::OnMouseMove(nFlags, point);
}


void CDrawView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// mp_r = point;
	CView::OnRButtonDown(nFlags, point);
}


void CDrawView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
/*	CDrawDoc* pd = GetDocument();
	pd->pt[pd->LineCnt].line_type = 1;
	pd->pt[pd->LineCnt].pt_cnt = pd->PTCnt;
	if (pd->LineCnt < 100) pd->LineCnt++;
	if (pd->PTCnt < 1000) pd->PTCnt = 0;*/
	CView::OnRButtonUp(nFlags, point);
}


void CDrawView::OnFree()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CDrawView::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CDrawView::OnRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CDrawView::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
