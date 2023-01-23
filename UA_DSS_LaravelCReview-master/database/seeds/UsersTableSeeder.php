<?php

use Illuminate\Database\Seeder;

use App\User;
use Illuminate\Support\Facades\Hash;

class UsersTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $faker = Faker\Factory::create('es_ES');

        for ($i=0; $i<15; $i++) {
            $user = new User();
            $user->name = $faker->unique()->firstName($gender = 'male'|'female');
            $user->email = $faker->unique()->safeEmail;
            $user->password = $faker->regexify('[A-Z0-9_]{5,8}');
            $user->role = $faker->randomElement($array = array ('USER','ADMIN'));
            $user->save();
        }

        $user = new User();
        $user->name = "Artyom";
        $user->email = 'artyom@mail.com';
        $user->password = Hash::make('metro');
        $user->role = 'ADMIN';
        $user->save();

        $user = new User();
        $user->name = "Jagger";
        $user->email = 'brocoli@mail.com';
        $user->password = Hash::make('brocoli');
        $user->role = 'USER';
        $user->save();
    }   
}   
