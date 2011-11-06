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



#ifndef INCLUDED_COMPHELPER_WEAKBAG_HXX
#define INCLUDED_COMPHELPER_WEAKBAG_HXX

#include "sal/config.h"

#include <list>
#include "com/sun/star/uno/Reference.hxx"
#include "cppuhelper/weakref.hxx"
#include "osl/diagnose.h"

namespace comphelper {

/**
   A bag of UNO weak references.
*/
template< typename T > class WeakBag {
public:
    /**
       Add a new weak reference.

       The implementation keeps the amount of memory consumed linear in the
       number of living references added, not linear in the number of total
       references added.

       @param e
       a non-null reference.
    */
    void add(com::sun::star::uno::Reference< T > const & e) {
        OSL_ASSERT(e.is());
        for (typename List::iterator i(m_list.begin()); i != m_list.end();) {
            if (com::sun::star::uno::Reference< T >(*i).is()) {
                ++i;
            } else {
                i = m_list.erase(i);
            }
        }
        m_list.push_back(com::sun::star::uno::WeakReference< T >(e));
    }

    /**
       Remove a living reference.

       @return
       a living reference, or null if there are none.
    */
    com::sun::star::uno::Reference< T > remove() {
        while (!m_list.empty()) {
            com::sun::star::uno::Reference< T > r(m_list.front());
            m_list.pop_front();
            if (r.is()) {
                return r;
            }
        }
        return com::sun::star::uno::Reference< T >();
    }

private:
    typedef std::list< com::sun::star::uno::WeakReference< T > > List;

    List m_list;
};

}

#endif
