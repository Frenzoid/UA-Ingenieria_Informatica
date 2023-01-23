@extends('layout')

@section('title', 'Suggesting something new?')

@section('content')
<div class="m-3 justify-content-center">
    <div class="mt-3 justify-content-center text-dark">
        <form action="{{ url('/suggestion/new') }}" method="POST" class="form-group">
            @csrf
            <div class="mb-3">
                <label for="suggestion"> Suggesting something cool. </label>
                <textarea class="form-control" name="suggestion"  rows="3" id="suggestion" autofocus></textarea>
            </div>
            <div class="text-right">
                <button type="submit" class="btn btn-primary">Submit Suggestion</button>
            </div>
        </form>
    </div>
</div>
@endsection