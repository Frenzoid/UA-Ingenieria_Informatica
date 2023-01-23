@extends('layout')

@section('title', 'Review')

@section('content')
<div class="m-3 justify-content-center">
    <div class="card bg-dark">
        <div onclick="showSubjectInfo({{$review->subject->id}})" style="cursor: pointer;" class="card-header text-warning"> {{ $review->subject->name }} at {{ $review->subject->degree->university->name }}</div>
        <div class="card-body">
            <p class="card-title text-primary font-italic">{{ $review->review }}</p>
        </div>
        <div class="d-flex card-footer text-inline text-white">
            <div>
                <div class="card-text">Review's Reputation: 
                <span class="text-primary">{{ $review->votes()->where('likes',true)->count() - $review->votes()->where('likes', false)->count() }} </span>
                </div>
                <div>Satisfaction: <span class="text-primary">{{ $review->satisfaction }} / 10</span></div>
                <div>
                Created at: <span class="text-info"> {{ $review->created_at }}</span>
                </div>
            </div>
            <div class="ml-auto">
            @if(App\User::isLoggedIn())
                @if(App\User::currentUser()->id == $review->user->id || App\User::isRoleOf('ADMIN'))
                <form action="{{url('/review', $review->id)}}" class="mr-3" method="post">
                    @csrf
                    {{ method_field('DELETE') }}
                    <button class="btn btn-danger m-3" style="width: 100%;" type="submit" >Delete</button>
                </form>                
                @endif
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

        </div>
    </div>
    @if(App\User::isLoggedIn())
    <div class="mt-3 justify-content-center text-dark">
        <form action="{{ url('/comment/new', $review->id) }}" method="POST" class="form-group">
            @csrf
            <div class="mb-3">
                <label for="comment"> Wanna post a comment? </label>
                <textarea class="form-control" name="comment" rows="3" id="comment" autofocus></textarea>
            </div>
            <div class="text-right">
                <button type="submit" class="btn btn-primary">Submit comment</button>
            </div>
        </form>
    </div>
    @endif
</div>
<div class="d-flex flex-row flex-wrap justify-content-center">
    <!-- Apparently, theres no clean way to paginate inside a hasMany rendered inside the view, the only way to do this without further bs is this: -->
    @php
        $comments = $review->comments()->simplePaginate(5);
    @endphp
    @foreach ($comments as $comment)
    <div class="card text-white bg-dark m-1 col-lg-4">
        <div onclick="showProfile({{$review->user->id}})" class="card-header" style="cursor: pointer; width: 22rem;">{{ $comment->user->name }}</div>
        <div class="card-body">
            <p class="card-text text-justify font-italic text-primary">{{ $comment->comment }}</p>
            Created at: <span class="text-info"> {{ $comment->created_at }}</span>
        </div>
        @if(App\User::isLoggedIn() && App\User::currentUser()->id == $comment->user->id || App\User::isRoleOf('ADMIN'))
        <div class="d-flex ">
            <button onclick="editComment({{$comment->id}})" type="submit"
                class="btn btn-warning m-3" style="width: 40%;">Edit</button>
            <form action="{{url('/comment', $comment->id)}}" style="width: 40%;" method="post">
                @csrf
                {{ method_field('DELETE') }}
                <button class="btn btn-danger m-3" style="width: 100%;" type="submit" >Delete</button>
            </form>
        </div>
        @endif
    </div>
    @endforeach

    </div>
    <div class="text-center d-flex justify-content-center m-5">
        {{ $comments->links() }}
    </div>

    <script>
        function downVote(id){
            window.location.href = `{{url('/vote/downvote/')}}/${id}`;
        }
        function upVote(id){
            window.location.href = `{{url('/vote/upvote/')}}/${id}`;
        }
        function showSubjectInfo(id) {
            window.location.href = `{{url('/subject/')}}/${id}`;
        }
        function editComment(id) {
            window.location.href = `{{url('/comment/edit/')}}/${id}`;
        }
        function showProfile(id) {
            window.location.href = `{{url('/profile/')}}/${id}`;
        }
    </script>
</div>
@endsection