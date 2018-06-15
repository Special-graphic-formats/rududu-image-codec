/***************************************************************************
 *   Copyright (C) 2007 by Nicolas Botti   *
 *   rududu@laposte.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "geomcodec.h"

namespace rududu {

CGeomCodec::CGeomCodec(CMuxCodec * RangeCodec, const unsigned char * k_init)
{
	setCtx(k_init);
	setRange(RangeCodec);
}

void CGeomCodec::setCtx(const unsigned char * k_init)
{
	for( int ctx = 0; ctx < GEO_CONTEXT_NB; ctx++){
		idx[ctx] = GEO_MAX_SHIFT - 1;
		if (k_init != 0) idx[ctx] = k_init[ctx];
		if (idx[ctx] >= GEO_MAX_SHIFT - 1)
			freq[ctx] = HALF_FREQ_COUNT;
		else
			freq[ctx] = (thres[(int)idx[ctx] - 1] + thres[(int)idx[ctx]]) >> 1;
	}
}


const unsigned short CGeomCodec::thres[11] = {
	1512, 2584, 3351, 3725, 3911, 4004, 4050, 4073, 4084, 4090, 4093
};

const unsigned char CGeomCodec::K[24] = {
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
};

const unsigned char CGeomCodec::shift[24] = {
	10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

}
