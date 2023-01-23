@extends('layout')

@section('title', 'Adding a new University')

@section('content')

<div class="m-3 justify-content-center text-dark">
    <form action="{{ url('/university/new') }}" method="POST" class="form-group">
        @csrf
        <div class="mb-3">
            <label for="name"> Name </label>
            <input required  name="name" type="text" value="{{ old('name') }}" class="form-control" placeholder="Enter name" id="email">
            <label for="city"> City </label>
            <input required name="city" type="text" value="{{ old('city') }}" class="form-control" placeholder="Enter city" id="city">
            <label for="country"> Country </label>
            <input required  name="country" type="text" value="{{ old('country') }}" class="form-control" placeholder="Enter country" id="country">
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-primary">Add University</button>
        </div>
    </form>
</div>

@endsection
