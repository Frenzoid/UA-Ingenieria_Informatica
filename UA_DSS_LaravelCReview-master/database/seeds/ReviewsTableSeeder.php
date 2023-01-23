<?php

use Illuminate\Database\Seeder;

use App\Subject;
use App\User;
use App\Review;
use App\University;
use App\Degree;

class ReviewsTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $students = User::where("role","USER")->get();
        $university = University::where("name","Universidad de Alicante")->first();
        $degree= $university->degrees()->where("name","Ingeniería Informática")->first();
        $subjects = $degree->subjects()->get();
        $faker = Faker\Factory::create();

        for ($i=0; $i<sizeof($students); $i++) {
            for($j=0; $j<sizeof($subjects); $j++){
                $review = new Review();
                $review->satisfaction = rand(0, 10);
                if($students[$i]->name == "Jagger"){
                    $review->review = "a";
                }else{
                    $review->review = $faker->realText($maxNbChars = 50, $indexSize = 2);
                }
                $review->user()->associate($students[$i]);
                $review->subject()->associate($subjects[$j]);
                if($faker->boolean($chanceOfGettingTrue = 75))
                    $review->save();
            }
            
        }
    }
}
