/*****************************************************************************

      Pot.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Pot.h"

#include "erb/Module.h"

namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Pot::Pot (Module & module, const AdcPin & pin, Mode mode)
:  AnalogControlBase (module, pin)
,  _mode (mode)
{
}



/*
==============================================================================
Name : ctor
Note : Multiplexer version
==============================================================================
*/

Pot::Pot (Multiplexer & multiplexer, const MultiplexerPin & pin, Mode mode)
:  AnalogControlBase (multiplexer, pin)
,  _mode (mode)
{
}



/*
==============================================================================
Name : set_mode
==============================================================================
*/

void  Pot::set_mode (Mode mode)
{
   _mode = mode;
}



/*
==============================================================================
Name : operator float
==============================================================================
*/

Pot::operator float () const
{
   switch (_mode)
   {
   case Mode::Normalized:
#if defined (__GNUC__) && ! defined (__clang__)
   default:
#endif
      return norm_val ();

   case Mode::Bipolar:
      return norm_val () * 2.f - 1.f;
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
