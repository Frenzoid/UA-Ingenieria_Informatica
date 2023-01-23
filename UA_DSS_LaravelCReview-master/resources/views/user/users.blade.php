@extends('layout')

@section('title', 'Users')

@section('content')

<form action="{{ url('/users/search') }}" method="POST" class="form-group">
    @csrf
    <label for="search"> Search by name or email. </label>
    <div class="mb-3">
        <input class="form-control" name="search" type="text" id="search" autofocus></input>
        <button hidden type="submit" class="btn btn-primary">Search</button>
    </div>
</form>

@foreach($users as $user)
<div style="cursor: pointer;" class="card bg-dark mb-1 text-white" onclick="showProfile({{$user->id}})">
    <h5 class="card-header">
        <span class="text-primary">{{ $user->name }}</span> (<span class="text-info">{{ $user->email }}</span>) - 
        @if($user->role == 'ADMIN')
            <span class="text-warning">{{ $user->role }}</span>
        @else
            <span class="text-primary">{{ $user->role }}</span>
        @endif
    </h5>
</div>
@endforeach

</div>
<div class="text-center d-flex justify-content-center m-5">
    {{ $users->links() }}
</div>

<script>
    function showProfile(id) {
        window.location.href = `{{url('/profile/')}}/${id}`;
    }
</script>
@endsection