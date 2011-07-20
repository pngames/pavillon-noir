#pragma once

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNModelExporter;

class PNModelWin : public CDialog
{
	DECLARE_DYNAMIC(PNModelWin)

	PNModelExporter* _model;
public:
	PNModelWin(PNModelExporter *model, CWnd* pParent = NULL);   // constructeur standard
	virtual ~PNModelWin();

public:
	void pnToMFC();
	void mfcToPN();

	virtual BOOL OnInitDialog();

// Données de boîte de dialogue
	enum { IDD = IDD_PNM_CONFIG };
private:
    CListCtrl _materials;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge DDX/DDV

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
	afx_msg void OnBnClickedBegin();
	afx_msg void OnBnClickedEnd();
};

//////////////////////////////////////////////////////////////////////////
};
