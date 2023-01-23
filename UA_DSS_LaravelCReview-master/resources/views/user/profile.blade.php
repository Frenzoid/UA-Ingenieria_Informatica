@extends('layout')

@section('title', 'Profile of ' . $user->name)

@section('content')
<div class="m-3 justify-content-center">
    <div class="card bg-dark text-white">
        <h5 class="card-header">
            <span class="text-primary">{{ $user->name }}</span>  (<span class="text-info">{{ $user->email }}</span>)
        </h5>
        <ul class="list-group list-group-flush">
            <li class="list-group-item bg-dark">Total reviews: <span class="text-primary">{{ $user->reviews()->count() }}</span></li>
            <li class="list-group-item bg-dark">Total votes: <span class="text-primary">{{ $user->votes()->count() }}</span></li>
            <li class="list-group-item bg-dark">Total suggestions: <span class="text-primary">{{ $user->suggestions()->count() }}</span></li>
            <li class="list-group-item bg-dark">Acc created at: <span class="text-info">{{ $user->created_at }}</span></li>
            <li class="list-group-item bg-dark">Role: <span class="text-info">{{ $user->role }}</span></li>
        </ul>
        @if(App\User::isLoggedIn() && App\User::currentUser()->id == $user->id || App\User::isRoleOf('ADMIN'))
        <div class="d-flex justify-content-end">
            <form action="{{url('/profile', $user->id)}}" class="mr-3" method="post">
                @csrf
                {{ method_field('DELETE') }}
                <button class="btn btn-danger m-3" style="width: 100%;" type="submit">Delete Profile</button>
            </form>
            <button onclick="editProfile({{$user->id}})" type="submit" class="btn btn-primary m-3">Edit profile</button>
            
        </div>
        @endif
    </div>
    <script>
        function editProfile(id) {
            window.location.href = `{{url('/profile/edit/')}}/${id}`;
        }
        function deleteProfile(id) {
            window.location.href = `{{url('/profile/delete/')}}/${id}`;
        }
    </script>
</div>

<!-- Apparently, theres no clean way to paginate inside a hasMany rendered inside the view, the only way to do this without further bs is this: -->
@php
    $reviews = $user->reviews()->simplePaginate(5);
@endphp
@if($reviews->count() > 0 )
<hr>
<h1 class="text-center text-dark">Reviews</h1>
<div class="d-flex flex-row flex-wrap justify-content-center">

    @foreach ($reviews as $review)
    <div class="card text-white bg-dark m-1 col-lg-4">
    <div onclick="showProfile({{$review->user->id}})" style="cursor: pointer;" class="card-header">Author: <span class="text-primary"> {{ $review->user->name }} </span></div>
        <div onclick="goToReview({{$review->id}})" style="cursor: pointer;" class="card-body">
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
            <button class="btn btn-disabled">👍 <span class="text-white">{{ $review->votes()->where('likes', true)->count() }}</span></button>
            <button class="btn btn-disabled">👎 <span class="text-white">{{ $review->votes()->where('likes', false)->count() }}</span></button>
            @endif
        </div>
        @if(App\User::isLoggedIn() && App\User::currentUser()->id == $review->user->id || App\User::isRoleOf('ADMIN'))
        <form action="{{url('/review', $review->id)}}" class="mr-3" method="post">
            @csrf
            {{ method_field('DELETE') }}
            <button class="btn btn-danger m-3" style="width: 100%;" type="submit">Delete</button>
        </form>
        @endif
    </div>
    @endforeach

    </div>
    <div class="text-center d-flex justify-content-center m-5">
        {{ $reviews->links() }}
    </div>
    <div class="container mb-5 mt-4">

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
@endif

<!-- Apparently, theres no clean way to paginate inside a hasMany rendered inside the view, the only way to do this without further bs is this: -->
@php
    $comments = $user->comments()->simplePaginate(5);
@endphp
@if($comments->count() > 0 )
<hr>
<h1 class="text-center text-dark">Comments</h1>
<div class="d-flex flex-row flex-wrap justify-content-center">
    @foreach ($comments as $comment)
    <div class="card text-white bg-dark m-1 col-lg-4">
        <div onclick="goToReview({{$comment->review->id}})" class="card-header" style="cursor: pointer;">Comment on review of {{ $comment->review->user->name }} at {{ $comment->review->subject->name }}</div>
        <div class="card-body">
            <p class="card-text text-justify font-italic text-primary">{{ $comment->comment }}</p>
        </div>
        <div class="card-footer">
            Created at: <span class="text-info"> {{ $comment->created_at }}</span>
        </div>
        @if(App\User::isLoggedIn() && App\User::currentUser()->id == $comment->user->id || App\User::isRoleOf('ADMIN'))
        <div class="d-flex justify-content-center">
            <button onclick="editComment({{$comment->id}})" type="submit"
                class="btn btn-warning m-3" style="width: 37%;">Edit</button>
            <form action="{{url('/comment', $comment->id)}}"  style="width: 40%;" method="post">
                @csrf
                {{ method_field('DELETE') }}
                <button class="btn btn-danger m-3" style="width: 100%;" type="submit">Delete</button>
            </form>
        </div>
        @endif
    </div>
    @endforeach

    </div>
    <div class="text-center d-flex justify-content-center m-5">
        {{ $comments->links() }}
    </div>
    <div class="container mb-5 mt-4">

    <script>
        function goToReview(id) {
            window.location.href = `{{url('/review/')}}/${id}`;
        }
        function editComment(id) {
            window.location.href = `{{url('/comment/edit/')}}/${id}`;
        }
    </script>
</div>
@endif

<!-- Apparently, theres no clean way to paginate inside a hasMany rendered inside the view, the only way to do this without further bs is this: -->
@php
    $suggestions = $user->suggestions()->simplePaginate(5);
@endphp
@if($suggestions->count() > 0 )
<hr>
<h1 class="text-center text-dark">Suggestions</h1>
<div class="d-flex flex-row flex-wrap justify-content-center">
    @foreach ($suggestions as $suggestion)
    <div class="card text-white bg-dark m-1 col-lg-4">
        <div class="card-body">
            <p class="card-text text-justify font-italic text-primary">{{ $suggestion->suggestion }}</p>
        </div>
        <div class="card-footer mb-2">
            Created at: <span class="text-info"> {{ $suggestion->created_at }}</span>
            <br/>
            @if($suggestion->checked == 1)
                Seen by admins: <span class="text-success"> YES </span>
            @else
                Seen by admins: <span class="text-warning"> NO </span>
            @endif
        </div>
        @if(App\User::isLoggedIn() && App\User::isRoleOf('ADMIN'))
        <div class="text-center">
            <form action="{{url('/suggestion', $suggestion->id)}}" class="mr-4" method="post">
                @csrf
                {{ method_field('DELETE') }}
                <button class="btn btn-danger m-3" style="width: 100%;" type="submit">Delete</button>
            </form>
        </div>
        @endif
    </div>
    @endforeach

    </div>
    <div class="text-center d-flex justify-content-center m-5">
        {{ $suggestions->links() }}
    </div>
    <div class="container mb-5 mt-4">
@endif

@endsection
