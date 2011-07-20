// PNModelWin.cpp : fichier d'implémentation
//

#include "stdafx.h"

#include "PNModelExporter.hpp"

#include "PNModelWin.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(PNModelWin, CDialog)
PNModelWin::PNModelWin(PNModelExporter *model, CWnd* pParent /*=NULL*/)
: CDialog(PNModelWin::IDD, pParent), _model(model)
{
}

PNModelWin::~PNModelWin()
{
}

void PNModelWin::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MATERIALS, _materials);
}

void PNModelWin::pnToMFC()
{
  _materials.DeleteAllItems();

  for (int i = 0; i < _model->_vectorMesh.size(); ++i)
  {
	_materials.InsertItem(LVIF_TEXT, i, _model->_vectorMesh[i].second->name, 0, 0, 0, 0);
  }
}

BEGIN_MESSAGE_MAP(PNModelWin, CDialog)
  ON_BN_CLICKED(IDUP, OnBnClickedUp)
  ON_BN_CLICKED(IDDOWN, OnBnClickedDown)
  ON_BN_CLICKED(IDBEGIN, OnBnClickedBegin)
  ON_BN_CLICKED(IDEND, OnBnClickedEnd)
END_MESSAGE_MAP()

BOOL  PNModelWin::OnInitDialog()
{
  if (CDialog::OnInitDialog() == FALSE)
	return FALSE;

  pnToMFC();

  return TRUE;
}

void PNModelWin::OnBnClickedUp()
{
  POSITION position = _materials.GetFirstSelectedItemPosition();
  int id = _materials.GetNextSelectedItem(position);

  if (id <= 0)
	return ;

  PNModelExporter::PAIR_MESH tmp = _model->_vectorMesh[id];

  _model->_vectorMesh[id] = _model->_vectorMesh[id-1];
  _model->_vectorMesh[id-1] = tmp;

  pnToMFC();

  _materials.SetSelectionMark(id-1);
  _materials.Invalidate();
}

void
PNModelWin::OnBnClickedDown()
{
  POSITION position = _materials.GetFirstSelectedItemPosition();
  int id = _materials.GetNextSelectedItem(position);

  if (id < 0 || id >= _model->_vectorMesh.size() - 1)
	return ;

  PNModelExporter::PAIR_MESH tmp = _model->_vectorMesh[id];

  _model->_vectorMesh[id] = _model->_vectorMesh[id+1];
  _model->_vectorMesh[id+1] = tmp;

  pnToMFC();

  _materials.SetSelectionMark(id+1);
  _materials.Invalidate();
}

void
PNModelWin::OnBnClickedBegin()
{
  POSITION position = _materials.GetFirstSelectedItemPosition();
  int id = _materials.GetNextSelectedItem(position);

  if (id <= 0)
	return ;

  PNModelExporter::PAIR_MESH tmp = _model->_vectorMesh[id];

  _model->_vectorMesh.erase(_model->_vectorMesh.begin() + id);
  _model->_vectorMesh.insert(_model->_vectorMesh.begin(), tmp);

  pnToMFC();

  _materials.SetSelectionMark(0);
  _materials.Invalidate();
}

void
PNModelWin::OnBnClickedEnd()
{
  POSITION position = _materials.GetFirstSelectedItemPosition();
  int id = _materials.GetNextSelectedItem(position);

  if (id < 0 || id >= _model->_vectorMesh.size() - 1)
	return ;

  PNModelExporter::PAIR_MESH tmp = _model->_vectorMesh[id];

  _model->_vectorMesh.erase(_model->_vectorMesh.begin() + id);
  _model->_vectorMesh.push_back(tmp);

  pnToMFC();

  _materials.SetSelectionMark((int)_model->_vectorMesh.size()-1);
  _materials.Invalidate();
}

//////////////////////////////////////////////////////////////////////////
};
