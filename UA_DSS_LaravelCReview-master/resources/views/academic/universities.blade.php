@extends('layout')

@section('title', 'Universities')

@section('content')

<div class="d-flex flex-row flex-wrap justify-content-center">
    
    @foreach ($universities as $university)
    <div  class="card text-white bg-dark m-1" style="width: 22rem;">
        <div onclick="goToDegrees({{$university->id}})" style="cursor: pointer;" class="card-header text-warning">{{ $university->name }}</div>
        <div onclick="goToDegrees({{$university->id}})" style="cursor: pointer;" class="card-body">
            <p class="card-text">Country: <span class="text-info">{{ $university->country }}</span></p>
            <p class="card-text">City: <span class="text-info">{{ $university->city }}</span></p>
            <p class="card-text">Number of Degrees: <span class="text-info">{{ $university->degrees()->count() }}</span></p>
            <p>Global Satisfaction: <span class="text-primary">{{ round($university->getAvgSatisfaction(), 2) }} / 10</span></p>
        </div>
        @if(App\User::isLoggedIn() && App\User::isRoleOf('ADMIN'))
        <div class="d-flex">

            <button onclick="editUniversity({{$university->id}})" class="btn btn-warning m-3" style="width: 40%;">Edit</button>
            
            <form action="{{url('/university', $university->id)}}" style="width: 40%;" method="post">
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
        {{ $universities->links() }}
    </div>

    <script>
        function goToDegrees(id) {
            window.location.href = `{{url('/university/')}}/${id}`;
        }
        function editUniversity(id) {
            window.location.href = `{{url('/university/edit')}}/${id}`;
        }
        
    </script>

</div>
@endsection
