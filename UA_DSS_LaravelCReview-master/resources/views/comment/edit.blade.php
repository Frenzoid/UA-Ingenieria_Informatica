@extends('layout')

@section('title', 'Review')

@section('content')
<div class="m-3 justify-content-center">
    <div class="card bg-dark">
        <div class="card-header text-white"> {{ $comment->review->subject->name }} at {{ $comment->review->subject->degree->university->name }}</div>
        <div class="card-body">
            <p class="card-title text-primary font-italic">{{ $comment->review->review }}</p>
        </div>
        <div class="d-flex card-footer text-inline text-white">
            <div>
                <div class="card-text">Review's Reputation: 
                <span class="text-primary">{{ $comment->review->votes()->where('likes',true)->count() - $comment->review->votes()->where('likes', false)->count() }} </span>
                </div>
                <div>Satisfaction: <span class="text-primary">{{ $comment->review->satisfaction }} / 10</span></div>
                <div>
                Created at: <span class="text-info"> {{ $comment->review->created_at }}</span>
                </div>
            </div>
        </div>
    </div>
    @if(App\User::isLoggedIn())
    <div class="mt-3 justify-content-center text-dark">
        <form action="{{ url('/comment/edit', $comment->id) }}" method="POST" class="form-group">
            @csrf
            {{ method_field('PUT') }}
            <div class="mb-3">
                <label for="comment"> Editing comment. </label>
                <textarea class="form-control" name="comment"  rows="3" id="comment" autofocus>{{ $comment->comment }}</textarea>
            </div>
            <div class="text-right">
                <button type="submit" class="btn btn-primary">Update Comment</button>
            </div>
        </form>
    </div>
    @endif
</div>
@endsection