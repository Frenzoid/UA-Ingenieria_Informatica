<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Review;
use App\User;
use App\Vote;


class VoteController extends Controller
{
    function upVote($id){
        $review = Review::findOrFail($id);
        $vote = Vote::where('review_id', $id)->where('user_id', User::currentUser()->id)->first();

        if (is_null($vote)){
            $vote = new Vote();
            $vote->likes = true;
            $vote->user()->associate(User::currentUser());
            $vote->review()->associate($review);
            $vote->save();
        } else if($vote->likes) {
            $vote->delete();
        } else if(!$vote->likes){
            $vote->likes = true;
            $vote->save();
        }

        return redirect()->back();
    }

    function downVote($id){
        $review = Review::findOrFail($id);
        $vote = Vote::where('review_id', $id)->where('user_id', User::currentUser()->id)->first();

        if (is_null($vote)){
            $vote = new Vote();
            $vote->likes = false;
            $vote->user()->associate(User::currentUser());
            $vote->review()->associate($review);
            $vote->save();
        } else if($vote->likes) {
            $vote->likes = false;
            $vote->save();
        } else if(!$vote->likes){
            $vote->delete();
        }

        return redirect()->back();
    }
}
