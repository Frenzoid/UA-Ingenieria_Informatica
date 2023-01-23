use crossbeam_utils::sync::WaitGroup;
use crossbeam_utils::thread::scope;

fn main(){
    
    // Creamos un wg ( barrera ).
    let wg = WaitGroup::new();
    
    scope(|s| {
    
        // Creamos 4 hilos.
        for i in 0..4 {
        
            // Creamos otra referencia a la MISMA barrera.
            let wg = wg.clone();
    
            s.spawn(move |_| {
            
                // Logica del hilo.
                println!("El hilo {} hace cosas..", i);
                
                // Dropeamos la referencia, dando a entender que ya no necesitamos esperar.
                drop(wg);
            });
        }
        
        // Se bloque hasta que todas las referencias de dicha barrera ( wg ) estén dropeadas
        //    para continuar.
        wg.wait();
        print!("Todos los procesos han finalizado. :)");
        
    }).unwrap();

}