  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >=0.7.0 <0.9.0;

  // Contrato para depositar Ether.
  contract Deposito {

    mapping(address => uint) balances;

    function depositar() public payable { 
      balances [msg.sender] += msg.value;
    }

    function retirar (uint256 cantidad) public {
      balances [msg.sender] -= cantidad;
      (bool success, ) = msg.sender.call{value: cantidad}(""); 
      require(success, "Fallo en la transferencia, revertiendo estado...");
    }

    function totalDepositadoPorTodos() public view returns (uint256) { 
      return address (this).balance;
    }
  }