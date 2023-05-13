<!-- Lista.svelte -->
<script>
  import { contract } from "../controllers/web3Controller";
  import { utils } from "ethers";
  import { onMount } from "svelte";

  export let proposer = null;
  export let changePage;

  const ProjectState = {
    0: "Pendiente de Votación",
    1: "Pendiente de Financiación",
    2: "Finalizado",
    3: "Cancelado",
  };

  let projects = [];
  let fundsToDonate;
  let loading = -1;
  let projectsCount = -1;

  // Obtenemos los proyectos
  onMount(async () => {
    projectsCount = (await contract.getProjectsCount()).toNumber();
    for (let i = 0; i < projectsCount; i++) {
      const project = await contract.getProject(i);

      if (!proposer || proposer == project.proposer)
        projects = [...projects, project];
    }
  });

  // Funcion para votar un proyecto
  async function voteProject(projectId, bool) {
    loading = projectId;
    try {
      const tx = await contract.voteProject(projectId, bool);
      await tx.wait();

      const project = await contract.getProject(projectId);
      projects[projectId] = { ...project };
    } finally {
      loading = -1;
    }
  }

  // Funcion para donar fondos a un proyecto
  async function investInProject(projectId) {
    loading = projectId;
    try {
      const tx = await contract.investInProject(projectId, {
        value: utils.parseEther(fundsToDonate),
      });
      await tx.wait();

      const project = await contract.getProject(projectId);
      projects[projectId] = { ...project };
    } finally {
      loading = -1;
    }
  }
</script>

{#if projectsCount != -1 && projects.length > 0}
  {#if proposer}
    <h2 class="my-4">Tus Proyectos:</h2>
  {:else}
    <h2 class="my-4">Lista de Proyectos:</h2>
  {/if}
  <div class="row">
    {#each projects as project, i}
      <div class="col-md-6 col-lg-4 mb-4">
        <div class="card h-100">
          <div class="card-body" on:click={() => changePage(i)}>
            <h4 class="card-title">Titulo: <i>{project.title}</i></h4>
            <h6 class="card-subtitle mb-2 text-muted">
              Proponente: <pre>{project.proposer}</pre>
            </h6>
            <h5>Descripción:</h5>
            <div class="card-text text-muted text-justify">
              {project.description}
            </div>
            <hr />
            <p>
              Fondos necesarios: {utils.formatEther(project.requiredFunds)} MATIC
            </p>
            {#if project.state == 1}
              <p>
                Fondos recaudados: {utils.formatEther(project.collectedFunds)} MATIC
              </p>
            {/if}
            <p>
              Tiempo de desarrollo: {project.totalDevelopmentTime /
                60 /
                60 /
                24} Días
            </p>
            <p>Estado: {ProjectState[project.state]}</p>
            {#if project.state == 0}
              <hr />
              <p>
                Fecha límite para votar: {new Date(
                  project.deadline * 1000
                ).toLocaleDateString("es-ES")}
              </p>
              <p>Votos totales: {project.totalVotes}</p>
              <p>Votos positivos: {project.positiveVotes}</p>
            {/if}
          </div>
          {#if project.state == 0}
            <div
              class="card-footer d-flex justify-content-around
            {project.userVoted ? 'bg-success' : ''}"
            >
              {#if project.userVoted}
                <span class="badge bg-success">Ya has votado</span>
              {/if}
              {#if !project.userVoted && loading != i}
                <button
                  class="btn btn-success w-25"
                  on:click={() => voteProject(i, true)}
                >
                  <span role="img" aria-label="Pulgar hacia arriba mx-auto"
                    >👍</span
                  >
                </button>
                <button
                  class="btn btn-danger w-25"
                  on:click={() => voteProject(i, false)}
                >
                  <span role="img" aria-label="Pulgar hacia abajo">👎</span>
                </button>
              {/if}
              {#if loading == i}
                <div class="spinner-border text-primary" role="status">
                  <span class="visually-hidden">Procesando transacción</span>
                </div>
              {/if}
            </div>
          {:else if project.state == 1}
            <div class="m-2">
              <div class="progress mb-2">
                <div
                  class="progress-bar"
                  role="progressbar"
                  style={"Width: " +
                    (+utils.formatEther(project.collectedFunds) /
                      +utils.formatEther(project.requiredFunds)) *
                      100 +
                    "%"}
                >
                  {(
                    (+utils.formatEther(project.collectedFunds) /
                      +utils.formatEther(project.requiredFunds)) *
                    100
                  ).toFixed(2)}%
                </div>
              </div>
              <div class="d-flex flex-row">
                <input
                  bind:value={fundsToDonate}
                  type="text"
                  class="form-control me-2"
                  placeholder="Fondos a donar en MATIC"
                  disabled={loading == i}
                />
                {#if loading == i}
                  <button class="btn btn-primary" type="button" disabled>
                    <span
                      class="spinner-border spinner-border-sm"
                      role="status"
                      aria-hidden="true"
                    />
                  </button>
                {:else}
                  <button
                    on:click={() => investInProject(i)}
                    class="btn btn-primary">Donar</button
                  >
                {/if}
              </div>
            </div>
          {:else if project.state == 2}
            <div class="card-footer d-flex justify-content-around bg-warning">
              <span class="badge bg-warning text-dark">Proyecto finalizado</span
              >
            </div>
          {:else if project.state == 3}
            <div class="card-footer d-flex justify-content-around bg-danger">
              <span class="badge bg-danger">Proyecto cancelado</span>
            </div>
          {/if}
        </div>
      </div>
    {/each}
  </div>
{:else if projectsCount == 0}
  <h2 class="my-4">No hay proyectos</h2>
{:else if projectsCount != 0 && projectsCount != -1 && projects.length == 0}
  <h2 class="my-4">No tienes proyectos propuestos</h2>
{:else}
  <h2 class="my-4">
    <div class="spinner-border text-black" role="status" />
    Cargando proyectos...
  </h2>
{/if}
