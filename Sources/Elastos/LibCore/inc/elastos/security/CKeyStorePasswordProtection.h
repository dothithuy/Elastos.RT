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

#ifndef __ELASTOS_SECURITY_CKEYSTOREPASSWORDPROTECTION_H__
#define __ELASTOS_SECURITY_CKEYSTOREPASSWORDPROTECTION_H__

#include "_Elastos_Security_CKeyStorePasswordProtection.h"
#include "elastos/core/Object.h"

using Elastos::Core::Object;

namespace Elastos {
namespace Security {

CarClass(CKeyStorePasswordProtection)
    , public Object
    , public IKeyStorePasswordProtection
    , public IKeyStoreProtectionParameter
    , public IDestroyable
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    CKeyStorePasswordProtection();

    CARAPI GetPassword(
        /* [out, callee] */ ArrayOf<Char32> **pwd);

    CARAPI Destroy();

    CARAPI IsDestroyed(
        /* [out] */ Boolean *isDestroyed);

    CARAPI constructor(
        /* [in] */ ArrayOf<Char32> *password);

private:
    // Store password
    AutoPtr<ArrayOf<Char32> > mPassword;

    Boolean mIsDestroyed;

    Object mLock;
};

}
}

#endif // __ELASTOS_SECURITY_CKEYSTOREPASSWORDPROTECTION_H__