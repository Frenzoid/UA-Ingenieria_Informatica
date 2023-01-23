<?php

use Illuminate\Database\Seeder;

use App\User;
use App\Suggestion;

class SuggestionTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $students = User::where("role", "USER")->get();
        $faker = Faker\Factory::create();

        for ($i = 0; $i < 40; $i++) {
            $suggestion = new Suggestion();
            $suggestion->suggestion = $faker->realText($maxNbChars = 50, $indexSize = 2);
            $suggestion->checked = rand(0,1) == 1;
            $suggestion->user()->associate($students[rand(0, sizeof($students) - 1)]);
            $suggestion->save();
        }
    }
}
