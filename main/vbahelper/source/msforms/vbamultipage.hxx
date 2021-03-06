/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/


#ifndef SC_VBA_MULTIPAGE_HXX
#define SC_VBA_MULTIPAGE_HXX
#include <cppuhelper/implbase1.hxx>
#include <ooo/vba/msforms/XMultiPage.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>

#include "vbacontrol.hxx"
#include <vbahelper/vbahelper.hxx>
//#include <cppuhelper/implbase2.hxx>
#include <cppuhelper/implbase1.hxx>

typedef cppu::ImplInheritanceHelper1< ScVbaControl, ov::msforms::XMultiPage > MultiPageImpl_BASE;

class ScVbaMultiPage : public MultiPageImpl_BASE
{
    css::uno::Reference< css::container::XIndexAccess > getPages( sal_Int32 nPages );
    css::uno::Reference< css::beans::XPropertySet > mxDialogProps;
public:
    ScVbaMultiPage(
        const css::uno::Reference< ov::XHelperInterface >& xParent,
        const css::uno::Reference< css::uno::XComponentContext >& xContext,
        const css::uno::Reference< css::uno::XInterface >& xControl,
        const css::uno::Reference< css::frame::XModel >& xModel,
        ov::AbstractGeometryAttributes* pGeomHelper,
        const css::uno::Reference< css::awt::XControl >& xDialog );

   // Attributes
    virtual sal_Int32 SAL_CALL getValue() throw (css::uno::RuntimeException);
    virtual void SAL_CALL setValue( sal_Int32 _value ) throw (css::uno::RuntimeException);
    virtual css::uno::Any SAL_CALL Pages( const css::uno::Any& index ) throw (css::uno::RuntimeException);

    //XHelperInterface
    virtual rtl::OUString& getServiceImplName();
    virtual css::uno::Sequence<rtl::OUString> getServiceNames();
    // XDefaultProperty
    rtl::OUString SAL_CALL getDefaultPropertyName(  ) throw (css::uno::RuntimeException) { return ::rtl::OUString::createFromAscii("Value"); }
};
#endif //SC_VBA_LABEL_HXX
