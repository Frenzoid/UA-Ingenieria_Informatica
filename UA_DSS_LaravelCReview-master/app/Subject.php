<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Subject extends Model
{

    /**
     * Returns all reviews of the subject.
     * 
     * @return array
     */
    public function reviews() {
        return $this->hasMany(Review::class);
    }

     /**
     * Returns the Degree of said subject.
     * 
     * @return Degree
     */
    public function degree(){
        return $this->belongsTo(Degree::class); 
    }

    /**
     * Returns all materials associated to this subject.
     * 
     * @return array
     */
    public function materials() {
        return $this->hasMany(Material::class);
    }

    /**
     * Returns false if the subject has no reviews from such user, or true if else.
     * 
     * @return boolean
     */
    public function hasBeenReviewedBy($user) {
        return $this->reviews()->where('user_id', $user->id)->first()->count() > 0;
    }

    /**
     * Returns the average satisfaction of the subject 0 to 5
     * 
     * @return integer
     */
    public function getAvgSatisfaction(){
        if ($this->reviews()->count() > 0)
            return $this->reviews()->sum('satisfaction') / $this->reviews()->count();
        
        return 0;
    }
}
