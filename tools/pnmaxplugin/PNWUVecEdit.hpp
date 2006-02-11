#pragma once


// Boîte de dialogue PNWUVecEdit

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNWUVecEdit : public CDialog
{
  DECLARE_DYNAMIC(PNWUVecEdit)

public:
  PNWUVecEdit(Point3& point, CWnd* pParent = NULL);   // constructeur standard
  virtual ~PNWUVecEdit();

  // Données de boîte de dialogue
  enum { IDD = IDD_UTILS_VEDIT };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge DDX/DDV

  DECLARE_MESSAGE_MAP()
private:
  Point3& _point;

  void			_setValue(int id, float f);
  void		  	_setVector(const Point3& vec);
  float 	  	_getValue(int id);
  Point3		_getVector();

  void			_enableFields(BOOL enable);
public:
  virtual BOOL	OnInitDialog();
  afx_msg void	OnBnClickedOk();
  afx_msg void	OnBnClickedRbFdefault();
  afx_msg void	OnBnClickedRbRdefault();
  afx_msg void	OnBnClickedRbTdefault();
  afx_msg void	OnBnClickedRbCustom();
};

//////////////////////////////////////////////////////////////////////////
};
