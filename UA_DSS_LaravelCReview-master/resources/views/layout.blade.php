<!doctype html>
<html lang="en">

<head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css"
        integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l" crossorigin="anonymous">
    <style>
    body {
        background-image: url('https://fondosmil.com/fondo/455.png');
        background-attachment: fixed;
    }

    @keyframes shake {
        0% {
            transform: skew(20deg);
        }
        100% {
            transform: skew(-20deg);
        }
    }

    .wiggle {
        animation: shake 0.1s infinite;
        animation-direction: alternate;
    }

    .wiggle-reverse {
        animation: shake 0.1s infinite;
        animation-direction: alternate-reverse;
    }
    </style>
    <title>UNIVERSITY REVIEWER</title>
</head>

<body>
    <!-- navegador -->
    <nav class="navbar navbar-expand-md navbar-dark bg-dark">
        <a class="navbar-brand" href="{{ url('/') }}">UNIVERSITY REVIEWER</a>
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target=".dual-collapse2">
            <span class="navbar-toggler-icon"></span>
        </button>
        <div class="navbar-collapse collapse w-100 order-3 dual-collapse2">
            <ul class="nav justify-content-center">
                <li class="nav-item">
                    <a class="nav-link" href="{{ url('/top-reviews') }}">Top Reviews</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="{{ url('/latest-reviews') }}">Latest Reviews</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="{{ url('/universities') }}">All Universities</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="{{ url('/about') }}">About</a>
                </li>
            </ul>
            <ul class="nav ml-auto">
            @if(!App\User::isLoggedIn())
                <li class="nav-item">
                    <a class="nav-link" href="{{ url('/login') }}">Log-In</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="{{ url('/register') }}">Register</a>
                </li>
            @else
                @if(App\User::isRoleOf("USER"))
                <li class="nav-item">
                    <a class="nav-link text-info" href="{{ url('/profile', App\User::currentUser()->id) }}">{{ App\User::currentUser()->name }}</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link text-primary" href="{{ url('/suggestion/new') }}">Create Suggestion</a>
                </li>
                @endif
                @if(App\User::isRoleOf("ADMIN"))
                <li class="nav-item">
                    <a class="nav-link text-warning" href="{{ url('/profile', App\User::currentUser()->id) }}">{{ App\User::currentUser()->name }}</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link text-warning" href="{{ url('/admin') }}">Admin Panel</a>
                </li>
                @endif
                <li class="nav-item">
                    <a class="nav-link text-primary" href="{{ url('/users') }}">Search Users</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link text-danger" href="{{ url('/logout') }}">Log-Out</a>
                </li>
            @endif
            </ul>
        </div>
    </nav>

    <div class="container mb-5 mt-4">
        <h1 class="text-center text-dark">@yield('title')</h1>
        
        @yield('content')

        @if($errors->any())
        <div class="card text-white bg-danger">
            <div class="card-header">
                Errors encountered, validation type.
            </div>
            <div class="card-body text-center">
            @foreach($errors->all() as $error)
                <h5 class="card-title">{{ $error }}</h5>
            @endforeach
            </div>
        </div>
        @endif
        
        @if(isset($customError))
        <div class="card text-white bg-danger">
            <div class="card-header">
                Errors encountered, data inconsistency type.
            </div>
            <div class="card-body text-center">
                <h5 class="card-title">{{ $customError }}</h5>
            </div>
        </div>
        @endif
        
    </div>

    <footer class="fixed-bottom footer pt-3 bg-dark">
        <div class="container font-italic">
            <p class="text-primary">Creado por: Elvi Mihai, Jose Luis, Eduardo Espuch, David Mendez. <span class="text-muted">Curso 2020/21.</span></p>
        </div>
    </footer>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"
        integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj"
        crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js"
        integrity="sha384-9/reFTGAW83EW2RDu2S0VKaIzap3H66lZH81PoYlFhbGU+6BZp6G7niu735Sk7lN"
        crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/js/bootstrap.min.js"
        integrity="sha384-+YQ4JLhjyBLPDQt//I+STsc9iw4uQqACwlvpslubQzn4u2UU2UFM80nGisd026JF"
        crossorigin="anonymous"></script>
</body>

</html>
