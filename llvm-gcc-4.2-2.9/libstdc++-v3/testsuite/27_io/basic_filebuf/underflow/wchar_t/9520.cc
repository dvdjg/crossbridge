// { dg-require-namedlocale "" }

// 2003-05-03  Petur Runolfsson <peturr02@ru.is>

// Copyright (C) 2003, 2005 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
// USA.

#include <testsuite_hooks.h>
#include <fstream>
#include <cstdio>

// libstdc++/9520
void test01()
{
  using namespace std;

  bool test __attribute__((unused)) = true;
  const char* name = "tmp_9520";

  FILE* file = fopen(name, "w");
  for (int i = 1; i < 256; ++i)
    putc(static_cast<unsigned char>(i), file);
  fclose(file);

  locale loc (locale("de_DE.ISO-8859-15@euro"));
  wchar_t buf[1];
  wfilebuf fb;
  fb.pubimbue(loc);
  fb.pubsetbuf(buf, 1);
  fb.open(name, ios_base::in);

  for (int j = 1; j < 256; ++j)
    {
      wfilebuf::int_type c1 = fb.sgetc();
      VERIFY( c1 != wfilebuf::traits_type::eof() );
      wfilebuf::int_type c2 = fb.sbumpc();
      VERIFY( c1 == c2 );
    }

  fb.close();
}

int main()
{
  test01();  
  return 0;
}
