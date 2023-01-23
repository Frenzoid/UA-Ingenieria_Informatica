@extends('layout')

@section('title', 'Login')

@section('content')
<div class="m-3 justify-content-center text-white">
    <form action="{{ url('/login') }}" method="post">
        @csrf   
        <div class="form-group">
            <label for="email">Email address:</label>
            <input name="email" type="email" value="{{ old('email') }}" class="form-control" placeholder="Enter email" id="email">
        </div>
        <div class="form-group">
            <label for="pwd">Password:</label>
            <input name="password" type="password" value="{{ old('password') }}" class="form-control" placeholder="Enter password" id="pwd">
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-dark">Submit</button>
        </div>
    </form>
</div>
@endsection