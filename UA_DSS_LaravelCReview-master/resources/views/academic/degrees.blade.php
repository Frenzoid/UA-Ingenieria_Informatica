@extends('layout')

@section('title', $university->name)

@section('content')
<div class="d-flex flex-row flex-wrap justify-content-center">
    @php
        $degrees = $university->degrees()->simplePaginate(5);
    @endphp
    @foreach ($degrees as $degree)
    <div  class="card text-white bg-dark m-1" style="width: 22rem;">
        <div onclick="goToSubjects({{$degree->id}})" style="cursor: pointer;" class="card-header text-warning">{{ $degree->name }}</div>
        <div onclick="goToSubjects({{$degree->id}})" style="cursor: pointer;" class="card-body">
            <p class="card-text">Description: <i class="text-info">{{ $degree->description }}</i></p>
            <p class="card-text">Number of years: <span class="text-info">{{ $degree->years }}</span></p>
            <p class="card-text">General satisfaction: <span class="text-primary">{{ round($degree->getAvgSatisfaction(), 2) }} / 10</span></p>
        </div>
        @if(App\User::isLoggedIn() && App\User::isRoleOf('ADMIN'))
        <div class="d-flex">
            <button onclick="editDegree({{$degree->id}})" type="submit"
                class="btn btn-warning m-3" style="width: 40%;">Edit</button>

            <form action="{{url('/degree', $degree->id)}}" style="width: 40%;" method="post">
                @csrf
                {{ method_field('DELETE') }}
                <button class="btn btn-danger m-3" style="width: 100%;" type="submit" >Delete</button>
            </form>
        </div>
        @endif
    </div>
    @endforeach
    </div>

    <div class="text-center d-flex justify-content-center m-5">
        {{ $degrees->links() }}
        @if(App\User::isRoleOf('ADMIN'))
            <button onclick="newDegree({{$university->id}})" class="btn btn-success m-3" style="width: 35%;">Add degree</button>
        @endif
    </div>

    <script>
        function goToSubjects(id) {
            window.location.href = `{{url('/degree/')}}/${id}`;
        }
        function editDegree(id) {
            window.location.href = `{{url('/degree/edit')}}/${id}`;
        }
        function newDegree(id){
            window.location.href = `{{url('/degree/new')}}/${id}`;
        }
    </script>
</div>
@endsection
