/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 1999-2001 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Log: XMLDOMNamedNodeMap.h,v $
 * Revision 1.6  2004/02/12 13:49:43  amassari
 * Updated version to 2.5
 *
 * Revision 1.5  2003/11/21 12:05:48  amassari
 * Updated version to 2.4
 *
 * Revision 1.4  2003/10/21 21:21:32  amassari
 * When the COM object is loaded by a late-binding engine (like WSH, or
 * Visual Basic when the type library is not preloaded in the editor), the type
 * library version stored in the resource must match the version specified in the
 * IDispatchImpl template (defaulted to 1.0), or trying to invoke a method will fail
 *
 * Revision 1.3  2003/03/14 12:44:49  tng
 * [Bug 17147] C++ namespace breaks build of XercesCOM DLL
 *
 * Revision 1.2  2002/05/21 19:53:53  tng
 * DOM Reorganization: update include path for the old DOM interface in COM files
 *
 * Revision 1.1.1.1  2002/02/01 22:21:41  peiyongz
 * sane_include
 *
 * Revision 1.5  2001/05/11 13:25:06  tng
 * Copyright update.
 *
 * Revision 1.4  2001/01/19 15:18:26  tng
 * COM Updates by Curt Arnold: changed 1.3 to 1.4, updated the GUID's so
 * both can coexist and fixed a new minor bugs.  Most of the changes involved
 * error reporting, now a DOM defined error will return an HRESULT of
 * 0x80040600 + code and will set an error description to the error name.
 *
 * Revision 1.3  2000/06/03 00:29:00  andyh
 * COM Wrapper changes from Curt Arnold
 *
 * Revision 1.2  2000/03/30 02:00:10  abagchi
 * Initial checkin of working code with Copyright Notice
 *
 */

#ifndef ___xmldomnamednodemap_h___
#define ___xmldomnamednodemap_h___

#include <xercesc/dom/deprecated/DOM_NamedNodeMap.hpp>
#include "NodeContainerImpl.h"

XERCES_CPP_NAMESPACE_USE

class ATL_NO_VTABLE CXMLDOMNamedNodeMap :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IXMLDOMNamedNodeMap, &IID_IXMLDOMNamedNodeMap, &LIBID_Xerces, 2, 50>,
	public NodeContainerImpl<DOM_NamedNodeMap>,
	public ISupportErrorInfo
{
public:
	CXMLDOMNamedNodeMap()
	{}

	void FinalRelease()
	{
		ReleaseOwnerDoc();
	}

DECLARE_NOT_AGGREGATABLE(CXMLDOMNamedNodeMap)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXMLDOMNamedNodeMap)
	COM_INTERFACE_ENTRY(IXMLDOMNamedNodeMap)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


	//   ISupportErrorInfo
	HRESULT STDMETHODCALLTYPE InterfaceSupportsErrorInfo(REFIID iid);

	// IXMLDOMNamedNodeMap methods
	STDMETHOD(getNamedItem)(BSTR name, IXMLDOMNode  * *namedItem);
	STDMETHOD(setNamedItem)(IXMLDOMNode  *newItem, IXMLDOMNode  * *nameItem);
	STDMETHOD(removeNamedItem)(BSTR name, IXMLDOMNode  * *namedItem);
	STDMETHOD(get_item)(long index, IXMLDOMNode  * *pVal);
	STDMETHOD(get_length)(long  *pVal);
	STDMETHOD(getQualifiedItem)(BSTR baseName, BSTR namespaceURI, IXMLDOMNode  * *node);
	STDMETHOD(removeQualifiedItem)(BSTR baseName, BSTR namespaceURI, IXMLDOMNode  * *node);
	STDMETHOD(nextNode)(IXMLDOMNode  * *nextItem);
	STDMETHOD(reset)();
	STDMETHOD(get__newEnum)(IUnknown  * *pVal);
};

typedef CComObject<CXMLDOMNamedNodeMap> CXMLDOMNamedNodeMapObj;

#endif // ___xmldomnamednodemap_h___