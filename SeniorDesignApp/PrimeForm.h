#pragma once
#include "afxcmn.h"


// CPrimeForm form view

class CPrimeForm : public CFormView
{
	DECLARE_DYNCREATE(CPrimeForm)

protected:
	CPrimeForm();           // protected constructor used by dynamic creation
	virtual ~CPrimeForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRIMEFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
public:
	int TestSensorID; //id of sensor that were testing (0 if not testing)
	int TestCount; //Seconds to wait for ping back from sensor were testing
	int updateCount; 
	int MaxSensorID();

	afx_msg void OnUsersViewusers();
	afx_msg void OnAddUser();
	afx_msg void OnUsersDeleteuser();
	CListCtrl mViewSensors;
	afx_msg void OnButtonRefresh();
	void ResetListControl();
	void FillSensorTable();
	void FillAlertTable();
	afx_msg void OnAddSensor();
	afx_msg void OnSensorsDeleteuser();
	afx_msg void OnSensorsConfiguresensor();
	afx_msg void OnSensorsTestsensor();
	CListCtrl m_ViewAlerts;
	afx_msg void OnButtonAlerts();
	afx_msg void OnButtonUsers();
	afx_msg void OnDebugSmstest();
	int sendSMS(char const* message);
	afx_msg void OnDebugLedswitch();
	afx_msg void OnSensorsUpdatesensors();
	afx_msg void OnAlertsViewalerts();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


