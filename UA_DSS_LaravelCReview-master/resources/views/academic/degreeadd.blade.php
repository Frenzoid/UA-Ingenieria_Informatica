@extends('layout')

@section('title', 'Adding a new Degree')

@section('content')

<div class="m-3 justify-content-center text-dark">
    <form action="{{ url('/degree/new', $university->id) }}" method="POST" class="form-group">
        @csrf
        <div class="mb-3">
            <label for="name"> Name </label>
            <input required  name="name" type="text" value="{{ old('name') }}" class="form-control" placeholder="Enter name" id="name">
            <label for="description"> Description </label>
            <input required name="description" type="text" value="{{ old('description') }}" class="form-control" placeholder="Enter description" id="description">
            <label for="years"> Years </label>
            <input required  name="years" min="1" type="number" value="{{ old('years') }}" class="form-control" placeholder="Enter years" id="years">
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-primary">Add Degree</button>
        </div>
    </form>
</div>

@endsection