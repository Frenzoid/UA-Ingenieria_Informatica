@extends('layout')

@section('title', 'Adding a new Subject')

@section('content')

<div class="m-3 justify-content-center text-dark">
    <form action="{{ url('/subject/new', $degree->id) }}" method="POST" class="form-group">
        @csrf
        <div class="mb-3">
            <label for="name"> Name </label>
            <input required  name="name" type="text" value="{{ old('name') }}" class="form-control" placeholder="Enter name" id="name">
            <label for="description"> Description </label>
            <input required name="description" type="text" value="{{ old('description') }}" class="form-control" placeholder="Enter description" id="description">
            <label for="year"> Year </label>
            <input required  name="year" min="1" type="number" value="{{ old('year') }}" class="form-control" placeholder="Enter year" id="year">
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-primary">Add Subject</button>
        </div>
    </form>
</div>

@endsection