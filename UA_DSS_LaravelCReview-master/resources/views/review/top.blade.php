@extends('layout')

@section('title', 'Reviews')

@section('content')
<div class="d-flex flex-row flex-wrap justify-content-center">

    @foreach ($reviews as $review)
    <div class="card text-white bg-dark m-1" style="width: 22rem;">
        <div onclick="showProfile({{$review->user->id}})" class="card-header" style="cursor: pointer;">Author: <span class="text-primary"> {{ $review->user->name }} </span></div>
        <div onclick="goToReview({{$review->id}})" class="card-body" style="cursor: pointer;">
            <h5 class="card-text">Review:</h5>
            @if ($review->satisfaction > 4)
            <p class="card-text text-justify font-italic text-success">{{ $review->review }}</p>
            @else
            <p class="card-text text-justify font-italic text-danger">{{ $review->review }}</p>
            @endif
        </div>
        <div class="card-footer">
            Satisfaction: <span class="card-text text-primary mr-4">{{ $review->satisfaction }} / 10</span>
            @if(App\User::isLoggedIn())
                @if(App\User::currentUser()->hasVoted($review))
                    @if(App\User::currentUser()->returnVoteOf($review)->likes == true)
                    <button onclick="upVote({{$review->id}})" class="btn btn-success">👍 <span class="text-white">{{ $review->votes()->where('likes', true)->count() }}</span></button>
                    <button onclick="downVote({{$review->id}})" class="btn btn-primary">👎 <span class="text-white">{{ $review->votes()->where('likes', false)->count() }}</span></button>
                    @else
                    <button onclick="upVote({{$review->id}})" class="btn btn-primary">👍 <span class="text-white">{{ $review->votes()->where('likes', true)->count() }}</span></button>
                    <button onclick="downVote({{$review->id}})" class="btn btn-danger">👎 <span class="text-white">{{ $review->votes()->where('likes', false)->count() }}</span></button>
                    @endif
                @else
                <button onclick="upVote({{$review->id}})" class="btn btn-primary">👍 <span class="text-white">{{ $review->votes()->where('likes', true)->count() }}</span></button>
                <button onclick="downVote({{$review->id}})" class="btn btn-primary">👎 <span class="text-white">{{ $review->votes()->where('likes', false)->count() }}</span></button>
                @endif
            @else
            <button class="btn btn-disabled" style="cursor: initial;">👍 <span class="text-white">{{ $review->votes()->where('likes', true)->count() }}</span></button>
            <button class="btn btn-disabled" style="cursor: initial;">👎 <span class="text-white">{{ $review->votes()->where('likes', false)->count() }}</span></button>
            @endif
        </div>
        @if(App\User::isLoggedIn() && App\User::currentUser()->id == $review->user->id || App\User::isRoleOf('ADMIN'))
        <form action="{{url('/review', $review->id)}}" style="width: 90%;" method="post">
            @csrf
            {{ method_field('DELETE') }}
            <button class="btn btn-danger m-3" style="width: 100%;" type="submit" >Delete</button>
        </form>
        @endif
    </div>
    @endforeach
    
    </div>
    <div class="text-center d-flex justify-content-center m-5">
        {{ $reviews->links() }}
    </div>

    <script>
    function downVote(id){
        window.location.href = `{{url('/vote/downvote/')}}/${id}`;
    }
    function upVote(id){
        window.location.href = `{{url('/vote/upvote/')}}/${id}`;
    }
    function goToReview(id) {
        window.location.href = `{{url('/review/')}}/${id}`;
    }
    function showProfile(id) {
        window.location.href = `{{url('/profile/')}}/${id}`;
    }
    </script>
</div>
@endsection
