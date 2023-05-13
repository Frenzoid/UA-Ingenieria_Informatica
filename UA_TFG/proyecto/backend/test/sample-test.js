const { expect } = require("chai");
const { ethers } = require("hardhat");

describe("ProjectPlatformDemo", function () {
  it("Should return the new greeting once it's changed", async function () {
    const contract = await ethers.getContractFactory("ProjectPlatformDemo");
    const greeter = await contract.deploy();
    await greeter.deployed();

  });
});
