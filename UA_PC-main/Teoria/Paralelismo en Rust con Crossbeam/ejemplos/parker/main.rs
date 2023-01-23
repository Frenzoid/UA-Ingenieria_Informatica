use std::thread;
use std::time::Duration;
use crossbeam_utils::sync::Parker;

fn main(){

    let p = Parker::new();
    let u = p.unparker().clone();
    
    // Crea una señal que será consumida por el siguiente p.park().
    u.unpark();
    
    println!("Hilo Principal: Me voy a aparcar.");
    
    // Consume la señal y permite que el proceso continue, 
    //   si no hubiera una señal, el proceso se quedaria 
    //   aparcado hasta que una señal fuera generada por u.unpark().
    p.park();
    
    println!("Hilo Principal: Estoy aparcado!");
    
    thread::spawn(move || {
        println!("Hilo Hijo: Me espero 2 segundos.");
        thread::sleep(Duration::from_millis(2000));
        println!("Hilo Hijo: Desaparco el hilo principal.");
        u.unpark();
    });
    
    // El proceso se queda aparcado hasta que algún otro hilo genere
    //   una señal para desaparcar.
    p.park();
    
    println!("Hilo Principal: Ya estoy de vuelta.");

}