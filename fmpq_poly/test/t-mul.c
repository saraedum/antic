/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2010 Sebastian Pancratz
    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    fmpz_randstate_t state;

    printf("mul....");
    fflush(stdout);

    fmpq_poly_randinit(state);

    /* Check aliasing of a and b */
    for (i = 0; i < 2000; i++)
    {
        fmpq_poly_t a, b, c;

        fmpq_poly_init(a);
        fmpq_poly_init(b);
        fmpq_poly_init(c);
        fmpq_poly_randtest(b, state, n_randint(50), 500);
        fmpq_poly_randtest(c, state, n_randint(50), 500);

        fmpq_poly_mul(a, b, c);
        fmpq_poly_mul(b, b, c);

        result = (fmpq_poly_equal(a, b));
        if (!result)
        {
            printf("FAIL:\n");
            fmpq_poly_print(a), printf("\n\n");
            fmpq_poly_print(b), printf("\n\n");
            abort();
        }

        fmpq_poly_clear(a);
        fmpq_poly_clear(b);
        fmpq_poly_clear(c);
    }

    /* Check aliasing of a and c */
    for (i = 0; i < 2000; i++)
    {
        fmpq_poly_t a, b, c;

        fmpq_poly_init(a);
        fmpq_poly_init(b);
        fmpq_poly_init(c);
        fmpq_poly_randtest(b, state, n_randint(50), 500);
        fmpq_poly_randtest(c, state, n_randint(50), 500);

        fmpq_poly_mul(a, b, c);
        fmpq_poly_mul(c, b, c);

        result = (fmpq_poly_equal(a, c));
        if (!result)
        {
            printf("FAIL:\n");
            fmpq_poly_print(a), printf("\n\n");
            fmpq_poly_print(c), printf("\n\n");
            abort();
        }

        fmpq_poly_clear(a);
        fmpq_poly_clear(b);
        fmpq_poly_clear(c);
    }

    /* Check (b*c)+(b*d) = b*(c+d) */
    for (i = 0; i < 2000; i++)
    {
        fmpq_poly_t a1, a2, b, c, d;

        fmpq_poly_init(a1);
        fmpq_poly_init(a2);
        fmpq_poly_init(b);
        fmpq_poly_init(c);
        fmpq_poly_init(d);
        fmpq_poly_randtest(b, state, n_randint(100), 500);
        fmpq_poly_randtest(c, state, n_randint(100), 500);
        fmpq_poly_randtest(d, state, n_randint(100), 500);

        fmpq_poly_mul(a1, b, c);
        fmpq_poly_mul(a2, b, d);
        fmpq_poly_add(a1, a1, a2);

        fmpq_poly_add(c, c, d);
        fmpq_poly_mul(a2, b, c);

        result = (fmpq_poly_equal(a1, a2));
        if (!result)
        {
            printf("FAIL:\n");
            fmpq_poly_print(a1), printf("\n\n");
            fmpq_poly_print(a2), printf("\n\n");
            abort();
        }

        fmpq_poly_clear(a1);
        fmpq_poly_clear(a2);
        fmpq_poly_clear(b);
        fmpq_poly_clear(c);
        fmpq_poly_clear(d);
    }

    fmpq_poly_randclear(state);
    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}
