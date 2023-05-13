  // SPDX-License-Identifier: GPL-3.0
  pragma solidity >=0.7.0 <0.9.0;


  contract Acontract {
    
    string name;

    // Constructor. 
    constructor(string memory _name) { 
      name = _name;
    }
  }


  // Herencia.
  contract Constructor is Acontract {

    uint number;

    // Acontract() Es la lamada al constructor padre desde el constructor del mismo.
    constructor(string memory _name, uint _number) Acontract(_name) { 
        number = _number;
    }
  }