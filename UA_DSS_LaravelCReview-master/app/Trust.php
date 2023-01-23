<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Trust extends Model
{
    /**
     * Returns the Material of the trust activity.
     * 
     * @return Material
     */
    public function material(){
        return $this->belongsTo(Material::class); 
    }
    /**
     * Returns the user of the trust activity.
     * 
     * @return User
     */
    public function user(){
        return $this->belongsTo(User::class); 
}
}
