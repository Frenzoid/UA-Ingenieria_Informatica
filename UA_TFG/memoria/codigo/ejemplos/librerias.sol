  pragma solidity ^0.8.0;
  import "https://github.com/OpenZeppelin/openzeppelin-solidity/contracts/math/SafeMath.sol";
  
  contract SimpleContract {
      using SafeMath for uint256;
  
      uint256 public balance;
  
      function deposit(uint256 _value) public {
          balance = balance.add(_value);
      }
  
      function withdraw(uint256 _value) public {
          require(balance >= _value, "Insufficient balance.");
          balance = balance.sub(_value);
      }
  }