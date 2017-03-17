//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#include "CBerInputStream.h"

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace Asn1 {

ECode CBerInputStream::constructor(
    /* [in] */ ArrayOf<Byte>* encoded)
{
    return BerInputStream::constructor(encoded);
}

ECode CBerInputStream::constructor(
    /* [in] */ ArrayOf<Byte>* encoded,
    /* [in] */ Int32 offset,
    /* [in] */ Int32 expectedLength)
{
    return BerInputStream::constructor(encoded, offset, expectedLength);
}

ECode CBerInputStream::constructor(
    /* [in] */ IInputStream* is)
{
    return BerInputStream::constructor(is);
}

ECode CBerInputStream::constructor(
    /* [in] */ IInputStream* is,
    /* [in] */ Int32 initialSize)
{
    return BerInputStream::constructor(is, initialSize);
}

CAR_OBJECT_IMPL(CBerInputStream)

} // namespace Asn1
} // namespace Security
} // namespace Harmony
} // namespace Apache
} // namespace Org
