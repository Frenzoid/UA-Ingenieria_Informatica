<?php

use Illuminate\Database\Seeder;

use App\University;

class UniversityTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $university = new University();
        $university->name = "Universidad de Alicante";
        $university->city = "San Vicente del Raspeig";
        $university->country = "Spain";
        $university->save();

        $university = new University();
        $university->name = "Universidad Miguel Hernandez";
        $university->city = "Elche";
        $university->country = "Spain";
        $university->save();

        $university = new University();
        $university->name = "Universidad Politecnica de Valencia";
        $university->city = "Valencia";
        $university->country = "Spain";
        $university->save();

        $university = new University();
        $university->name = "Universidad Complutense de Madrid";
        $university->city = "Madrid";
        $university->country = "Spain";
        $university->save();
    }
}
