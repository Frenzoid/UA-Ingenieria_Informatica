<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Material extends Model
{
    /**
     * Returns the subject of the material.
     * 
     * @return Subject
     */
    public function subject(){
        return $this->belongsTo(Subject::class); 
    }

     /**
     * Returns the publisher (user) of the material.
     * 
     * @return User
     */
    public function user(){
        return $this->belongsTo(User::class);
    }

    /**
     * Returns all trust activity of the material.
     * 
     * @return array
     */
    public function trusts() {
        return $this->hasMany(Trusts::class);
    }

    /**
     * Returns true if the user has already qualified said material, or false if else.
     * 
     * @param User $user
     * @return boolean
     */
    public function hasQualified($user) {
        return $this->trusts()->where('user_id', $user->id)->first()->count() > 0;
    }
}
