<?php

use Illuminate\Database\Seeder;

use App\User;
use App\Review;
use App\Comment;

class CommentTableSeeder extends Seeder
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
            $comment = new Comment();
            $comment->comment = $faker->realText($maxNbChars = 50, $indexSize = 2);
            $comment->user()->associate($students[rand(0, sizeof($students)-1)]);
            $comment->review()->associate($reviews[rand(0, sizeof($reviews)-1)]);
            $comment->save();
        }
    }
}
