@extends('layout')

@section('title', 'Editing profile of: ' . $user->name)

@section('content')
<div class="m-3 justify-content-center text-dark">
    <form action="{{ url('/profile/edit', $user->id) }}" method="post">
        @csrf
        {{ method_field('PUT') }}
        <div class="form-group">
            <label for="name">Name:</label>
            <input required value="{{ $user->name }}" name="name" type="text" class="form-control" placeholder="Enter name" id="name">
        </div>
        @if(App\User::isRoleOf("USER"))
        <div class="form-group">
            <label for="pwd3">Old Password:</label>
            <input required name="oldPassword" type="password" class="form-control" placeholder="Enter previous password" id="pwd3">
        </div>
        @endif
        <div class="form-group">
            <label for="pwd">New password:</label>
            <input  name="newPassword" type="password" class="form-control" placeholder="Enter new password" id="pwd">
        </div>
        <div class="form-group">
            <label for="pwd2">Confirm Password:</label>
            <input name="newPassword2" type="password" class="form-control" placeholder="Confirm password" id="pwd2">
        </div>
        <div class="text-right">
            <button type="submit" class="btn btn-dark">Submit</button>
        </div>
    </form>
</div>
@endsection