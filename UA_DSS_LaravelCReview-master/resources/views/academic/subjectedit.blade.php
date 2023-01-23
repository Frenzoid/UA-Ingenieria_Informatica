@extends('layout')

@section('title', 'Editing Subject: ' . $subject->name)

@section('content')

<div class="m-3 justify-content-center text-dark">
<form action="{{ url('/subject/edit', $subject->id) }}" method="POST" class="form-group">
        @csrf
        {{ method_field('PUT') }}
        <div class="mb-3">
            <label for="name"> Name </label>
            <input required value="{{$subject->name}}" name="name" type="text" class="form-control" placeholder="Enter name" id="name">
            <label for="description"> Description </label>
            <input required value="{{$subject->description}}" name="description" type="text" class="form-control" placeholder="Enter description" id="description">
            <label for="year"> Year </label>
            <input value="{{$subject->year}}" name="year" type="number" min="1" class="form-control" placeholder="Enter year" id="year">
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-primary">Update Subject</button>
        </div>
    </form>
</div>

@endsection
