<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class University extends Model
{
    /**
     * Returns all degrees of the university.
     * 
     * @return array
     */
    public function degrees() {
        return $this->hasMany(Degree::class);
    }

    /**
     * Returns the average satisfacion of said university 0 to 5
     * @return integer
     */
    public function getAvgSatisfaction(){
        if ($this->degrees()->count() > 0)
        {
            $avg = 0;
            foreach ($this->degrees()->get() as $degree) {
                $avg += $degree->getAvgSatisfaction();
            }

            return $avg / $this->degrees()->count();
        }
        
        return 0;
    }
}
