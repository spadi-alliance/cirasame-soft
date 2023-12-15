#ifndef REGISTER_HH
#define REGISTER_HH

#include"RegisterMapCommon.hh"

namespace LBUS{
  //-------------------------------------------------------------------------
  // HGD
  //-------------------------------------------------------------------------
  namespace HGD{
    enum LocalAddress
      {
	kAddrMask        = 0x10000000  // W/R, [31:0] Delay line mask
      };
  };
  
  //-------------------------------------------------------------------------
  // AD9220
  //-------------------------------------------------------------------------
  namespace AD9220{
    enum LocalAddress
      {
	kAddrDaqGate     = 0x20000000, // W/R, [0:0] ADC DAQ gate
	kAddrEventFull   = 0x20100000, // R,   [0:0] ADC event fifo is full
	kAddrReadFIFO    = 0x21000000, // R,   FIFO read sequence
	kAddrReleaseBusy = 0x22000000  // W,   Release busy (event full)
      };
  };


  
};


#endif
