/* Copyright (C) 2019 Kasm Web
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
#ifndef __RFB_TIGHTWEBPENCODER_H__
#define __RFB_TIGHTWEBPENCODER_H__

#include <rfb/Encoder.h>
#include <stdint.h>
#include <vector>

namespace rfb {

  class TightWEBPEncoder : public Encoder {
  public:
    TightWEBPEncoder(SConnection* conn);
    virtual ~TightWEBPEncoder();

    virtual bool isSupported();

    virtual void setQualityLevel(int level);
    virtual void setFineQualityLevel(int quality, int subsampling);

    virtual bool treatLossless();

    virtual void writeRect(const PixelBuffer* pb, const Palette& palette);
    virtual void compressOnly(const PixelBuffer* pb, const uint8_t quality,
                              std::vector<uint8_t> &out, const bool lowVideoQuality) const;
    virtual void writeOnly(const std::vector<uint8_t> &out) const;
    virtual void writeSolidRect(int width, int height,
                                const PixelFormat& pf,
                                const rdr::U8* colour);

    rdr::U32 benchmark() const;

  protected:
    void writeCompact(rdr::U32 value, rdr::OutStream* os) const;

  protected:
    int qualityLevel;
  };
}
#endif
