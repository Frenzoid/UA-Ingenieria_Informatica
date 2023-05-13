<script>
  import "bootstrap/dist/css/bootstrap.min.css";
  import {
    onUndetectedWallet,
    onWalletConnected,
    onWrongNetwork,
  } from "./stores/web3Store";
  import { onArtifactImported } from "./stores/importStore";
  import { connect, getSigner } from "./controllers/web3Controller";
  import { DEPLOYED_NETWORK } from "./config/constants/contract";

  import Lista from "./components/Lista.svelte";
  import Crear from "./components/Crear.svelte";
  import Details from "./components/Details.svelte";

  const PAGE = {
    PROJECTLIST: "projectList",
    PROJECTCREATION: "projectCreation",
    MYPROJECTS: "myProjects",
  };

  let show = PAGE.PROJECTLIST;
  let account;

  function changePage(page) {
    show = page;
  }

  onWalletConnected.subscribe(async (value) => {
    if (value == true) {
      account = await getSigner().getAddress();
    }
  });
</script>

{#if $onArtifactImported}
  <div>
    {#if $onUndetectedWallet}
      <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
        <div class="container-fluid mx-4">
          <a class="navbar-brand" href="/">UACrowdFunder</a>
          <button class="btn btn-danger" on:click={connect}
            >Conectar la cartera</button
          >
        </div>
      </nav>
      <div class="text-center mt-5">
        <h1>! Instala Metamask !</h1>
        <h3>
          Para poder obtener los datos de la blockchain tendrás que instalar la
          extension de Metamask
        </h3>
      </div>
    {/if}
    {#if !$onWalletConnected && !$onUndetectedWallet}
      <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
        <div class="container-fluid mx-4">
          <a class="navbar-brand" href="/">UACrowdFunder</a>
          <button class="btn btn-success" on:click={connect}
            >Conectar la cartera</button
          >
        </div>
      </nav>
      <div class="text-center mt-5">
        <h1>Conecta tu cartera :)</h1>
        <h3>
          Para poder obtener los datos de la blockchain tendrás que conectar tu
          cartera
        </h3>
      </div>
    {/if}
    {#if $onWalletConnected && $onWrongNetwork}
      <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
        <div class="container-fluid mx-4">
          <a class="navbar-brand" href="/">UACrowdFunder</a>
        </div>
        <div>
          <img
            width="50px"
            src="https://avatars.dicebear.com/api/adventurer/{account}.svg"
            alt="avatar of {account}"
          />
        </div>
      </nav>
      <div class="text-center mt-5">
        <h1>Red equivocada!</h1>
        <h3>
          Red equivocada! Tu cartera está conectada a la red equivocada,
          conectala a la red: {DEPLOYED_NETWORK.name}
        </h3>
      </div>
    {/if}
    {#if $onWalletConnected && !$onWrongNetwork}
      <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
        <div class="container-fluid mx-4">
          <a class="navbar-brand" href="/">UACrowdFunder</a>
          <div class="navbar-collapse" id="navbarNav">
            <ul class="navbar-nav">
              <li class="nav-item">
                <a
                  class="nav-link"
                  href="/"
                  on:click|preventDefault={() => changePage(PAGE.PROJECTLIST)}
                  >Lista de Proyectos</a
                >
              </li>
              <li class="nav-item">
                <a
                  class="nav-link"
                  href="/"
                  on:click|preventDefault={() =>
                    changePage(PAGE.PROJECTCREATION)}>Publicar Proyecto</a
                >
              </li>
              <li class="nav-item">
                <a
                  class="nav-link"
                  href="/"
                  on:click|preventDefault={() => changePage(PAGE.MYPROJECTS)}
                  >Mis Proyectos</a
                >
              </li>
            </ul>
          </div>
          <div>
            <img
              width="50px"
              src="https://avatars.dicebear.com/api/adventurer/{account}.svg"
              alt="avatar of {account}"
            />
          </div>
        </div>
      </nav>
      <div class="mx-5 pb-5">
        {#if show === PAGE.PROJECTLIST}
          <Lista {changePage} />
        {/if}

        {#if typeof show === "number"}
          <Details projectId={show} />
        {/if}

        {#if show === PAGE.PROJECTCREATION}
          <Crear {changePage} />
        {/if}

        {#if show === PAGE.MYPROJECTS}
          <Lista {changePage} proposer={account} />
        {/if}
      </div>
    {/if}
    <footer class="bg-dark text-center footer py-2 footer">
      <div class="container">
        <a
          class="text-white text-decoration-none"
          href="https://github.com/frenzoid"
          role="button"
          ><i class="fab fa-github" /> Made by Frenzoid ( Elvi Mihai Sabau Sabau
          ) - Universidad de Alicante.</a
        >
      </div>
    </footer>
  </div>
{/if}

<style>
  footer {
    position: fixed;
    height: 40px;
    bottom: 0;
    width: 100%;
  }
</style>
