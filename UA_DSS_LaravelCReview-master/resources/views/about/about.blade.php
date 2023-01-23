@extends('layout')

@section('title', 'About')

@section('content')

<div class="m-3 justify-content-center">
    <div class="card">

        <div class="bg-image rounded" style="background-image: url('https://fondosmil.com/fondo/23222.jpg');">
            <div class="card-body text-white" >
                <h5>University Reviewer es una aplicación realizada por el equipo CREVIEW con la intención de conectar a estudiantes, ofreciendole la oportunidad de conocer 
                las opiniones de diversos compañeros respecto a las asignaturas que han cursado. Las opiniones puedes realizarse sobre la asignatura o sobre las reviews 
                realizadas. Es posible ver todas las reviews de una asignatura al acceder a la información de ésta misma. 
                <br><br>
                Cualquier usuario registrado es libre de realizar sugerencias a los Admin y poder mejorar la aplicación.</h5>
        </div>
    </div>
</div>

<hr>
<h3 class="text-center text-dark">Admin comments:</h3>

<div class="m-3 justify-content-center">

        <div class="bg-image rounded" style="background-image: url('https://fondosmil.com/fondo/23222.jpg');">
            <div class="card-body text-white" >
                <blockquote class="blockquote">
                    <p class="font-italic">ᵃ</p>
                    <footer class="blockquote-footer text-white">ADMIN - David</footer>
                </blockquote>
            </div>
        </div>
        <hr>
        <div class="bg-dark" style="background: url('https://pngimage.net/wp-content/uploads/2018/06/red-footer-png-3.png') no-repeat; background-size: cover;)">
            <div class="card-body text-white">
                <blockquote class="blockquote">
                    <p class="font-italic" 
                    style="">The "state" in Bitcoin is the collection of all coins (technically, "unspent transaction outputs" or UTXO) that have been mined and not yet spent, 
                    with each UTXO having a denomination and an owner (defined by a 20-byte address which is essentially a cryptographic public keyfn. 1). A transaction contains 
                    one or more inputs, with each input containing a reference to an existing UTXO and a cryptographic signature produced by the private key associated with the 
                    owner's address, and one or more outputs, with each output containing a new UTXO to be added to the state.</p>
                    <footer class="blockquote-footer text-white">ADMIN - Elvi</footer>
                </blockquote>
            </div>
        </div>
        <hr>
        <div class="bg-image rounded" style="background-image: url('https://fondosmil.com/fondo/23222.jpg');">
            <div class="card-body text-white" >
                <blockquote class="blockquote">
                    <p class="font-italic">"No soy muy original para estas cosas, os lo dejo a vosotros"</p>
                    <footer class="blockquote-footer text-white">ADMIN - Jose Luis</footer>
                </blockquote>
            </div>
        </div>
        <hr>
        <div class="bg-image rounded" style="background-image: url('https://fondosmil.com/fondo/23222.jpg');">
            <div class="card-body text-white" >
                <blockquote class="blockquote">
                    <p class="font-italic">Ser #TeamJagger es ser parte del pueblo. ᵃ</p>
                    <footer class="blockquote-footer text-white">ADMIN - Eduardo</footer>
                </blockquote>
            </div>
        </div>
        <hr>
</div>

@endsection