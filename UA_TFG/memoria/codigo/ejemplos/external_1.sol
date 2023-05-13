  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >=0.7.0 <0.9.0;
  
  contract ContratoExterno {
    function saludo (string memory nombre) external pure returns (string memory) { 
      return string(bytes.concat("Hola", bytes (nombre)));
    }
  }

  contract Contrato {
    address direccionContratoExterno;
    constructor(address _dirContExterno) {
      direccionContratoExterno = _dirContExterno;
    }

    function saludar(string memory nombre) public payable returns (string memory) {
      return ContratoExterno(direccionContratoExterno).saludo(nombre);
    }
  }