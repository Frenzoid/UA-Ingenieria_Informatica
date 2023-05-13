  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >=0.7.0 <0.9.0;
  
  contract ContratoExterno {
    function saludo(string memory nombre) external pure returns(string memory) {
      return string (bytes.concat("Hola ", bytes (nombre)));
    }
  }
  
  contract Contrato {
    address direccionContratoExterno;
    constructor(address _dirContExterno) {
      direccionContratoExterno = _dirContExterno;
    }
  
    function saludar(string memory nombre) public payable returns (string memory) { 
      // .call devuelve (bool, bytes).
      // Si la llamada ha sido una transaccion ordinaria de ether, bool se debe comprobar, bytes son datos sobre la transferencia.
      // Si la llamada ha sido una llamada a otra funcion de otro contrato, bytes almacenará los datos devueltos.
      (bool success, bytes memory data) = direccionContratoExterno.call(abi.encodeWithSignature("saludo(string)", nombre));
  
      require(success, "Fallo al llamar a ContratoExterno.saludo.");
      return string(data);
    }
  }