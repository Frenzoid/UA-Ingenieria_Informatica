    // SPDX-License-Identifier: GPL-3.0
    pragma solidity >=0.7.0 <0.9.0;
    
    contract Deposito {
      address propietario;
      
      constructor() {
        propietario = msg.sender;
      }
    
      // Modificador que comprueba si el usuario que ha llamado a la funcion es el propietario.
      modifier soloPropietario() {
        require(msg.sender == propietario, "El usuario no es el propietario!");
    
        // Ahora se ejecuta la funcion a la que se adjunta el modificador.
        _; 
      }
    
      // Adjuntamos el modificador a la función vaciar().
      function vaciar() public soloPropietario {
        (bool success, ) = msg.sender.call{value: address(this).balance}("");
        require(success, "Error en la transferencia de Ether");
      }
    }