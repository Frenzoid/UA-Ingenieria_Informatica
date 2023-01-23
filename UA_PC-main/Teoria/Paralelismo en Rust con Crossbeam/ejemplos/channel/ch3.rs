use crossbeam_channel::unbounded;

fn main(){

    let (s1, r1) = unbounded();
    
    // Clonamos la referencia.
    let (s2, r2) = (s1.clone(), r1.clone());
    let (s3, r3) = (s2.clone(), r2.clone());
    
    // Enviamos en orden s1, s2, s3.
    s1.send(10).unwrap();
    s2.send(20).unwrap();
    s3.send(30).unwrap();
    
    // Consumimos en orden, r3, r2, r1.
    //  pero el orden de los mensajes consumidos
    //  sigue siendo el mismo que cuando los producimos.
    println!("{}", r3.recv().unwrap());
    println!("{}", r2.recv().unwrap());
    println!("{}", r1.recv().unwrap());
}