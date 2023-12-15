#include <iostream>
#include <iomanip>
#include <ios>
#include <cstdio>
#include <stdint.h>

#include "RegisterMap.hh"
#include "FPGAModule.hh"
#include "UDPRBCP.hh"

// Main ___________________________________________________________________________
using namespace HUL;
using namespace LBUS;
int main(int argc, char* argv[])
{
  if(1 == argc || 2 == argc){
    std::cout << "Usage\n";
    std::cout << "set_hgddelay [IP address] [parameter]" << std::endl;
    std::cout << " Parameter range: 1-32 \n";
    std::cout << " Adjust the dealy for the hold signal with 32 steps in 2ns.\n";
    return 0;
  }// usage
  
  // body ------------------------------------------------------
  std::string board_ip = argv[1];
  uint32_t value = atoi(argv[2]);
  uint32_t reg   = 1 << (value-1);
  
  RBCP::UDPRBCP udp_rbcp(board_ip, RBCP::gUdpPort, RBCP::DebugMode::kNoDisp);
  HUL::FPGAModule fpga_module(udp_rbcp);

  fpga_module.WriteModule(HGD::kAddrMask, reg, 4);

  return 0;

}// main
