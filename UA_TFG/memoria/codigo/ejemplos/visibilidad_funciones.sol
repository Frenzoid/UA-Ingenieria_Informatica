  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >=0.7.0 <0.9.0;
  contract Funciones {
  
    // Cualquier puede llamar a esta funcion f1.
    function f1() public {  }
  
    // Solo cuentas externas puede a f2.
    function f2() external {  }
  
    // Solo el contracto actual y heredados pueden llamar a f3.
    function f3() private {  }
  
    // Solo el contrato actual puede llamar a f4.
    function f4() internal {  }
  }