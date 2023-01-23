@extends('layout')

@section('title', 'Creating new User')

@section('content')
<div class="m-3 justify-content-center text-dark">
    <form action="{{ url('/register') }}" method="post">
        @csrf   
        <div class="form-group">
            <label for="name">Name:</label>
            <input required name="name" type="text" value="{{ old('name') }}" class="form-control" placeholder="Enter name" id="name">
        </div>
        <div class="form-group">
            <label for="email">Email address:</label>
            <input required name="email" type="email"  value="{{ old('email') }}" class="form-control" placeholder="Enter email" id="email">
        </div>
        <div class="form-group">
            <label for="pwd">Password:</label>
            <input required name="password" type="password"  value="{{ old('password') }}" class="form-control" placeholder="Enter password" id="pwd">
        </div>
        <div class="form-group">
            <label for="pwd2">Confirm Password:</label>
            <input required name="password2" type="password"  value="{{ old('password2') }}" class="form-control" placeholder="Enter password" id="pwd2">
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-dark">Submit</button>
        </div>
    </form>
</div>

@endsection