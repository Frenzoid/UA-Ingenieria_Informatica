use crossbeam_channel::bounded;
use crossbeam_utils::thread::scope;

fn main() {
    /***
     * Un caso especial de channel con capacidad cero, que no puede contener ningún mensaje.
     * Las operaciones de envío y recepción deben ejecutarse al mismo tiempo para sincronizar y pasar el mensaje.
     */

    let (prod, cons) = bounded::<&str>(0);

    scope(|s| {
        // Crea un hilo que se espera a leer un mensaje, y envia otro.
        s.spawn(|_| {
            println!("{}", cons.recv().unwrap()); // => Envio mensaje al hilo hijo.
            prod.send("Envio mensaje al hilo principal.").unwrap();
        });

        // Envia un mensjae y se espera a leer.
        prod.send("Envio mensaje al hilo hijo.").unwrap();
        println!("{}", cons.recv().unwrap()); // => Envio mensaje al hilo hijo
    })
    .unwrap();
}
