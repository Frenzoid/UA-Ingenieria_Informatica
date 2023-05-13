  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >=0.7.0 <0.9.0;

  contract Suma {
    modifier numerosPares(uint numero1, uint numero2) { 
      require(
      (numero1 % 2 == 0) && 
      (numero2 % 2 == 0), 
      "Uno de los dos numeros no es par");
      _;
    }
    
    function sumaPares (uint a, uint b) public pure numerosPares(a, b) returns (uint) { 
      return a + b;
    }
  }