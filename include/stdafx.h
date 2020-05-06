//  Instinct Reactive Planning Library.
//  to interact with the Plan via a textual command line
//  Copyright (c) 2016  Robert H. Wortham <r.h.wortham@gmail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

// stdafx.h null library for VC++ compatability

#pragma once

#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#define PROGMEM

// Compatibility functions used from https://github.com/rwortham/Instinct-RobotWorld
namespace stdafx {

  inline int snprintf_P(char *_s, size_t _n, const char *_fmt, ...) {
    int nRtn;
    va_list args;
    va_start(args, _fmt);

    *(_s + _n - 1) = 0; // force a zero term at end of buffer
    nRtn = vsnprintf(_s, _n - 1, _fmt, args);
    va_end(args);

    if (nRtn < 0) {
      // ideally we should return number of chars that would have been written had the buffer been long enough
      // we don't know this easily, so just return buffer length
      nRtn = _n;
    }
    return nRtn;
  }

  inline  int sscanf_P(const char *_s, const char *_fmt, ...) {
    int nRtn;
    va_list args;
    va_start(args, _fmt);

    nRtn = vsscanf(_s, _fmt, args);
    va_end(args);

    return nRtn;
  }
}