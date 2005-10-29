/*
 * pn-setup.nsh
 *
 * Description :
 * Base script installer generator for Pavillon-Noir
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

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "Pavillon Noir"
!define PRODUCT_PUBLISHER "Pavillon Noir"
!define PRODUCT_WEB_SITE "http://www.pavillon-noir.org"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\pncore.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "ic_install.ico"
!define MUI_UNICON "ic_uninstall.ico"

; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "..\..\COPYING"
; Components page
!insertmacro MUI_PAGE_COMPONENTS
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Start menu page
var ICONS_GROUP
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Pavillon Noir"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
;!define MUI_FINISHPAGE_RUN "$INSTDIR\pavillonnoir\__binaries\win32\pncore.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "French"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "pn-setup-${PNSETUP_TYPE}-${PRODUCT_VERSION}.exe"
InstallDir "$PROGRAMFILES\Pavillon Noir"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

SectionGroup /e "Jeu"
Section "!Binaires" SecBin
  SetOutPath "$INSTDIR"
  File "..\..\AUTHORS"
  File "..\..\Changelog.txt"
  File "..\..\COPYING"
  File "..\..\FAL"
  File "..\..\README"
  
  SetOutPath "$INSTDIR\pavillonnoir\__binaries"
  File    /x .svn /x *.log "..\__binaries\*.*"

  SetOutPath "$INSTDIR\pavillonnoir\__binaries\win32"
  File /r /x .svn /x *.ilk /x *.exp /x *.log "..\__binaries\win32\*.*"
  File "C:\WINDOWS\system32\msvc*d.dll"
  
  SetOutPath "$INSTDIR\pavillonnoir\__doc\quickstart"
  File /x .svn /x *.log "..\__doc\quickstart\*.pdf"

; Shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  SetOutPath "$INSTDIR\pavillonnoir\__binaries\win32"
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  
  ; pncore release and debug shortcuts
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\${PRODUCT_NAME}.lnk" "$INSTDIR\pavillonnoir\__binaries\win32\pncore.exe"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\${PRODUCT_NAME} (Debug).lnk" "$INSTDIR\pavillonnoir\__binaries\win32\pncore-dbg.exe"
  CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\pavillonnoir\__binaries\win32\pncore.exe"
  
  ; pneditor release and debug shortcuts
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\PNEditor.lnk" "$INSTDIR\pavillonnoir\__binaries\win32\pneditor.exe"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\PNEditor (Debug).lnk" "$INSTDIR\pavillonnoir\__binaries\win32\pneditor-dbg.exe"
  
  ; user documentation shortcut
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Documentation utilisateur.lnk" "$INSTDIR\pavillonnoir\__doc\quickstart\Demarrage rapide.pdf"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section "Données" SecData
  SetOutPath "$INSTDIR\pavillonnoir\__binaries"
  File /r /x .svn /x Thumbs.db /x __JUNK "..\__binaries\datafiles"
SectionEnd
SectionGroupEnd

Section -SecOpenAl
  SetOutPath "$INSTDIR\pavillonnoir\__library\win32\install"
  File "..\__library\win32\install\OpenALwEAX.exe"
  ExecWait '"$INSTDIR\pavillonnoir\__library\win32\install\OpenALwEAX.exe"'
SectionEnd

Section -AdditionalIcons
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Site Internet ${PRODUCT_NAME}.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Désinstallation.lnk" "$INSTDIR\uninst.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\pavillonnoir\__binaries\win32\pncore.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) a été désinstallé avec succès de votre ordinateur."
FunctionEnd

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Êtes-vous certains de vouloir désinstaller totalement $(^Name) et tous ses composants ?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  RMDir /r "$INSTDIR"
  
  RMDir /r "$SMPROGRAMS\$ICONS_GROUP"
  Delete "$DESKTOP\Pavillon Noir.lnk"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd