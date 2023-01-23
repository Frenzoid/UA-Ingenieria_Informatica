<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Degree extends Model
{
     /**
     * Returns the subjects of the Degree.
     * 
     * @return array
     */
    public function subjects(){
        return $this->hasMany(Subject::class); 
    }

     /**
     * Returns the university binded to said Degree.
     * 
     * @return University
     */
    public function university(){
        return $this->belongsTo(University::class); 
    }

    /**
     * Returns the average satisfacion of said degree 0 to 5
     * @return integer
     */
    public function getAvgSatisfaction(){
        if ($this->subjects()->count() > 0)
        {
            $avg = 0;
            foreach ($this->subjects()->get() as $subject) {
                $avg += $subject->getAvgSatisfaction();
            }

            return $avg / $this->subjects()->count();
        }
        
        return 0;
    }
}
