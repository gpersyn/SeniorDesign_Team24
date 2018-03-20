
// SeniorDesignAppView.h : interface of the CSeniorDesignAppView class
//

#pragma once


class CSeniorDesignAppView : public CView
{
protected: // create from serialization only
	CSeniorDesignAppView();
	DECLARE_DYNCREATE(CSeniorDesignAppView)

// Attributes
public:
	CSeniorDesignAppDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSeniorDesignAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddUser();
	afx_msg void OnAddSensor();

//Custom Variables
private:
	int num_Row{ 2 }; //Number of rows in table
	int num_Col = 5; //Number of cols in table
	double table_size{ 1 }; //Multiplier used to determine size of table, Shouldn't be less than 1
	CString m_SerialDebug_Write_View{"Test"};
	CString m_SerialDebug_Read_View;
	CButton m_SerialDebug_Send_View; 
	char *charInputArray;

	//Sensor Value Variables
	CString Sensor_ID;
	CString Sensor_Status;
	CString CO_Value;
	CString Methane_Value;
	CString Propane_Value;

public:
	afx_msg void OnDebugAddrow();
	afx_msg void OnDebugRemoverow();
	afx_msg void OnDebugSerialDebug();
	afx_msg void OnDebugLightswitch();
	afx_msg void OnDebugLedswitch();
	afx_msg void OnButtonTablesizeIncrease();
	afx_msg void OnButtonTablesizeDecrease();

	//Custom Functions
	void DecodeSerialInput();
};

#ifndef _DEBUG  // debug version in SeniorDesignAppView.cpp
inline CSeniorDesignAppDoc* CSeniorDesignAppView::GetDocument() const
   { return reinterpret_cast<CSeniorDesignAppDoc*>(m_pDocument); }
#endif

