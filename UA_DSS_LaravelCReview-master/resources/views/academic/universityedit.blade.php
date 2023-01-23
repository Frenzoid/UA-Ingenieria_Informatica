@extends('layout')

@section('title', 'Editing University: ' . $university->name)

@section('content')

<div class="m-3 justify-content-center text-dark">
<form action="{{ url('/university/edit', $university->id) }}" method="POST" class="form-group">
        @csrf
        {{ method_field('PUT') }}
        <div class="mb-3">
            <label for="name"> Name </label>
            <input required value="{{$university->name}}" name="name" type="text" class="form-control" placeholder="Enter name" id="email">
            <label for="city"> City </label>
            <input required value="{{$university->city}}" name="city" type="text" class="form-control" placeholder="Enter city" id="city">
            <label for="country"> Country </label>
            <input value="{{$university->country}}" name="country" type="text" class="form-control" placeholder="Enter country" id="country">
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-primary">Update University</button>
        </div>
    </form>
</div>

@endsection
