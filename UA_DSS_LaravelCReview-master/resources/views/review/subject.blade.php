@extends('layout')

@section('title', 'Details of ' . $subject->name)

@section('content')
<div class="m-3 justify-content-center">
    <div class="card bg-dark text-white">
        <div class="card-header text-primary">{{ $subject->degree->university->name }} > {{ $subject->degree->name }}</div>
        <div class="card-body">
            <h5 class="card-title">{{ $subject->name }}</h5>
            <p class="card-text">{{ $subject->description }}</p>
        </div>
        @if(App\User::isLoggedIn())
        <div class="d-flex justify-content-end">
            <!-- TODO redirect->back x2 to avoid backing to an inexistent subject
            
            @if(App\User::isLoggedIn() && App\User::isRoleOf('ADMIN'))
            <form action="{{url('/subject', $subject->id)}}" style="width: 10%;" class="mr-2" method="post">
                @csrf
                {{ method_field('DELETE') }}
                <button class="btn btn-danger m-3" style="width: 100%;" type="submit" >Delete</button>
            </form>
            @endif
            
            -->

            @if(!App\User::currentUser()->hasReviewed($subject))
            <button onclick="reviewSubject({{$subject->id}})" type="submit" class="btn btn-primary m-3">Review</button>
            @else
            <button onclick="goToReview({{App\User::currentUser()->returnReviewOf($subject)->id}})" type="submit" class="btn btn-primary m-3">See my Review</button>
            @endif
        </div>
        @endif
    </div>
</div>
<div class="d-flex flex-row flex-wrap justify-content-center">
    <!-- Apparently, theres no clean way to paginate inside a hasMany rendered inside the view, the only way to do this without further bs is this: -->
    @php
        $reviews = $subject->reviews()->simplePaginate(5);
    @endphp
    @foreach ($reviews as $review)
    <div class="card text-white bg-dark m-1" style="width: 22rem;">
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
        function reviewSubject(id) {
            window.location.href = `{{url('/review/new')}}/${id}`;
        }
        function deleteReview(id) {
            window.location.href = `{{url('/review/delete/')}}/${id}`;
        }
        function showProfile(id) {
            window.location.href = `{{url('/profile/')}}/${id}`;
        }
    </script>
</div>
@endsection