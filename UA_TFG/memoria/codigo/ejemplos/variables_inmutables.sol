  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >-0.7.0 <0.9.0;
  contract Immutable {
  
    address immutable MY_ADDRESS;
    uint immutable MY_UINT;
  
    constructor(uint _myUint) { 
      MY_ADDRESS = msg.sender;
      MY_UINT = _myUint;
    }
    
  }