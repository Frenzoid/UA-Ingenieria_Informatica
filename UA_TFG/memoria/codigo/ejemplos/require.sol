  // SPDX-License-Identifier: GPL-3.0 
  pragma solidity >=0.7.0 <0.9.0;

  contract Deposito {
    address propietario;
    mapping(address => uint) balances;

    // Cuando el contrato se despliega en la red, se setea "propietario" con la 
    // Direccion de la cuenta ( usuario ) que ha desplegado el contrato. propietario msg.sender;
    constructor() {
      propietario = msg.sender;
    }
    
    function depositar() public payable {
      // ...
    }

    function retirar (uint cantidad) public { 
      // ...
    }

    // Función que vacia el contrto, solo puede ser ejecutada por el propietario.
    function vaciar() public {
      // Si la condicion falla, se revierte con el mensaje de error. 
      require(msg.sender == propietario, "El usuario no es el propietario!");

      // Se envia el Ether al propietario del contrato. Devuelve un booleano que indica si la transacción fue exitosa.
      (bool success, ) = msg.sender.call{value: address(this).balance}("");

      // Si la transaccion no fue exitosa, se revierte con el mensaje de error.
      require(success, "Error en la transferencia de Ether");
    }
  }