
/*============================================================================

This C source file is part of the SoftFloat IEEE Floating-Point Arithmetic
Package, Release 3a, by John R. Hauser.

Copyright 2011, 2012, 2013, 2014 The Regents of the University of California.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions, and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions, and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. Neither the name of the University nor the names of its contributors may
    be used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS", AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ARE
DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/

#include "platform.h" 
#include "internals.h"

struct exp32_sig128
 softfloat_normSubnormalF128Sig( uint_fast64_t sig64, uint_fast64_t sig0 )
{
    int_fast8_t shiftCount;
    struct exp32_sig128 z;

    if ( ! sig64 ) {
        shiftCount = softfloat_countLeadingZeros64( sig0 ) - 15;
        z.exp = -63 - shiftCount;
        if ( shiftCount < 0 ) {
            z.sig.v64 = sig0>>-shiftCount;
            z.sig.v0  = sig0<<(shiftCount & 63);
        } else {
            z.sig.v64 = sig0<<shiftCount;
            z.sig.v0  = 0;
        }
    } else {
        shiftCount = softfloat_countLeadingZeros64( sig64 ) - 15;
        z.exp = 1 - shiftCount;
        z.sig = softfloat_shortShiftLeft128( sig64, sig0, shiftCount );
    }
    return z;

}

