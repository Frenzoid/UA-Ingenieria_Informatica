<?php

namespace Tests\Feature;

use Illuminate\Foundation\Testing\RefreshDatabase;
use Illuminate\Foundation\Testing\WithFaker;
use Tests\TestCase;

use App\Vote;
use App\User;
use App\Review;
use App\University;
use App\Degree;
use App\Subject;

class VoteTest extends TestCase
{
    /**
     * A basic feature test example.
     *
     * @return void
     */
    public function testExample()
    {
        $university = new University();
        $university->name = "Universidad de Alicanteee";
        $university->city = "Alicanteee";
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

        $userV = new User();
        $userV->name = "David";
        $userV->email = "davidmgaspe@gmail.com";
        $userV->password = "holaquetal";
        $userV->role = "tester";
        $userV->save();

        $userR = new User();
        $userR->name = "Juan";
        $userR->email = "juanmgaspe@gmail.com";
        $userR->password = "holaquetal2";
        $userR->role = "tester";
        $userR->save();

        $review = new Review();
        $review->satisfaction = 0;
        $review->review = "Buena asignatura, me gusta.";
        $review->user()->associate($userR);
        $review->subject()->associate($subject);
        $review->save();

        $vote = new Vote();
        $vote->likes = true;
        $vote->user()->associate($userV);
        $vote->review()->associate($review);
        $vote->save();

        $this->assertEquals($userV->votes()->first()->likes, true);
        $this->assertEquals($review->votes()->first()->likes, true);
        $this->assertEquals($vote->user->name, "David");
        $this->assertEquals($vote->review->review, "Buena asignatura, me gusta.");

        $userV->delete();
        $userR->delete();
        $review->delete();
        $vote->delete();
        $university->delete();
        $degree->delete();
        $subject->delete();
    }
}
