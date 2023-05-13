// SPDX-License-Identifier: MIT
pragma solidity ^0.8.17;

contract Counter {
    uint public count;

    // Funcion para obtener el valor de "count"
    function get() public view returns (uint) {
        return count;
    }

    // Funcion para incrementar count
    function inc() public {
        count += 1;
    }

    // Funcion para decrementar count 
    function dec() public {
        // Esta funcion fallara si count = 0, esto se debe al tipo de count
        count -= 1;
    }
}