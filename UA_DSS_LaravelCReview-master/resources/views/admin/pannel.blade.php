@extends('layout')

@section('title', 'Administration Pannel')

@section('content')

@if(App\User::isLoggedIn() && App\User::isRoleOf('ADMIN'))
<div class="d-flex flex-row flex-wrap justify-content-center">
    <button onclick="newUniversity()" style="width: 45%;" type="submit" class="btn btn-dark m-3 text-center text-warning font-weight-bold" >Add new University</button>
    <button onclick="showSuggestions()" style="width: 45%;" type="submit" class="btn btn-dark m-3 text-center text-warning font-weight-bold" >Show Suggestions</button>
</div>

<script>
    function newUniversity() {
        window.location.href = `{{url('/university/new')}}`;
    }
    function showSuggestions() {
        window.location.href = `{{url('/suggestions/')}}`;
    }
</script>
@endif
@endsection