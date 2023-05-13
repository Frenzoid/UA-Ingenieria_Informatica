  // SPDX-License-Identifier: GPL-3.0 
  pragma solidity >=0.7.0 <0.9.0;
  contract Variables {

    uint numeroSinSigno;
    int numeroConSigno;
    string nombre;
    bytes2 dosChars;
    address direccionCuenta;

    // Mapping es la equivalencia a un diccionario en Solidity.
    mapping(address => string) nombres;
    
    struct persona {
      string nombre;
      uint edad;
    }

    function setNombre (address _direccion, string memory _nombre) public {
      nombres[_direccion] = _nombre;
    }
  }