<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Vote extends Model
{
    /**
     * Returns the voter (user) of the review.
     * 
     * @return User
     */
    public function user(){
        return $this->belongsTo(User::class);
    }

    /**
     * Returns the review of the vote.
     * 
     * @return Review
     */
    public function review(){
        return $this->belongsTo(Review::class);
    }

}
