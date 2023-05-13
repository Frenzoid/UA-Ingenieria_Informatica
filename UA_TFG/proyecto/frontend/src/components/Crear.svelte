<!-- Crear.svelte -->
<script>
  import { contract } from "../controllers/web3Controller";

  export let changePage;

  let title = "";
  let description = "";
  let fundingGoal = 0;
  let totalDevelopmentTime = 0;

  let errorMsg = "";
  let loading = false;

  async function createProject() {
    try {
      errorMsg = "";
      loading = true;

      let id = (await contract.getProjectsCount()).toNumber();

      const tx = await contract.proposeProject(
        title,
        description,
        fundingGoal,
        totalDevelopmentTime
      );

      await tx.wait();

      changePage(id);
      console.log("Project created successfully!");
    } catch (error) {
      console.error(error);
      if (error.error.data.message) {
        errorMsg = error.error.data.message;
      }
    } finally {
      loading = false;
    }
  }
</script>

<div class="mt-4 container">
  <h2>Proponer proyecto:</h2>
  <form>
    <div class="mb-3">
      <label for="title" class="form-label">Titulo del proyecto</label>
      <input
        type="text"
        class="form-control"
        id="title"
        bind:value={title}
        placeholder="Titulo del proyecto"
      />
    </div>
    <div class="mb-3">
      <label for="description" class="form-label">Descripcion</label>
      <textarea
        class="form-control"
        id="description"
        rows="3"
        bind:value={description}
        placeholder="Descripcion del proyecto"
      />
    </div>
    <div class="mb-3">
      <label for="fundingGoal" class="form-label"
        >Fondos Necesarios ( MATIC )</label
      >
      <input
        type="number"
        class="form-control"
        id="fundingGoal"
        bind:value={fundingGoal}
        placeholder="Fondos necesario en MATIC"
      />
    </div>
    <div class="mb-3">
      <label for="totalDevelopmentTime" class="form-label"
        >Tiempo total para el desarollo ( Días )</label
      >
      <input
        type="number"
        class="form-control"
        id="totalDevelopmentTime"
        bind:value={totalDevelopmentTime}
        placeholder="Tiempo total necesario para el desarollo ( en días )"
      />
    </div>
    <button type="button" class="btn btn-primary" on:click={createProject}
      >Proponer Proyecto</button
    >
  </form>
  {#if loading}
    <div class="alert alert-primary mt-4" role="alert">
      <div class="spinner-border mx-3" role="status">
        <span class="sr-only" />
      </div>
      Transacción en proceso...
    </div>
  {/if}
  {#if errorMsg}
    <div class="alert alert-danger mt-4" role="alert">
      {errorMsg}
    </div>
  {/if}
</div>
