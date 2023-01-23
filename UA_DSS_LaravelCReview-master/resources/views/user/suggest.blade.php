
@extends('layout')

@section('title', 'Suggest an Idea!')

@section('content')

<div class="m-3 justify-content-center text-white">
    <form action="{{ url('/review/create') }}">
        <div class="form-group">
            <h5 for="exampleFormControlTextarea1">Tell us how can we improve our system, any idea is welcome!
            </h5>
            <textarea class="form-control" id="exampleFormControlTextarea1" rows="3"></textarea>
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-dark">Submit</button>
        </div>
    </form>
</div>
@endsection