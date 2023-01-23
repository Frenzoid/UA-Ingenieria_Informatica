@extends('layout')

@section('title', 'Editing Degree: ' . $degree->name)

@section('content')

<div class="m-3 justify-content-center text-dark">
<form action="{{ url('/degree/edit', $degree->id) }}" method="POST" class="form-group">
        @csrf
        {{ method_field('PUT') }}
        <div class="mb-3">
            <label for="name"> Name </label>
            <input required value="{{$degree->name}}" name="name" type="text" class="form-control" placeholder="Enter name" id="name">
            <label for="description"> Description </label>
            <input required value="{{$degree->description}}" name="description" type="text" class="form-control" placeholder="Enter description" id="description">
            <label for="years"> Years </label>
            <input value="{{$degree->years}}" name="years" type="number" min="1" class="form-control" placeholder="Enter years" id="years">
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-primary">Update Degree</button>
        </div>
    </form>
</div>

@endsection
