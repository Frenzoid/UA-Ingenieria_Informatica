<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Suggestion extends Model
{
    /**
     * Returns the author (user) of the suggestion.
     * 
     * @return User
     */
    public function user(){
        return $this->belongsTo(User::class);
    }
}
