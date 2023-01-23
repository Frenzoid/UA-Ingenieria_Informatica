<?php

use Illuminate\Database\Seeder;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     *
     * @return void
     */
    public function run()
    {
        $this->call(UsersTableSeeder::class);
        $this->command->info('User table seeded!');

        $this->call(UniversityTableSeeder::class);
        $this->command->info('University table seeded!');

        $this->call(DegreeTableSeeder::class);
        $this->command->info('Degree table seeded!');

        $this->call(SubjectTableSeeder::class);
        $this->command->info('Subject table seeded!');

        $this->call(SuggestionTableSeeder::class);
        $this->command->info('Suggestions table seeded!');

        $this->call(ReviewsTableSeeder::class);
        $this->command->info('Reviews table seeded!');

        $this->call(CommentTableSeeder::class);
        $this->command->info('Comments table seeded!');

        $this->call(VoteTableSeeder::class);
        $this->command->info('Votes table seeded!');

        

    }
}
