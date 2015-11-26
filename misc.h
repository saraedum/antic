/*=============================================================================

    This file is part of ANTIC

    ANTIC is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ANTIC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2015 Claus Fieker

******************************************************************************/

#ifndef ANTIC_MISC_H
#define ANTIC_MISC_H

#undef ulong
#define ulong ulongxx /* interferes with system includes */
#include <stdio.h>
#undef ulong

#ifdef __cplusplus
 extern "C" {
#endif

FLINT_DLL slong _nmod_mat_howell(nmod_mat_t A)

FLINT_DLL slong _fmpz_mat_howell(fmpz_mat_t A, fmpz_t mod)

#ifdef __cplusplus
}
#endif
#endif

