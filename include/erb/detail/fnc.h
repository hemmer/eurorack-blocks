/*****************************************************************************

      fnc.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"

#include <cstddef>
#include <cstdint>



namespace erb
{



template <size_t NbrChannels>
void              scale (std::array <Buffer, NbrChannels> & out, float * const * in, float gain);
template <size_t NbrChannels>
void              scale (float ** out, const std::array <Buffer, NbrChannels> & in, float gain);

inline uint16_t   norm_to_u16 (float norm_val);
inline float      to_float_norm (uint16_t val);



}  // namespace erb



#include "erb/detail/fnc.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
