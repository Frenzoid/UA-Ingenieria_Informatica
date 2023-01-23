class ProcessNode {
  public next: null | ProcessNode = null;
  public prev: null | ProcessNode = null;
  public start: number = 0;
  public end: number = 0;
  public empty: boolean = true;
  public aliveTime: number = 0;

  constructor(
    public process: string,
    public memory: number,
    public arrivalTime: number,
    aliveTime?: number,
    start?: number,
    end?: number,
  ) {
    if (start) this.start = start;
    if (end) this.end = end;
    if (process != "HUECO") this.empty = false;
    if (aliveTime) this.aliveTime = aliveTime;
  }

  public turnIntoProcess(node: ProcessNode): boolean {
    if (this.empty && !node.empty) {
      this.process = node.process;
      this.arrivalTime = node.arrivalTime;
      this.empty = false;
      return true;
    }

    console.log(
      "turnIntoProcess() => Reciving node empty or current node is not empty..",
    );
    return false;
  }

  public remove(): ProcessNode | boolean {
    if (!this.empty) {
      this.empty = true;
      this.process = "HUECO";

      return this.merge();
    }

    console.log("remove() => Failed removing node, node already empty.");
    return false;
  }

  public tick(): boolean {
    if (this.empty) return false;
    if (!this.empty) this.aliveTime--;
    if (this.aliveTime == 0) return true;
    return false;
  }

  private merge(): ProcessNode {
    // Si hay un hueco a la izquierda, se lo come y se vuelve uno.
    if (this.prev && this.prev.empty) {
      this.start = this.prev.start;
      this.memory += this.prev.memory;

      if (this.prev.prev) {
        this.prev.prev.next = this;
        this.prev = this.prev.prev;
      } else this.prev = null;
    }

    // Si hay un hueco a la derecha, se lo come y se vuelve uno.
    if (this.next && this.next.empty) {
      this.end = this.next.end;
      this.memory += this.next.memory;

      if (this.next.next) {
        this.next.next.prev = this;
        this.next = this.next.next;
      } else this.next = null;
    }

    return this;
  }

  public toString(): String {
    return `[ ${this.start} ${this.process} ${this.memory} ]`;
  }
}

class Memory {
  public first: null | ProcessNode = null;
  public last: null | ProcessNode = null;

  constructor(public memory: number) {
    this.first = this.last = new ProcessNode(
      "HUECO",
      this.memory,
      0,
      0,
      0,
      memory - 1,
    );
  }

  public toString(): string {
    let msg = "";
    let current: null | ProcessNode = this.first;

    while (current != null) {
      msg += current.toString();
      current = current.next;
    }

    return msg;
  }

  public worst(node: ProcessNode): boolean {
    let biggest: ProcessNode = new ProcessNode("COMPARISON_NODE", 0, 0);
    let current: null | ProcessNode = this.first;

    // Busca el hueco más grande.
    while (current != null) {
      if (
        (current.empty) &&
        (current.memory >= biggest.memory)
      ) {
        biggest = current;
      }

      current = current.next;
    }

    console.assert(
      this.insertIntoGap(biggest, node),
      "worst() => Failed inserting into gap",
    );
    return false;
  }

  public best(node: ProcessNode): boolean {
    let fittest: ProcessNode = new ProcessNode("COMPARISON_NODE", Infinity, 0);
    let current: null | ProcessNode = this.first;

    while (current != null) {
      // Busca el más pequeño, pero en el que pueda caber el proceso.
      if (
        (current.empty) &&
        (current.memory <= fittest.memory) && // Si es más pequeño que el actual.
        (current.memory >= node.memory) // Si es suficientemente grande para el proceso.
      ) {
        fittest = current;
      }
      current = current.next;
    }

    console.assert(
      this.insertIntoGap(fittest, node),
      "best() => Failed inserting into gap",
    );
    return true;
  }

  public insertIntoGap(
    emptyNode: ProcessNode,
    processNode: ProcessNode,
  ): boolean {
    // Primero comprobabmos el que el nodo realmente sea un nodo de un hueco y no de un proceso.
    // Despues comprobamos que el hueco es mayor o igual a la memoria del proceso.
    if (!emptyNode.empty) return false;
    if (emptyNode.memory < processNode.memory) return false;

    // Si ocupa lo mismo que el hueco exactamente, convierte el hueco en el proceso.
    if (emptyNode.memory == processNode.memory) {
      return emptyNode.turnIntoProcess(processNode);
    }

    // Enlazamos, primero comporbamos si detras del hueco habia algo.
    if (emptyNode.prev) {
      processNode.prev = emptyNode.prev;
      emptyNode.prev.next = processNode;
    }

    // Enlazamos los nodos entre si.
    processNode.next = emptyNode;
    emptyNode.prev = processNode;

    if (this.first === emptyNode) this.first = processNode;

    // Recalculamos el inicio y el final de cada.
    processNode.start = emptyNode.start;
    processNode.end = emptyNode.start + processNode.memory - 1;
    emptyNode.start = processNode.end + 1;
    emptyNode.memory -= processNode.memory;

    this.memory -= processNode.memory;

    return true;
  }

  public tick(): ProcessNode[] {
    let deadProcs: ProcessNode[] = [];
    let current: null | ProcessNode = this.first;

    while (current != null) {
      if (current.tick()) {
        deadProcs.push(
          Object.assign(Object.create(Object.getPrototypeOf(current)), current),
        );

        this.memory += current.memory;
        const vac: ProcessNode | boolean = current.remove();
        if (vac !== false && (vac as ProcessNode).start == 0) {
          this.first = vac as ProcessNode;
        }
      }

      current = current.next;
    }

    return deadProcs;
  }
}

// -- Main --

async function main(args: any) {
  if (args.length < 1) return false;
  const rammemory: number = 2000;
  const RAM: Memory = new Memory(rammemory);
  let processes: ProcessNode[] = [];

  (await Deno.readTextFile(args[0])).split("\n").forEach((txt_line) => {
    const procOnArr = txt_line.split(" ");
    processes.push(
      new ProcessNode(
        procOnArr[0],
        +procOnArr[2],
        +procOnArr[1],
        +procOnArr[3],
      ),
    );
  });

  processes.sort((b, a) => a.arrivalTime - b.arrivalTime);
  // processes.map((proc) => console.log(proc.arrivalTime, proc.aliveTime));

  let log: string = "";
  let iter: number = 1;

  console.log("Tick:", iter - 1, RAM.toString());
  log += `Tick: ${iter - 1} ${RAM.toString()}\n`;

  do {
    RAM.tick();

    while (
      args[1].toLowerCase() == "mejor" &&
      processes.length > 0 &&
      processes[processes.length - 1].arrivalTime == iter
    ) {
      RAM.best(processes.pop() as ProcessNode);
    }

    while (
      args[1].toLowerCase() == "peor" &&
      processes.length > 0 &&
      processes[processes.length - 1].arrivalTime == iter
    ) {
      RAM.worst(processes.pop() as ProcessNode);
    }

    iter++;
    console.log("Tick:", iter - 1, RAM.toString());
    log += `Tick: ${iter - 1} ${RAM.toString()}\n`;
  } while (RAM.memory !== rammemory);

  Deno.writeTextFile("./particiones.txt", log);
}

main(Deno.args);
