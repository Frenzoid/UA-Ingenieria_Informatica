<?php

use Illuminate\Database\Seeder;

use App\University;
use App\Degree;
use App\Subject;

class SubjectTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $university = University::where("name","Universidad de Alicante")->first();
        $degree= $university->degrees()->where("name","Ingeniería Informática")->first();
        
        $subject = new Subject();
        $subject->name = "DSS";
        $subject->description = "Diseño de Sistemas Software";
        $subject->year = 3;
        $subject->degree()->associate($degree);
        $subject->save();

        $subject = new Subject();
        $subject->name = "RC";
        $subject->description = "Redes de los Computadores";
        $subject->year = 2;
        $subject->degree()->associate($degree);
        $subject->save();

        $subject = new Subject();
        $subject->name = "FC";
        $subject->description = "Fundamentos de los Computadores";
        $subject->year = 1;
        $subject->degree()->associate($degree);
        $subject->save();
    }
}
