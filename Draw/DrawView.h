
// DrawView.h: CDrawView 클래스의 인터페이스
//

#pragma once


class CDrawView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDrawView() noexcept;
	DECLARE_DYNCREATE(CDrawView)

// 특성입니다.
public:
	CDrawDoc* GetDocument() const;
	int		mObjType;   // 0:free, 1:line, 2:rect, 3:ellipse

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void DrawPT(CPoint p1, CPoint p2, int opt);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFree();
	afx_msg void OnLine();
	afx_msg void OnRect();
	afx_msg void OnEllipse();
};

#ifndef _DEBUG  // DrawView.cpp의 디버그 버전
inline CDrawDoc* CDrawView::GetDocument() const
   { return reinterpret_cast<CDrawDoc*>(m_pDocument); }
#endif

