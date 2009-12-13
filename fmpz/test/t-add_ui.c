/*============================================================================

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

===============================================================================*/
/****************************************************************************

   Copyright (C) 2009 William Hart

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

int main(void)
{
   int result;
   printf("add_ui....");
   fflush(stdout);

   fmpz_randinit();

   for (ulong i = 0; i < 100000UL; i++) 
   {
      fmpz_t a, b;
      mpz_t d, e, f;
      ulong x;

      fmpz_init(a);
      fmpz_init(b);
      
      mpz_init(d);
      mpz_init(e);
      mpz_init(f);
      
      fmpz_randtest(a, 200);
      
      fmpz_get_mpz(d, a);
      x = n_randtest();

      fmpz_add_ui(b, a, x);
      mpz_add_ui(e, d, x);
      
      fmpz_get_mpz(f, b);
         
      result = (mpz_cmp(e, f) == 0);

      if (!result)
      {
         printf("FAIL\n");
         gmp_printf("d = %Zd, e = %Zd, f = %Zd, x = %lu\n", d, e, f, x);
         abort();
      }

      fmpz_clear(a);
      fmpz_clear(b);
      
      mpz_clear(d);
      mpz_clear(e);
      mpz_clear(f);
   }

   // check aliasing of a and b
   for (ulong i = 0; i < 100000UL; i++) 
   {
      fmpz_t a;
      mpz_t d, e, f;
      ulong x;

      fmpz_init(a);
      
      mpz_init(d);
      mpz_init(e);
      mpz_init(f);
      
      fmpz_randtest(a, 200);
      
      fmpz_get_mpz(d, a);
      x = n_randtest();

      fmpz_add_ui(a, a, x);
      mpz_add_ui(e, d, x);
      
      fmpz_get_mpz(f, a);
         
      result = (mpz_cmp(e, f) == 0);

      if (!result)
      {
         printf("FAIL\n");
         gmp_printf("d = %Zd, e = %Zd, f = %Zd, x = %lu\n", d, e, f, x);
         abort();
      }

      fmpz_clear(a);
      
      mpz_clear(d);
      mpz_clear(e);
      mpz_clear(f);
   }

   fmpz_randclear();

   _fmpz_cleanup();
   printf("PASS\n");
   return 0;
}