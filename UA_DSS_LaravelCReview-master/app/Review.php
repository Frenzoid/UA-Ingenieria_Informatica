<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Review extends Model
{
     /**
     * Returns the author (user) of the review.
     * 
     * @return User
     */
    public function user(){
        return $this->belongsTo(User::class);
    }

     /**
     * Returns the subject of the review.
     * 
     * @return Subject
     */
    public function subject(){
        return $this->belongsTo(Subject::class); 
    }

    /**
     * Returns all comments for the review.
     * 
     * @return array
     */
    public function comments() {
        return $this->hasMany(Comment::class);
    }


    /**
     * Returns all votes for the review.
     * 
     * @return array
     */
    public function votes() {
        return $this->hasMany(Vote::class);
    }


    /**
     * Returns true if the user has already voted on the review, or false if else.
     * 
     * @param User $user
     * @return boolean
     */
    public function hasBeenVoted($user) {
        return $this->votes()->where('user_id', $user->id)->first()->count() > 0;
    }
}
