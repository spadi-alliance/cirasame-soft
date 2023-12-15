#include <iostream>
#include <iomanip>
#include <fstream>
#include <ios>
#include <cstdio>

#include "RegisterMap.hh"
#include "FPGAModule.hh"
#include "UDPRBCP.hh"

// Main ___________________________________________________________________________
enum argIndex{kBin, kIp, kFilePath, kEventNo};
using namespace HUL;
using namespace LBUS;
int main(int argc, char* argv[])
{
  if(1 == argc){
    std::cout << "Usage\n";
    std::cout << "read_ad9220 [IP address] [output file path] [# of events]" << std::endl;
    return 0;
  }// usage
  
  // body ------------------------------------------------------
  const std::string kBoardIp  = argv[kIp];
  const std::string kOutPath  = argv[kFilePath];
  const int32_t kEventNum     = atoi(argv[kEventNo]);

  std::ofstream ofs(kOutPath.c_str(), std::ios::binary);
  if(!ofs.is_open()){
    std::cerr << "#E: File cannot be not created (" << kFilePath << ")." << std::endl;
    return 0;
  }

  RBCP::UDPRBCP udp_rbcp(kBoardIp, RBCP::gUdpPort, RBCP::DebugMode::kNoDisp);
  HUL::FPGAModule fpga_module(udp_rbcp);

  fpga_module.WriteModule(AD9220::kAddrDaqGate, 0);
  fpga_module.WriteModule(AD9220::kAddrDaqGate, 1);
  

  const uint32_t kReadLength = 33*4*2;
  uint8_t fifo_data[kReadLength];

  for(int i = 0; i<kEventNum; ++i){
    while(0 == fpga_module.ReadModule(AD9220::kAddrEventFull, 1));

    for(int i = 0; i<2; ++i){
      fpga_module.ReadModule_nByte(AD9220::kAddrReadFIFO, kReadLength/2);
      auto itr_begin = fpga_module.GetDataIteratorBegin();
      auto itr_end   = fpga_module.GetDataIteratorEnd();
      std::copy(itr_begin, itr_end, fifo_data + i*kReadLength/2);
    }

    ofs.write((char*)fifo_data, kReadLength);
  
    fpga_module.WriteModule(AD9220::kAddrReleaseBusy, 0);

    if(i%100 == 0) std::cout << "#D: Event num: " << i+1 << std::endl;
  }

  ofs.close();

  fpga_module.WriteModule(AD9220::kAddrDaqGate, 0);
  fpga_module.WriteModule(AD9220::kAddrReleaseBusy, 0);


  return 0;

}// main
