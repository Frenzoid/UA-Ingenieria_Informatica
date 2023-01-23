<?php

use Illuminate\Database\Seeder;
use App\Vote;
use App\User;
use App\Review;

class VoteTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $students = User::where("role", "USER")->get();
        $reviews = Review::get();
        $faker = Faker\Factory::create();

        for ($i = 0; $i < 60; $i++) {
            $vote = new Vote();
            $vote->likes = $faker->boolean($chanceOfGettingTrue = 75);
            $vote->user()->associate($students[rand(0, sizeof($students)-1)]);
            $vote->review()->associate($reviews[rand(0, sizeof($reviews)-1)]);
            $vote->save();
        }
    }
}
