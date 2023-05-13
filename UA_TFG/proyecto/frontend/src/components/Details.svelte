<!-- Details.svelte -->
<script>
  import { utils } from "ethers";
  import { onMount } from "svelte";
  import { contract } from "../controllers/web3Controller";

  export let projectId;
  let project;
  let fundsToDonate;
  let comment;
  let comments = [];

  let loading = "false";

  onMount(async () => {
    project = await contract.getProject(projectId);
    comments = await contract.getComments(projectId);
  });

  // Funcion para votar un proyecto
  async function voteProject(projectId, bool) {
    const tx = await contract.voteProject(projectId, bool);
    await tx.wait();

    project = await contract.getProject(projectId);
  }

  // Funcion para donar fondos a un proyecto
  async function investInProject(projectId) {
    loading = "investing";
    try {
      const tx = await contract.investInProject(projectId, {
        value: utils.parseEther(fundsToDonate),
      });
      await tx.wait();

      project = await contract.getProject(projectId);
    } finally {
      loading = "false";
    }
  }

  // funcion para comentar un proyecto
  async function addComment() {
    loading = "commenting";
    try {
      const tx = await contract.addComment(projectId, comment);
      await tx.wait();
      comments = await contract.getComments(projectId);
    } finally {
      loading = "false";
    }
  }
</script>

<div class="container">
  <h2 class="my-4">Detalles del Proyecto:</h2>

  {#if project}
    <div class="card">
      <div class="card-body">
        <h3 class="card-title">{project.title}</h3>
        <pre class="card-subtitle mb-2 text-muted">{project.proposer}</pre>
        <p class="card-text">{project.description}</p>
        <p>
          Fondos requeridos: {utils.formatEther(project.requiredFunds)} MATIC
        </p>
        <p>
          Fondos recaudados: {utils.formatEther(project.collectedFunds)} MATIC
        </p>
        <p>
          Tiempo total de desarrollo: {project.totalDevelopmentTime /
            60 /
            60 /
            24} días
        </p>
        <p>
          Fecha límite: {new Date(project.deadline * 1000).toLocaleDateString()}
        </p>
        <p>
          Votos totales: {project.totalVotes} ({project.positiveVotes} positivos)
        </p>
        <p>Estado: {project.state}</p>
      </div>
      {#if project.state == 0}
        <div
          class="card-footer d-flex justify-content-around
      {project.userVoted ? 'bg-success' : ''}"
        >
          {#if project.userVoted}
            <span class="badge bg-success">Ya has votado</span>
          {/if}
          {#if !project.userVoted}
            <button
              class="btn btn-success w-25"
              on:click={() => voteProject(projectId, true)}
            >
              <span role="img" aria-label="Pulgar hacia arriba mx-auto">👍</span
              >
            </button>
            <button
              class="btn btn-danger w-25"
              on:click={() => voteProject(projectId, false)}
            >
              <span role="img" aria-label="Pulgar hacia abajo">👎</span>
            </button>
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
              disabled={loading == "investing"}
            />
            {#if loading == "investing"}
              <button class="btn btn-primary" type="button" disabled>
                <span
                  class="spinner-border spinner-border-sm"
                  role="status"
                  aria-hidden="true"
                />
              </button>
            {:else}
              <button
                on:click={() => investInProject(projectId)}
                class="btn btn-primary"
              >
                Donar
              </button>
            {/if}
          </div>
        </div>
      {:else if project.state == 2}
        <div class="card-footer d-flex justify-content-around bg-warning">
          <span class="badge bg-warning text-dark">Proyecto finalizado</span>
        </div>
      {:else if project.state == 3}
        <div class="card-footer d-flex justify-content-around bg-danger">
          <span class="badge bg-danger">Proyecto cancelado</span>
        </div>
      {/if}
    </div>
    <div class="my-3 d-flex flex-row justify-content-evenly">
      {#if comments.length > 0}
        <div class="w-50">
          <h3>Comentarios:</h3>
          <ul class="list-group">
            {#each comments as comment}
              <li class="list-group-item">
                <div>
                  <img
                    width="50px"
                    src="https://avatars.dicebear.com/api/adventurer/{comment.author}.svg"
                    alt="avatar of {comment.author}"
                  />
                  <strong>{comment.author}</strong>
                </div>
                <br />
                <div class="ms-1 my-0 py-0">
                  {comment.message}
                </div>
                <small class="text-muted"
                  >{new Date(comment.date * 1000).toLocaleString()}</small
                >
              </li>
            {/each}
          </ul>
        </div>
      {/if}
      <div class="w-25">
        <div class="form-group">
          <h3>Añadir nuevo comentario:</h3>
          <textarea
            class="form-control"
            id="commentInput"
            bind:value={comment}
            rows="4"
          />
        </div>
        {#if loading != "commenting"}
          <button
            type="submit"
            class="btn btn-primary mt-2 w-100"
            on:click={addComment}>Enviar</button
          >
        {:else}
          <button type="submit" class="btn btn-primary mt-2 w-100" disabled>
            <div class="spinner-border mx-3" role="status">
              <span class="sr-only" />
            </div></button
          >
        {/if}
      </div>
    </div>
  {/if}
</div>
