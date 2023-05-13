  function enviarEther() public {
    bool success = payable(msg.sender).send(1 ether);
    require(success);
  }

  function enviarEther() public {
    payable(msg.sender).transfer (1 ether);
  }
  
  function enviarEther() public {
    // Modo 1, especificando el gas máximo a usar.
    (bool success1, ) = msg.sender.call{value: 1 ether, gas: 500000}("");
    
    // Modo 2, sin especificar el gas.
    (bool success2, ) = msg.sender.call{value: 1 ether }("");

    require(success1 && success2);
  }