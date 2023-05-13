  contract Funciones {
    // Método A
    function f1() public pure returns (uint){
      uint numero= 1;
      return numero;
    }

    // Método B
    function f2() public pure returns (uint numero){
      numero = 1;
    }


    // Devuelve varias variables
    function devuelve2() internal pure returns (uint a, string b) {
      a = 1;
      b = "hola";
    }
    
    // Captura las variables
    function captura2() public pure {
      (uint numero, string memory palabra) = devuelve2();
    }
  }