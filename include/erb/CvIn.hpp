/*****************************************************************************

      CvIn.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <FloatRange Range>
CvIn <Range>::CvIn (const std::uint16_t & data)
:  _data (data)
{
}



/*
==============================================================================
Name : operator float
==============================================================================
*/

template <FloatRange Range>
CvIn <Range>::operator float () const
{
   constexpr float u16_to_norm = 1.f / 65535.f;
   float norm_val = float (_data) * u16_to_norm;

   if constexpr (Range == FloatRange::Normalized)
   {
      return norm_val;
   }
   else if constexpr (Range == FloatRange::Bipolar)
   {
      return norm_val * 2.f - 1.f;
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
