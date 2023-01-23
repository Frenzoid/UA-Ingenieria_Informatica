<?php

namespace Tests\Feature;

use Illuminate\Foundation\Testing\RefreshDatabase;
use Illuminate\Foundation\Testing\WithFaker;
use Tests\TestCase;

use App\Subject;
use App\Degree;
use App\University;


class UniversityTest extends TestCase
{
        
    /**
     * 
     * Testing the relation between University, Degree and Subject. 
     * 
     * Creates two objects of those mentioned classes and link both, after that tests with an assert if it was done correctly
     *
     * 
     * @test
     */
    public function testUniversityRelations()
    {
        $university = new University();
        $university->name = "Universidad de Alicanteeee";
        $university->city = "Alicante";
        $university->country = "Spain";
        $university->save();

        $degree = new Degree();
        $degree->name = "Ingenieria Informatica";
        $degree->description = "En fin, la UA";
        $degree->years = 4;
        $degree->university()->associate($university);
        $degree->save();

        $subject = new Subject();
        $subject->name = "DSS";
        $subject->description = "Diseño de sistemas software";
        $subject->year = 3;
        $subject->degree()->associate($degree);
        $subject->save();

        $this->assertEquals($university->degrees()->first()->subjects()->first()->name, "DSS");
        $this->assertEquals($subject->degree->university->name, "Universidad de Alicanteeee");

        $university->delete();
        $degree->delete();
        $subject->delete();

    }
}
