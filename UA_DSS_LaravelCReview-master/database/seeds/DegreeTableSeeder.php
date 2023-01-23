<?php

use Illuminate\Database\Seeder;

use App\University;
use App\Degree;

class DegreeTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $degree = new Degree();
        $degree->name = "Ingeniería Informática";
        $degree->description = "Aprender a endulzar las soluciones aplicadas sobre problemas del día a día";
        $degree->years = 4;
        $degree->university()->associate(University::where("name","Universidad de Alicante")->first());
        $degree->save();

        $degree = new Degree();
        $degree->name = "Magisterio";
        $degree->description = "Aprender a hacer cuadros con macarrones";
        $degree->years = 4;
        $degree->university()->associate(University::where("name","Universidad de Alicante")->first());
        $degree->save();

        $degree = new Degree();
        $degree->name = "Matemáticas";
        $degree->description = "Aprender a llorar con diversos problemas";
        $degree->years = 4;
        $degree->university()->associate(University::where("name","Universidad de Alicante")->first());
        $degree->save();

        $degree = new Degree();
        $degree->name = "Medicina";
        $degree->description = "Aprender a curar gente en una facultad despegada";
        $degree->years = 4;
        $degree->university()->associate(University::where("name","Universidad Miguel Hernandez")->first());
        $degree->save();
    }
}
