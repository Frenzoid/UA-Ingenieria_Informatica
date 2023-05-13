  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >=0.7.0 <0.9.0;

  contract Funciones {
  uint256 numero;

    function setNumero (uint256 _numero) public {
      numero = _numero;
    }

    function getNumero() public view returns (uint256) { 
      return numero;
    }

    function suma (uint256 a, uint256 b) public pure returns (uint256) {
      return a + b;
    }
  }