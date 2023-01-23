use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let mut hilos = vec![];
    let contador = Arc::new(Mutex::new(0));

    for i in 0..5 {
        // Clonamos el contador
        let contador = contador.clone();

        // Creamos un hilo
        let hilo = thread::spawn(move || {
            let mut num = contador.lock().unwrap();

            for _ in 0..50000 {
                *num += 1;
            }

            println!("Hilo: {}, contador: {}", i, *num);
        });

        hilos.push(hilo);
    }

    for hilo in hilos {
        hilo.join().unwrap();
    }

    println!("\nContador: {} == {}", *contador.lock().unwrap(), 250000);
}
