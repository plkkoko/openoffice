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



#include "oox/dump/pptxdumper.hxx"

#include "oox/dump/biffdumper.hxx"
#include "oox/dump/oledumper.hxx"
#include "oox/dump/xlsbdumper.hxx"
#include "oox/helper/zipstorage.hxx"
#include "oox/ole/olestorage.hxx"

#if OOX_INCLUDE_DUMPER

namespace oox {
namespace dump {
namespace pptx {

// ============================================================================

using namespace ::com::sun::star::io;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;

using ::comphelper::MediaDescriptor;
using ::oox::core::FilterBase;
using ::rtl::OUString;

// ============================================================================

RootStorageObject::RootStorageObject( const DumperBase& rParent )
{
    StorageObjectBase::construct( rParent );
}

void RootStorageObject::implDumpStream( const Reference< XInputStream >& rxStrm, const OUString& rStrgPath, const OUString& rStrmName, const OUString& rSysFileName )
{
    OUString aExt = InputOutputHelper::getFileNameExtension( rStrmName );
    if( aExt.equalsIgnoreAsciiCaseAscii( "pptx" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "potx" ) )
    {
        Dumper( getContext(), rxStrm, rSysFileName ).dump();
    }
    else if(
        aExt.equalsIgnoreAsciiCaseAscii( "xlsb" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "xlsm" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "xlsx" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "xltm" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "xltx" ) )
    {
        ::oox::dump::xlsb::Dumper( getContext(), rxStrm, rSysFileName ).dump();
    }
    else if(
        aExt.equalsIgnoreAsciiCaseAscii( "xla" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "xlc" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "xlm" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "xls" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "xlt" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "xlw" ) )
    {
        ::oox::dump::biff::Dumper( getContext(), rxStrm, rSysFileName ).dump();
    }
    else if(
        aExt.equalsIgnoreAsciiCaseAscii( "xml" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "vml" ) ||
        aExt.equalsIgnoreAsciiCaseAscii( "rels" ) )
    {
        XmlStreamObject( *this, rxStrm, rSysFileName ).dump();
    }
    else if( aExt.equalsIgnoreAsciiCaseAscii( "bin" ) )
    {
        if( rStrgPath.equalsAscii( "ppt" ) && rStrmName.equalsAscii( "vbaProject.bin" ) )
        {
            StorageRef xStrg( new ::oox::ole::OleStorage( getContext(), rxStrm, false ) );
            VbaProjectStorageObject( *this, xStrg, rSysFileName ).dump();
        }
        else if( rStrgPath.equalsAscii( "ppt/embeddings" ) )
        {
            StorageRef xStrg( new ::oox::ole::OleStorage( getContext(), rxStrm, false ) );
            OleStorageObject( *this, xStrg, rSysFileName ).dump();
        }
        else if( rStrgPath.equalsAscii( "ppt/activeX" ) )
        {
            StorageRef xStrg( new ::oox::ole::OleStorage( getContext(), rxStrm, true ) );
            ActiveXStorageObject( *this, xStrg, rSysFileName ).dump();
        }
        else
        {
            BinaryStreamObject( *this, rxStrm, rSysFileName ).dump();
        }
    }
}

// ============================================================================

#define DUMP_PPTX_CONFIG_ENVVAR "OOO_PPTXDUMPER"

Dumper::Dumper( const FilterBase& rFilter )
{
    ConfigRef xCfg( new Config( DUMP_PPTX_CONFIG_ENVVAR, rFilter ) );
    DumperBase::construct( xCfg );
}

Dumper::Dumper( const Reference< XComponentContext >& rxContext, const Reference< XInputStream >& rxInStrm, const OUString& rSysFileName )
{
    if( rxContext.is() && rxInStrm.is() )
    {
        StorageRef xStrg( new ZipStorage( rxContext, rxInStrm ) );
        MediaDescriptor aMediaDesc;
        ConfigRef xCfg( new Config( DUMP_PPTX_CONFIG_ENVVAR, rxContext, xStrg, rSysFileName, aMediaDesc ) );
        DumperBase::construct( xCfg );
    }
}

void Dumper::implDump()
{
    RootStorageObject( *this ).dump();
}

// ============================================================================

} // namespace pptx
} // namespace dump
} // namespace oox

#endif
