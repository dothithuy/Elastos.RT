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

#include <elautoptr.h>
#include <elastos/coredef.h>
#include <elastos/core/StringUtils.h>
#include <elastos/core/StringBuilder.h>
#include <elastos/utility/etl/List.h>
#include <elastos/utility/Arrays.h>

using namespace Elastos;
using Elastos::Core::StringUtils;
using Elastos::Core::Math;
using Elastos::Math::IBigInteger;
using Elastos::Math::CBigInteger;
using Elastos::Math::IBigDecimal;
using Elastos::Math::CBigDecimal;
using Elastos::Math::IBigDecimalHelper;
using Elastos::Math::CBigDecimalHelper;
using Elastos::Core::EIID_IComparable;


namespace Elastos {
namespace Math {

static void assertEquals(const char *hintMessage, Int32 expecting, Int32 toVerify)
{
    printf("expecting: %d, toVerify: %d. %s\n", expecting, toVerify, hintMessage);
    assert(expecting == toVerify);
}

#if 0
/*
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *  The ASF licenses this file to You under the Apache License, Version 2.0
 *  (the "License"); you may not use this file except in compliance with
 *  the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
/**
 * @author Elena Semukhina
 */

package org.apache.harmony.tests.java.math;

import junit.framework.TestCase;
import java.math.BigInteger;

/**
 * Class:  java.math.BigInteger
 * Method: multiply
 */
public class BigIntegerMultiplyTest extends TestCase {
#endif
    /**
     * Multiply two negative numbers of the same length
     */
#if 0
    public void testCase1() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3};
        byte bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        int aSign = -1;
        int bSign = -1;
        byte rBytes[] = {10, 40, 100, -55, 96, 51, 76, 40, -45, 85, 105, 4, 28, -86, -117, -52, 100, 120, 90};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
static void testCase1()
{
    signed char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3};
    signed char _bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    signed char _rBytes[] = {10, 40, 100, -55, 96, 51, 76, 40, -45, 85, 105, 4, 28, -86, -117, -52, 100, 120, 90};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = -1;
    int bSign = -1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec) || bNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", 1, sign);
}

    /**
     * Multiply two numbers of the same length and different signs.
     * The first is negative.
     */
#if 0
    public void testCase2() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3};
        byte bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        int aSign = -1;
        int bSign = 1;
        byte rBytes[] = {-11, -41, -101, 54, -97, -52, -77, -41, 44, -86, -106, -5, -29, 85, 116, 51, -101, -121, -90};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif
static void testCase2()
{
    signed char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3};
    signed char _bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    signed char _rBytes[] = {-11, -41, -101, 54, -97, -52, -77, -41, 44, -86, -106, -5, -29, 85, 116, 51, -101, -121, -90};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = -1;
    int bSign = 1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec) || bNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", -1, sign);
}


    /**
     * Multiply two positive numbers of different length.
     * The first is longer.
     */
#if 0
    public void testCase3() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
        byte bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        int aSign = 1;
        int bSign = 1;
        byte rBytes[] = {10, 40, 100, -55, 96, 51, 76, 40, -45, 85, 115, 44, -127,
                         115, -21, -62, -15, 85, 64, -87, -2, -36, -36, -106};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
static void testCase3()
{
    signed char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
    signed char _bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    signed char _rBytes[] = {10, 40, 100, -55, 96, 51, 76, 40, -45, 85, 115, 44, -127,
                         115, -21, -62, -15, 85, 64, -87, -2, -36, -36, -106};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    int bSign = 1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf("testCase3() Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf("testCase3() Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase3() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase3() incorrect sign", 1, sign);
}


    /**
     * Multiply two positive numbers of different length.
     * The second is longer.
     */
#if 0
    public void testCase4() {
        byte aBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
        int aSign = 1;
        int bSign = 1;
        byte rBytes[] = {10, 40, 100, -55, 96, 51, 76, 40, -45, 85, 115, 44, -127,
                         115, -21, -62, -15, 85, 64, -87, -2, -36, -36, -106};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
static void testCase4()
{
    signed char _aBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    signed char _bBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
    signed char _rBytes[] = {10, 40, 100, -55, 96, 51, 76, 40, -45, 85, 115, 44, -127,
                         115, -21, -62, -15, 85, 64, -87, -2, -36, -36, -106};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    int bSign = 1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec) || bNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", 1, sign);
}


    /**
     * Multiply two numbers of different length and different signs.
     * The first is positive.
     * The first is longer.
     */
#if 0
    public void testCase5() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
        byte bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        int aSign = 1;
        int bSign = -1;
        byte rBytes[] = {-11, -41, -101, 54, -97, -52, -77, -41, 44, -86, -116, -45, 126,
                         -116, 20, 61, 14, -86, -65, 86, 1, 35, 35, 106};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif
static void testCase5()
{
    signed char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
    signed char _bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    signed char _rBytes[] = {-11, -41, -101, 54, -97, -52, -77, -41, 44, -86, -116, -45, 126,
                         -116, 20, 61, 14, -86, -65, 86, 1, 35, 35, 106};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    int bSign = -1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf("testCase5() Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf("testCase5() Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase5() data error", (*resBytes)[i], (*rBytes)[i]);
        return;
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase5() incorrect sign", -1, sign);
}


    /**
     * Multiply two numbers of different length and different signs.
     * The first is positive.
     * The second is longer.
     */
#if 0
    public void testCase6() {
        byte aBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
        int aSign = 1;
        int bSign = -1;
        byte rBytes[] = {-11, -41, -101, 54, -97, -52, -77, -41, 44, -86, -116, -45, 126,
                         -116, 20, 61, 14, -86, -65, 86, 1, 35, 35, 106};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif
static void testCase6()
{
    signed char _aBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    signed char _bBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
    signed char _rBytes[] = {-11, -41, -101, 54, -97, -52, -77, -41, 44, -86, -116, -45, 126,
                         -116, 20, 61, 14, -86, -65, 86, 1, 35, 35, 106};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    int bSign = -1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec) || bNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", -1, sign);
}


    /**
     * Multiply a number by zero.
     */
#if 0
    public void testCase7() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
        byte bBytes[] = {0};
        int aSign = 1;
        int bSign = 0;
        byte rBytes[] = {0};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 0, result.signum());
    }
#endif
static void testCase7()
{
    signed char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
    signed char _bBytes[] = {0};
    signed char _rBytes[] = {0};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    int bSign = 0;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec) || bNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", 0, sign);
}


    /**
     * Multiply a number by ZERO.
     */
#if 0
    public void testCase8() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
        int aSign = 1;
        byte rBytes[] = {0};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = BigInteger.ZERO;
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 0, result.signum());
    }
#endif
static void testCase8()
{
    signed char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
    signed char _bBytes[] = {0};
    signed char _rBytes[] = {0};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    int bSign = 0;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec) || bNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", 0, sign);
}


    /**
     * Multiply a positive number by ONE.
     */
#if 0
    public void testCase9() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
        int aSign = 1;
        byte rBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = BigInteger.ONE;
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
static void testCase9()
{
    signed char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
    signed char _bBytes[] = {1};
    signed char _rBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    int bSign = 1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec) || bNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", 1, sign);
}


    /**
     * Multiply a negative number by ONE.
     */
#if 0
    public void testCase10() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
        int aSign = -1;
        byte rBytes[] = {-2, -3, -4, -5, -6, -7, -8, -2, -3, -4, -2, -3, -4, -5, -5};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = BigInteger.ONE;
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif
static void testCase10()
{
    signed char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 1, 2, 3, 4, 5};
    signed char _bBytes[] = {1};
    signed char _rBytes[] = {-2, -3, -4, -5, -6, -7, -8, -2, -3, -4, -2, -3, -4, -5, -5};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = -1;
    int bSign = 1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec) || bNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", -1, sign);
}


    /**
     * Multiply two numbers of 4 bytes length.
     */
#if 0
    public void testIntbyInt1() {
        byte aBytes[] = {10, 20, 30, 40};
        byte bBytes[] = {1, 2, 3, 4};
        int aSign = 1;
        int bSign = -1;
        byte rBytes[] = {-11, -41, -101, 55, 5, 15, 96};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif
static void testIntbyInt1()
{
    signed char _aBytes[] = {10, 20, 30, 40};
    signed char _bBytes[] = {1, 2, 3, 4};
    signed char _rBytes[] = {-11, -41, -101, 55, 5, 15, 96};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    int bSign = -1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec) || bNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", -1, sign);
}


    /**
     * Multiply two numbers of 4 bytes length.
     */
#if 0
    public void testIntbyInt2() {
        byte aBytes[] = {-1, -1, -1, -1};
        byte bBytes[] = {-1, -1, -1, -1};
        int aSign = 1;
        int bSign = 1;
        byte rBytes[] = {0, -1, -1, -1, -2, 0, 0, 0, 1};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.multiply(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
static void testIntbyInt2()
{
    signed char _aBytes[] = {-1, -1, -1, -1};
    signed char _bBytes[] = {-1, -1, -1, -1};
    signed char _rBytes[] = {0, -1, -1, -1, -2, 0, 0, 0, 1};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(sizeof(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, sizeof(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    int bSign = 1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec) || bNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Multiply(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", 1, sign);
}


    /**
     * Negative exponent.
     */
#if 0
    public void testPowException() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7};
        int aSign = 1;
        int exp = -5;
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        try {
            aNumber.pow(exp);
            fail("ArithmeticException has not been caught");
        } catch (ArithmeticException e) {
        }
    }
#endif
static void testPowException()
{
    signed char _aBytes[] = {1, 2, 3, 4, 5, 6, 7};
    signed char _rBytes[] = {1};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    Int32 exp = -5;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    ec = aNumber->Pow(exp, (IBigInteger**)&result);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" ArithmeticException has been caught. Error %08X\n", ec);
    } else {
        printf(" ArithmeticException has not been caught. Error %08X\n", ec);
    }
}


    /**
     * Exponentiation of a negative number to an odd exponent.
     */
#if 0
    public void testPowNegativeNumToOddExp() {
        byte aBytes[] = {50, -26, 90, 69, 120, 32, 63, -103, -14, 35};
        int aSign = -1;
        int exp = 5;
        byte rBytes[] = {-21, -94, -42, -15, -127, 113, -50, -88, 115, -35, 3,
            59, -92, 111, -75, 103, -42, 41, 34, -114, 99, -32, 105, -59, 127,
            45, 108, 74, -93, 105, 33, 12, -5, -20, 17, -21, -119, -127, -115,
            27, -122, 26, -67, 109, -125, 16, 91, -70, 109};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger result = aNumber.pow(exp);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif
static void testPowNegativeNumToOddExp()
{
    signed char _aBytes[] = {50, -26, 90, 69, 120, 32, 63, -103, -14, 35};
    signed char _rBytes[] = {-21, -94, -42, -15, -127, 113, -50, -88, 115, -35, 3,
            59, -92, 111, -75, 103, -42, 41, 34, -114, 99, -32, 105, -59, 127,
            45, 108, 74, -93, 105, 33, 12, -5, -20, 17, -21, -119, -127, -115,
            27, -122, 26, -67, 109, -125, 16, 91, -70, 109};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = -1;
    Int32 exp = 5;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Pow(exp, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", -1, sign);
}


    /**
     * Exponentiation of a negative number to an even exponent.
     */
#if 0
    public void testPowNegativeNumToEvenExp() {
        byte aBytes[] = {50, -26, 90, 69, 120, 32, 63, -103, -14, 35};
        int aSign = -1;
        int exp = 4;
        byte rBytes[] = {102, 107, -122, -43, -52, -20, -27, 25, -9, 88, -13,
            75, 78, 81, -33, -77, 39, 27, -37, 106, 121, -73, 108, -47, -101,
            80, -25, 71, 13, 94, -7, -33, 1, -17, -65, -70, -61, -3, -47};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger result = aNumber.pow(exp);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
static void testPowNegativeNumToEvenExp()
{
    signed char _aBytes[] = {50, -26, 90, 69, 120, 32, 63, -103, -14, 35};
    signed char _rBytes[] = {102, 107, -122, -43, -52, -20, -27, 25, -9, 88, -13,
            75, 78, 81, -33, -77, 39, 27, -37, 106, 121, -73, 108, -47, -101,
            80, -25, 71, 13, 94, -7, -33, 1, -17, -65, -70, -61, -3, -47};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = -1;
    Int32 exp = 4;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Pow(exp, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", 1, sign);
}



    /**
     * Exponentiation of a negative number to zero exponent.
     */
#if 0
    public void testPowNegativeNumToZeroExp() {
        byte aBytes[] = {50, -26, 90, 69, 120, 32, 63, -103, -14, 35};
        int aSign = -1;
        int exp = 0;
        byte rBytes[] = {1};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger result = aNumber.pow(exp);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
void testPowNegativeNumToZeroExp()
{
    signed char _aBytes[] = {50, -26, 90, 69, 120, 32, 63, -103, -14, 35};
    signed char _rBytes[] = {1};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = -1;
    Int32 exp = 0;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Pow(exp, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", 1, sign);
}


    /**
     * Exponentiation of a positive number.
     */
#if 0
    public void testPowPositiveNum() {
        byte aBytes[] = {50, -26, 90, 69, 120, 32, 63, -103, -14, 35};
        int aSign = 1;
        int exp = 5;
        byte rBytes[] = {20, 93, 41, 14, 126, -114, 49, 87, -116, 34, -4, -60,
            91, -112, 74, -104, 41, -42, -35, 113, -100, 31, -106, 58, -128,
            -46, -109, -75, 92, -106, -34, -13, 4, 19, -18, 20, 118, 126, 114,
            -28, 121, -27, 66, -110, 124, -17, -92, 69, -109};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger result = aNumber.pow(exp);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
void testPowPositiveNum()
{
    signed char _aBytes[] = {50, -26, 90, 69, 120, 32, 63, -103, -14, 35};
    signed char _rBytes[] = {20, 93, 41, 14, 126, -114, 49, 87, -116, 34, -4, -60,
            91, -112, 74, -104, 41, -42, -35, 113, -100, 31, -106, 58, -128,
            -46, -109, -75, 92, -106, -34, -13, 4, 19, -18, 20, 118, 126, 114,
            -28, 121, -27, 66, -110, 124, -17, -92, 69, -109};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    Int32 exp = 5;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf("testPowPositiveNum() Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Pow(exp, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testPowPositiveNum() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testPowPositiveNum() incorrect sign", 1, sign);
}


    /**
     * Exponentiation of a negative number to zero exponent.
     */
#if 0
    public void testPowPositiveNumToZeroExp() {
        byte aBytes[] = {50, -26, 90, 69, 120, 32, 63, -103, -14, 35};
        int aSign = 1;
        int exp = 0;
        byte rBytes[] = {1};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger result = aNumber.pow(exp);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
void testPowPositiveNumToZeroExp()
{
    signed char _aBytes[] = {50, -26, 90, 69, 120, 32, 63, -103, -14, 35};
    signed char _rBytes[] = {1};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(sizeof(_aBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(sizeof(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, sizeof(_aBytes));
    memcpy(rBytes->GetPayload(), _rBytes, sizeof(_rBytes));

    int aSign = 1;
    Int32 exp = 0;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec) || aNumber == NULL) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Pow(exp, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("incorrect sign", 1, sign);
}

//==============================================================================

EXTERN_C int mainBigIntegerMultiplyTest(int argc, char *argv[])
{
    printf("\n==== libcore/math/BigIntegerMultiplyTest ====\n");
    testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();
    testCase6();
    testCase7();
    testCase8();
    testCase9();
    testCase10();
    testIntbyInt1();
    testIntbyInt2();
    testPowException();
    testPowNegativeNumToOddExp();
    testPowNegativeNumToEvenExp();
    testPowNegativeNumToZeroExp();
    testPowPositiveNum();
    testPowPositiveNumToZeroExp();
    printf("\n==== end of libcore/math/BigIntegerMultiplyTest ====\n");

    return 0;
}

}
}
