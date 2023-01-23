<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Review;
use App\Subject;
use App\User;
use DB;

class ReviewController extends Controller
{
    /**
     * Returns all reviews ordered by top votes.
     * */
    function getTopReviews() {
        // TODO Order returned reviews by up votes.

        $reviews = Review::select(DB::raw('reviews.*, count(votes.id) as likes'))
        ->leftJoin('votes', 'votes.review_id', '=', 'reviews.id')
        ->where('votes.likes', '=', '1')
        ->groupBy('votes.review_id')
        ->orderBy('likes', 'desc')
        ->simplePaginate(5);

        return view('review.top')->with("reviews", $reviews);
    }

    /**
     * Returns the latest reviews.
     */
    function getLatestReviews(){
        $reviews = Review::orderBy('created_At', 'DESC')->simplePaginate(5);
        return view('review.top')->with("reviews", $reviews);
    }

    /**
     * Returns the data of a specific review, with the author, comments and votes populates.
     */
    function getReview($id) {
        $review = Review::findOrFail($id);
        return view('review.review')->with("review", $review);
    }

    /**
     * Returns the form to create a new review depeding on the subject selected.
     */
    function newReview($id) {
        $subject = Subject::findOrFail($id);
        return view('review.create')->with("subject", $subject);
    }

    /**
     * Processes the review form and submits a new review.
     */
    function newReviewProcess(Request $req, $id) {
        $subject = Subject::findOrFail($id);
        $req->validate(['review' => 'required|max:200',
                        'satisfaction' => 'required|integer|between:0,10']);

        $review = new Review();
        $review->review = $req->input('review');
        $review->satisfaction = $req->input('satisfaction');
        $review->user()->associate(User::currentUser());
        $review->subject()->associate($subject);
        $review->save();

        return view('review.review')->with("review", $review);
    }

    /**
     * Deletes a review.
     */
    function deleteReview($id) {
        $review = Review::findOrFail($id);
        if (!(User::currentUser()->id == $review->user->id) && !User::currentUser()->isRoleOf('ADMIN'))
            return abort(403, 'Access denied');

        $review->delete();
        return redirect('/');
    }
}
