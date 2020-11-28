
/*  Copyright (C) 2006 Koninklijke Philips Electronics N.V.
    All Rights Reserved.
    This source code and any compilation or derivative thereof is the
    proprietary information of Koninklijke Philips Electronics N.V. and is
    confidential in nature.
    Under no circumstances is this software to be exposed to or placed under an
    Open Source License of any type without the expressed written permission of
    Koninklijke Philips Electronics N.V.
*//**
     @file   tmNxCompId.h
     @brief  Brief description of this h file.

     @b  Component:  n/a

     This is a temporary workaround to assist integration of STB810 components
     into the STB225 project. STB810 uses the newer 'tmNxCompId.h' naming
     convention, while existing STB225 include 'tmCompId.h'.

     Set your editor for 4 space indentation.
  *//*

    Rev Date        Author      Comments
    --------------------------------------------------------------------------------
    001 20060605    G.Lawrance  Original
    --------------------------------------------------------------------------------
    For consistency and standardisation retain the Section Separators.
*/
#ifndef TMNXCOMPID_H
#define TMNXCOMPID_H

#ifdef __cplusplus
extern "C"
{
#endif

/* -------------------------------------------------------------------------- */
/* Project include files:                                                     */
/* -------------------------------------------------------------------------- */
#include "tmCompId.h"

// Map tmNxCompId.h onto tmCompId.h
#define CID_STBSTREAMINGSYSTEM CID_COMP_STBSTREAMINGSYSTEM


#ifdef __cplusplus
}
#endif

#endif /* TMNXCOMPID_H */
