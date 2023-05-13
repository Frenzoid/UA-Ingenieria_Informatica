  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >=0.7.0 <0.9.0;
  contract Storage {

    /// @dev numero es una variable de estado almacenada en Storage.
    /// Por defecto, las variables declaradas a nivel de contrato se guardan en Storage.
    uint256 numero;

    /// @dev _numero es una variable recibida por parametro almacenada en calldata. 
    function store (uint[] calldata _numero) public {
      
      // Declaramos un array de enteros sin signo de tamaño 5.
      // Esta variable es local, y guardada en Memory.
      uint[] memory misNumeros = new uint[](5);

      // Guardamos en Storage el valor de la posicion del array _numero.
      numero = _numero[0];

      // Variable local, guardada en Memory.
      uint8 n = 4;

    }
  }