<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Review;
use App\Comment;
use App\User;

class CommentController extends Controller
{
    /**
     * Processes the new comment form on the review page, and creates a new comment.
     */
    function newComment(Request $req, $id){
        $review = Review::findOrFail($id);
        $req->validate(['comment' => 'required']);
        
        $comment = new Comment();
        $comment->comment = $req->input('comment');
        $comment->user()->associate(User::currentUser());
        $comment->review()->associate($review);
        $comment->save();

        return redirect()->action(
            'ReviewController@getReview', ['id' => $review->id]
        );
    }

    /**
     * Deletes a comment.
     */
    function deleteComment($id){
        $comment = Comment::findOrFail($id);

        if (!(User::currentUser()->id == $comment->user->id) && !User::currentUser()->isRoleOf('ADMIN'))
            return abort(403, 'Access denied');

        $reviewId = $comment->review->id;
        $comment->delete();

        return redirect()->back();
    }

    /**
     * returns the form to edit a comment.
     */
    function editComment($id){
        $comment = Comment::findOrFail($id);
        if (!(User::currentUser()->id == $comment->user->id) && !User::currentUser()->isRoleOf('ADMIN'))
            return abort(403, 'Access denied');

        return view('comment.edit')->with('comment', $comment);
    }

    /**
     * Processes the edit comment form on the review page.
     */
    function editCommentProcess(Request $req, $id){
        $comment = Comment::findOrFail($id);
        if (!(User::currentUser()->id == $comment->user->id) && !User::currentUser()->isRoleOf('ADMIN'))
            return abort(403, 'Access denied');

        $req->validate(['comment' => 'required']);
        
        $comment->comment = $req->input('comment');
        $comment->save();

        return redirect()->action(
            'ReviewController@getReview', ['id' => $comment->review->id]
        );
    }
}
