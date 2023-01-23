<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Comment extends Model
{
    /**
     * Returns the comment (user) of the review.
     * 
     * @return User
     */
    public function user(){
        return $this->belongsTo(User::class);
    }

    /**
     * Returns the review of the comment.
     * 
     * @return Review
     */
    public function review(){
        return $this->belongsTo(Review::class);
    }
}
