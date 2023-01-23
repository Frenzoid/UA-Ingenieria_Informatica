@extends('layout')

@section('title', 'Suggestions: ')

@section('content')

@foreach ($suggestions as $suggestion)
    <div class="card text-white bg-dark mb-1">
        <div onclick="showProfile({{$suggestion->user->id}})" class="card-header" style="cursor: pointer;">Submitter: <span class="text-primary"> {{ $suggestion->user->name }} </span></div>
        <div class="card-body">
            <p class="card-text text-justify font-italic text-primary">{{ $suggestion->suggestion }}</p>
        </div>
        <div class="card-footer">
            Created at: <span class="text-info"> {{ $suggestion->created_at }}</span>
            <br/>
            @if($suggestion->checked == 1)
                Seen by admins: <span class="text-success"> YES </span>
            @else
                Seen by admins: <span class="text-warning"> NO </span>
            @endif
        </div>
        @if(App\User::isLoggedIn() && App\User::currentUser()->id == $suggestion->user->id || App\User::isRoleOf('ADMIN'))
        <div class="d-flex justify-content-center">
            <form action="{{url('/suggestion', $suggestion->id)}}" style="width: 45%;" method="post">
                @csrf
                {{ method_field('DELETE') }}
                <button class="btn btn-danger m-3" style="width: 100%;" type="submit" >Delete</button>
            </form>
            @if($suggestion->checked == 0)
            <form class="ml-3" action="{{url('/suggestion', $suggestion->id)}}" style="width: 45%;" method="post">
                @csrf
                {{ method_field('PUT') }}
                <button class="btn btn-success m-3" style="width: 100%;" type="submit" >Mark as checked</button>
            </form>
            @endif
        </div>
        @endif
    </div>
    @endforeach

    </div>
    <div class="text-center d-flex justify-content-center m-5">
        {{ $suggestions->links() }}
    </div>
    <div class="container mb-5 mt-4">

    <script>
        function showProfile(id) {
            window.location.href = `{{url('/profile')}}/${id}`;
        }
    </script>
@endsection