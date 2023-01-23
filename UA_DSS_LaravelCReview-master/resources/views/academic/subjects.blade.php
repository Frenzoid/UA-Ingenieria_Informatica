@extends('layout')

@section('title', $degree->university->name . " > " . $degree->name)

@section('content')
<div class="d-flex flex-row flex-wrap justify-content-center">
    @php
        $subjects = $degree->subjects()->simplePaginate(5);
    @endphp
    @foreach ($subjects as $subject)
    <div class="card text-white bg-dark m-1" style="width: 22rem;">
        <div onclick="showSubjectInfo({{$subject->id}})" style="cursor: pointer;" class="card-header text-warning">{{ $subject->name }}</div>
        <div onclick="showSubjectInfo({{$subject->id}})" style="cursor: pointer;" class="card-body"> 
            <p class="card-text">Description: <i class="text-info">{{ $subject->description }}</i></p>
            <p class="card-text">Year of degree: <span class="text-info">{{ $subject->year }} / {{ $degree->years }}</span></p>
            <p class="card-text">Times reviewd: <span class="text-primary">{{ $subject->reviews()->count() }}</span></p>            
            <p class="card-text">General Satisfaction: <span class="text-primary">{{ round($subject->getAvgSatisfaction(), 2) }} / 10</span></p>
        </div>
        @if(App\User::isLoggedIn() && App\User::isRoleOf('ADMIN'))
        <div class="d-flex">
            <button onclick="editSubject({{$subject->id}})" type="submit"
                class="btn btn-warning m-3" style="width: 40%;">Edit</button>
            <form action="{{url('/subject', $subject->id)}}" style="width: 40%;" method="post">
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
        @if(App\User::isRoleOf('ADMIN'))
            <button onclick="newSubject({{$degree->id}})" class="btn btn-success m-3" style="width: 35%;">Add subject</button>
        @endif
        {{ $subjects->links() }}
    </div>

    <script>
    function showSubjectInfo(id) {
        window.location.href = `{{url('/subject/')}}/${id}`;
    }
    function editSubject(id) {
        window.location.href = `{{url('/subject/edit')}}/${id}`;
    }
    function newSubject(id) {
        window.location.href = `{{url('/subject/new')}}/${id}`;
    }
    </script>

</div>
@endsection
