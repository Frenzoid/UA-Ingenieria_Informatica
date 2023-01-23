use crossbeam_channel::bounded;

fn main(){
    
    // Crea un canal que solo puede tener 5 mensajes sin consumir.
    let (s, _r) = bounded(5);
    
    // Solo se pueden mandar 5 mensajes sin quedarse bloqueado.
    for i in 0..5 {
        s.send(i).unwrap();
    }
    
    // Otra llamada a "send" bloquearía el canal porque el canal estaria lleno.
    // s.send(5).unwrap();
}