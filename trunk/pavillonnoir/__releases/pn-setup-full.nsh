/*
 * pn-setup-full.nsh
 *
 * Description :
 * Full script installer generator for Pavillon-Noir.
 * Adding sources and dependencies.
 *
 * Copyright (C) 2005 PAVILLON-NOIR TEAM, http://pavillon-noir.org
 * This software has been written in EPITECH <http://www.epitech.net>
 * EPITECH is computer science school in Paris - FRANCE -
 * under the direction of flav <http://www.epita.fr/~flav>.
 * and Jerome Landrieu.
 *
 * This file is part of Pavillon Noir.
 *
 * Pavillon Noir is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * Pavillon Noir is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Pavillon Noir; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

!define PNSETUP_TYPE "full"

!include "pn-setup.nsh"

SectionGroup /e "Développement"
Section /o "Sources" SecSrc
  SetOutPath "$INSTDIR\pavillonnoir"
  File /r /x .svn "..\__src"
  File /r /x .svn /x *.ncb /x *.suo /x Debug /x Release /x .metadata "..\__managers"
  File /r /x .svn /x html "..\__doc"
  File /r /x .svn /x *.exe /x *.rar "..\__releases"
  SetOutPath "$INSTDIR"
  File /r /x .svn /x *.scb /x *.suo /x Debug /x Release "..\..\tools"
SectionEnd

Section /o "Dépendances" SecDep
  SetOutPath "$INSTDIR\pavillonnoir\__library"
  File /r /x .svn "..\__library\*.*"
  SetOutPath "$INSTDIR\tolua++"
  File /r /x .svn "..\..\tolua++\*.*"
SectionEnd
SectionGroupEnd

; Section descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecBin} "Binaires de Pavillon Noir."
  !insertmacro MUI_DESCRIPTION_TEXT ${SecData} "Données suplémentaires, notament les différentes cartes et ressources 3D..."
  !insertmacro MUI_DESCRIPTION_TEXT ${SecSrc} "Source de Pavillon Noir."
  !insertmacro MUI_DESCRIPTION_TEXT ${SecDep} "Dépendances de compilation."
!insertmacro MUI_FUNCTION_DESCRIPTION_END