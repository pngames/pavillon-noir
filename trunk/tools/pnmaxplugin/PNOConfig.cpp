// PNOConfig.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "pnmaxplugin.h"

#include "PN3DObjectExporter.hpp"
#include "PNWUVecEdit.hpp"

#include "PNOConfig.hpp"


// Boîte de dialogue PNOConfig

IMPLEMENT_DYNAMIC(PNOConfig, CDialog)
PNOConfig::PNOConfig(PN3DObjectExporter* object, CWnd* pParent /*=NULL*/)
: CDialog(PNOConfig::IDD, pParent), _object(object)
{

}

PNOConfig::~PNOConfig()
{
}

//////////////////////////////////////////////////////////////////////////

void
PNOConfig::_setVector(int id, const Point3& vec)
{
  std::ostringstream	os;
  os << vec.x << " " << vec.y << " " << vec.z;

  SetDlgItemText(id, os.str().c_str());
}

void
PNOConfig::_setFront(const Point3& vec)
{
  _setVector(IDC_T_FRONT, vec);
}

void
PNOConfig::_setRight(const Point3& vec)
{
  _setVector(IDC_T_RIGHT, vec);
}

void
PNOConfig::_setTop(const Point3& vec)
{
  _setVector(IDC_T_TOP, vec);
}

Point3
PNOConfig::_getVector(int id)
{
  CString cstr;

  GetDlgItemText(id, cstr);
  std::istringstream	is(cstr.GetString());

  Point3  vec;
  is >> vec.x >> vec.y >> vec.z;

  return vec;
}

Point3
PNOConfig::_getFront()
{
  return _getVector(IDC_T_FRONT);
}

Point3
PNOConfig::_getRight()
{
  return _getVector(IDC_T_RIGHT);
}

Point3
PNOConfig::_getTop()
{
  return _getVector(IDC_T_TOP);
}

//////////////////////////////////////////////////////////////////////////

void
PNOConfig::_enableFields(BOOL enable)
{
  GetDlgItem(IDC_T_FRONT)->EnableWindow(enable);
  GetDlgItem(IDC_BT_FRONT)->EnableWindow(enable);
  GetDlgItem(IDC_T_RIGHT)->EnableWindow(enable);
  GetDlgItem(IDC_BT_RIGHT)->EnableWindow(enable);
  GetDlgItem(IDC_T_TOP)->EnableWindow(enable);
  GetDlgItem(IDC_BT_TOP)->EnableWindow(enable);
}

//////////////////////////////////////////////////////////////////////////

void PNOConfig::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PNOConfig, CDialog)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
  ON_BN_CLICKED(IDC_RB_DEFAULT, OnBnClickedRbDefault)
  ON_BN_CLICKED(IDC_RB_180, OnBnClickedRb180)
  ON_BN_CLICKED(IDC_RB_CUSTOM, OnBnClickedRbCustom)
  ON_BN_CLICKED(IDC_BT_FRONT, OnBnClickedBtFront)
  ON_BN_CLICKED(IDC_BT_RIGHT, OnBnClickedBtRight)
  ON_BN_CLICKED(IDC_BT_TOP, OnBnClickedBtTop)
END_MESSAGE_MAP()


// Gestionnaires de messages PNOConfig

BOOL  PNOConfig::OnInitDialog()
{
  if (CDialog::OnInitDialog() == FALSE)
	return FALSE;

  if (_object->DefaultDirection)
  {
	CheckRadioButton(IDC_RB_DEFAULT, IDC_RB_CUSTOM, IDC_RB_DEFAULT);
	OnBnClickedRbDefault();
  }
  else
  {
	CheckRadioButton(IDC_RB_DEFAULT, IDC_RB_CUSTOM, IDC_RB_CUSTOM);
	OnBnClickedRbCustom();
  }

  //////////////////////////////////////////////////////////////////////////

  _setFront(_object->Front);
  _setRight(_object->Right);
  _setTop(_object->Top);

  //////////////////////////////////////////////////////////////////////////

  return TRUE;
}

void PNOConfig::OnBnClickedOk()
{
  _object->DefaultDirection = GetCheckedRadioButton(IDC_RB_DEFAULT, IDC_RB_CUSTOM) == IDC_RB_DEFAULT;

  //////////////////////////////////////////////////////////////////////////

  _object->Front = _getFront();
  _object->Right = _getRight();
  _object->Top = _getTop();

  //////////////////////////////////////////////////////////////////////////

  OnOK();
}

void PNOConfig::OnBnClickedRbDefault()
{
  _enableFields(FALSE);

  _setFront(Point3(0.0f, 1.0f, 0.0f));
  _setRight(Point3(1.0f, 0.0f, 0.0f));
  _setTop(Point3(0.0f, 0.0f, 1.0f));
}

void PNOConfig::OnBnClickedRb180()
{
  _enableFields(FALSE);

  _setFront(Point3(0.0f, -1.0f, 0.0f));
  _setRight(Point3(-1.0f, 0.0f, 0.0f));
  _setTop(Point3(0.0f, 0.0f, 1.0f));
}

void PNOConfig::OnBnClickedRbCustom()
{
  _enableFields(TRUE);
}

void PNOConfig::OnBnClickedBtFront()
{
  Point3  point = _getFront();

  PNWUVecEdit	config(point, this);
  config.DoModal();

  _setFront(point);
}

void PNOConfig::OnBnClickedBtRight()
{
  Point3  point = _getRight();

  PNWUVecEdit	config(point, this);
  config.DoModal();

  _setRight(point);
}

void PNOConfig::OnBnClickedBtTop()
{
  Point3  point = _getTop();

  PNWUVecEdit	config(point, this);
  config.DoModal();

  _setTop(point);
}
