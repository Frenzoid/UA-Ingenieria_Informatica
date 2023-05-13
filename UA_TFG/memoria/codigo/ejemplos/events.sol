  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >=0.7.0 <0.9.0;

  contract Contrato {
    
    address direccionContratoExterno;

    constructor(address _dirContExterno) {
      direccionContratoExterno = _dirContExterno;
    }

    // Definimos la estrucutra del evento ( los datos a loggear ). 
    event Tranferencia(address indexed destino, uint etherEnviado);

    function enviarEther() public {
      // Enviamos 1 ether del contrato al usuario que llama la función. 
      (bool success,) = msg.sender.call{value: 1 ether }("");
      require(success);

      // Emitimos el evento.
      emit Tranferencia (msg.sender, 1 ether);
    }
  }