// PNWUVecEdit.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "pnmaxplugin.h"

#include "PNWUVecEdit.hpp"


// Boîte de dialogue PNWUVecEdit

IMPLEMENT_DYNAMIC(PNWUVecEdit, CDialog)
PNWUVecEdit::PNWUVecEdit(Point3& point, CWnd* pParent /*=NULL*/)
: CDialog(PNWUVecEdit::IDD, pParent), _point(point)
{
}

PNWUVecEdit::~PNWUVecEdit()
{
}

//////////////////////////////////////////////////////////////////////////

void
PNWUVecEdit::_setValue(int id, float f)
{ 
  std::ostringstream	os;
  os << f;

  SetDlgItemText(id, os.str().c_str());
}

void
PNWUVecEdit::_setVector(const Point3& vec)
{
  _setValue(IDC_T_X, vec.x);
  _setValue(IDC_T_Y, vec.y);
  _setValue(IDC_T_Z, vec.z);
}

float
PNWUVecEdit::_getValue(int id)
{
  CString cstr;

  GetDlgItemText(id, cstr);
  std::istringstream	is(cstr.GetString());

  float  f;
  is >> f;

  return f;
}

Point3
PNWUVecEdit::_getVector()
{
  return Point3(
	_getValue(IDC_T_X),
	_getValue(IDC_T_Y),
	_getValue(IDC_T_Z));
}

//////////////////////////////////////////////////////////////////////////

void
PNWUVecEdit::_enableFields(BOOL enable)
{
  GetDlgItem(IDC_T_X)->EnableWindow(enable);
  GetDlgItem(IDC_T_Y)->EnableWindow(enable);
  GetDlgItem(IDC_T_Z)->EnableWindow(enable);
}

//////////////////////////////////////////////////////////////////////////

void
PNWUVecEdit::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PNWUVecEdit, CDialog)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
  ON_BN_CLICKED(IDC_RB_FDEFAULT, OnBnClickedRbFdefault)
  ON_BN_CLICKED(IDC_RB_RDEFAULT, OnBnClickedRbRdefault)
  ON_BN_CLICKED(IDC_RB_TDEFAULT, OnBnClickedRbTdefault)
  ON_BN_CLICKED(IDC_RB_CUSTOM, OnBnClickedRbCustom)
END_MESSAGE_MAP()


// Gestionnaires de messages PNWUVecEdit

BOOL
PNWUVecEdit::OnInitDialog()
{
  if (CDialog::OnInitDialog() == FALSE)
	return FALSE;

  int btToClick = IDC_RB_CUSTOM;

  if (_point == Point3(0.0f, 1.0f, 0.0f))
  {
	btToClick = IDC_RB_FDEFAULT;
	OnBnClickedRbFdefault();
  }
  else if (_point == Point3(1.0f, 0.0f, 0.0f))
  {
	btToClick = IDC_RB_RDEFAULT;
	OnBnClickedRbRdefault();
  }
  else if (_point == Point3(0.0f, 0.0f, 1.0f))
  {
	btToClick = IDC_RB_TDEFAULT;
	OnBnClickedRbTdefault();
  }

  CheckRadioButton(IDC_RB_FDEFAULT, IDC_RB_CUSTOM, btToClick);

  _setVector(_point);

  return TRUE;
}

void PNWUVecEdit::OnBnClickedRbFdefault()
{
  _enableFields(FALSE);

  _setVector(Point3(0.0f, 1.0f, 0.0f));
}

void PNWUVecEdit::OnBnClickedRbRdefault()
{
  _enableFields(FALSE);

  _setVector(Point3(1.0f, 0.0f, 0.0f));
}

void PNWUVecEdit::OnBnClickedRbTdefault()
{
  _enableFields(FALSE);

  _setVector(Point3(0.0f, 0.0f, 1.0f));
}

void PNWUVecEdit::OnBnClickedRbCustom()
{
  _enableFields(TRUE);
}

void PNWUVecEdit::OnBnClickedOk()
{
  _point = _getVector();
}

