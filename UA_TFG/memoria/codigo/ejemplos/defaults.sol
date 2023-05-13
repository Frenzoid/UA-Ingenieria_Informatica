  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >=0.7.0 <0.9.0;

  contract Contrato {
    // Se ejecuta cuandor recibe ether a través de una transferencia ordinaria.
    receive() external payable {
    }

    // Se ejecuta cuando se llama a una funcion inexistente.
    fallback() external payable {
    }
  }