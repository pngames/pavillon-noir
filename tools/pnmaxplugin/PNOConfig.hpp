#pragma once


// Boîte de dialogue PNOConfig

class PN3DObjectExporter;

class				  PNOConfig : public CDialog
{
  DECLARE_DYNAMIC(PNOConfig)

public:
  PNOConfig(PN3DObjectExporter* object, CWnd* pParent = NULL);   // constructeur standard
  virtual ~PNOConfig();

  // Données de boîte de dialogue
  enum { IDD = IDD_PNO_CONFIG };

protected:
  virtual void			DoDataExchange(CDataExchange* pDX);    // Prise en charge DDX/DDV

  DECLARE_MESSAGE_MAP()
private:
  PN3DObjectExporter*	_object;

  void					_setVector(int id, const Point3& vec);
  void					_setFront(const Point3& vec);
  void					_setRight(const Point3& vec);
  void					_setTop(const Point3& vec);

  Point3				_getVector(int id);
  Point3				_getFront();
  Point3				_getRight();
  Point3				_getTop();

  void					_enableFields(BOOL enable);
public:
  virtual BOOL			OnInitDialog();
  afx_msg void			OnBnClickedOk();
  afx_msg void			OnBnClickedRbDefault();
  afx_msg void			OnBnClickedRb180();
  afx_msg void			OnBnClickedRbCustom();
  afx_msg void OnBnClickedBtFront();
  afx_msg void OnBnClickedBtRight();
  afx_msg void OnBnClickedBtTop();
};
