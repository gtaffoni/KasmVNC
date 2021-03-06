/* Copyright (C) 2002-2005 RealVNC Ltd.  All Rights Reserved.
 * Copyright 2020 Pierre Ossman for Cendio AB
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <rdr/BufferedInStream.h>
#include <rdr/Exception.h>

using namespace rdr;

static const size_t DEFAULT_BUF_SIZE = 8192;

BufferedInStream::BufferedInStream()
  : bufSize(DEFAULT_BUF_SIZE), offset(0)
{
  ptr = end = start = new U8[bufSize];
}

BufferedInStream::~BufferedInStream()
{
  delete [] start;
}

size_t BufferedInStream::pos()
{
  return offset + ptr - start;
}

bool BufferedInStream::overrun(size_t needed, bool wait)
{
  if (needed > bufSize)
    throw Exception("BufferedInStream overrun: "
                    "requested size of %lu bytes exceeds maximum of %lu bytes",
                    (long unsigned)needed, (long unsigned)bufSize);

  // Do we need to shuffle things around?
  if ((bufSize - (ptr - start)) < needed) {
    memmove(start, ptr, end - ptr);

    offset += ptr - start;
    end -= ptr - start;
    ptr = start;
  }

  while (avail() < needed) {
    if (!fillBuffer(start + bufSize - end, wait))
      return false;
  }

  return true;
}
