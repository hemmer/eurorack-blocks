/*****************************************************************************

      BoardBase.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardBase.h"



namespace erb
{
namespace daisy
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

BoardBase::BoardBase ()
:  _adc_channels (_seed)
{
   enable_fz ();

   _this_ptr = this;

   _seed.Configure ();
   _seed.Init (true /* boost */);

   for (auto & frame : _onboard_codec_buffer_output) frame.fill (0.f);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : do_init_adc_channels
==============================================================================
*/

BoardBase::AdcChannelsData BoardBase::do_init_adc_channels (std::initializer_list <AdcChannel> adc_channels)
{
   std::array <daisy::AdcChannelConfig, NBR_MAX_ADC_CHANNELS> configs;

   size_t config_nbr = 0;
   for (auto && adc_channel : adc_channels)
   {
      auto & config = configs [config_nbr];
      ++config_nbr;

      if (adc_channel.nbr_channels == 1)
      {
         config.InitSingle (adc_channel.pin);
      }
      else
      {
         config.InitMux (
            adc_channel.pin,
            adc_channel.nbr_channels,
            adc_channel.pin_a,
            adc_channel.pin_b,
            adc_channel.pin_c
         );
      }
   }

   _seed.adc.Init (&configs [0], configs.size ());

   AdcChannelsData adc_channels_data;

   config_nbr = 0;
   size_t channel_nbr = 0;
   for (auto && adc_channel : adc_channels)
   {
      if (adc_channel.nbr_channels == 1)
      {
         adc_channels_data [channel_nbr] = _seed.adc.GetPtr (uint8_t (config_nbr));
         ++channel_nbr;
      }
      else
      {
         for (size_t i = 0 ; i < adc_channel.nbr_channels ; ++i)
         {
            adc_channels_data [channel_nbr]
               = _seed.adc.GetMuxPtr (uint8_t (config_nbr), i);
            ++channel_nbr;
         }
      }

      ++config_nbr;
   }

   return adc_channels_data;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : enable_fz
Description :
   Enable FZ (flush-to-zero) denormal behavior
==============================================================================
*/

void  BoardBase::enable_fz ()
{
   uint32_t fpscr = __get_FPSCR ();
   fpscr |= 0x01000000; // FZ bit
   __set_FPSCR (fpscr);
}



/*
==============================================================================
Name : do_run
==============================================================================
*/

void  BoardBase::do_run ()
{
   _adc_channels.init ();

   _seed.adc.Start ();
   _seed.StartAudio (audio_callback_proc);

   for (;;) {}
}



/*
==============================================================================
Name : audio_callback_proc
==============================================================================
*/

void  BoardBase::audio_callback_proc (float ** in, float ** out, size_t size)
{
   _this_ptr->audio_callback (in, out, size);
}



/*
==============================================================================
Name : audio_callback
==============================================================================
*/

void  BoardBase::audio_callback (float ** in, float ** out, size_t /* size */)
{
   constexpr uint64_t sample_rate_ull = uint64_t (erb_SAMPLE_RATE);
   constexpr uint64_t buffer_size_ull = erb_BUFFER_SIZE;

   // Map eurorack audio level (-5V, 5V) to (-1.f, 1.f)
   constexpr float gain_in = 2.3f;

   for (size_t i = 0 ; i < NBR_AUDIO_CHANNELS ; ++i)
   {
      auto & frame = _onboard_codec_buffer_input [i];
      const auto & in_arr = in [i];

      for (size_t j = 0 ; j < erb_BUFFER_SIZE ; ++j)
      {
         frame [j] = gain_in * in_arr [j];
      }
   }

   _now_ms = (_now_spl * 1000) / sample_rate_ull;
   _now_spl += buffer_size_ull;

   do_notify_audio_buffer_start ();

   _buffer_callback ();

   do_notify_audio_buffer_end ();

   // Map (-1.f, 1.f) to eurorack audio level (-5V, 5V)
   // 10V / (0.7 x 3.3V x 10) = 0.433
   constexpr float gain_out = 0.433f;

   for (size_t i = 0 ; i < NBR_AUDIO_CHANNELS ; ++i)
   {
      auto & out_arr = out [i];
      const auto & frame = _onboard_codec_buffer_output [i];

      for (size_t j = 0 ; j < erb_BUFFER_SIZE ; ++j)
      {
         out_arr [j] = gain_out * frame [j];
      }
   }
}



BoardBase * BoardBase::_this_ptr = nullptr;



}  // namespace daisy
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
