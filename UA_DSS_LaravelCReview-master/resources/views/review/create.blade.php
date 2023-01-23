@extends('layout')

@section('title', 'Reviewing subject ' . $subject->name)

@section('content')

<div class="m-3 justify-content-center text-dark">
    <form action="{{ url('/review/new', $subject->id) }}" method="POST" class="form-group">
        @csrf
        <div>
            <h5 class="text-center">Reviewing {{ $subject->name }} at {{ $subject->degree->university->name }}</h5>
            <textarea class="form-control" name="review" rows="3" autofocus>{{ old('review') }}</textarea>
        </div>
        <hr>
        <div>
            <label for="satisfaction"> How would you grade this subject from 0 to 10? </label>
            <input type="range" id="satisfaction" name="satisfaction" class="col col-lg-12 pl-0 pr-0" value="5" min="0" max="10">
            <div class="d-flex text-center">
                <p style="width: 9.1%;" class="text-left"> 0</p>
                <p style="width: 9.1%;"> 1</p>
                <p style="width: 9.1%;"> 2</p>
                <p style="width: 9.1%;"> 3</p>
                <p style="width: 9.1%;"> 4</p>
                <p style="width: 9.1%;"> 5</p>
                <p style="width: 9.1%;"> 6</p>
                <p style="width: 9.1%;"> 7</p>
                <p style="width: 9.1%;"> 8</p>
                <p style="width: 9.1%;"> 9</p>
                <p style="width: 9.1%;" class="text-right"> 10</p>
            </div>
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-primary">Submit Review</button>
        </div>
    </form>
</div>

@endsection
