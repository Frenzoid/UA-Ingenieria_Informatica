<?php

namespace Tests\Feature;

use Illuminate\Foundation\Testing\RefreshDatabase;
use Illuminate\Foundation\Testing\WithFaker;
use Tests\TestCase;

use App\Comment;
use App\User;
use App\Review;
use App\University;
use App\Degree;
use App\Subject;

class CommentTest extends TestCase
{
    /**
     * A basic feature test example.
     *
     * @return void
     */
    public function testCommentRelations()
    {

        $university = new University();
        $university->name = "Universidad de Alicanteee";
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

        $userC = new User();
        $userC->name = "David";
        $userC->email = "davidmgaspe@gmail.com";
        $userC->password = "holaquetal";
        $userC->role = "tester";
        $userC->save();

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

        $comment = new Comment();
        $comment->comment = "Buena review, no esta mal.";
        $comment->user()->associate($userC);
        $comment->review()->associate($review);
        $comment->save();

        $this->assertEquals($userC->comments()->first()->comment, "Buena review, no esta mal.");
        $this->assertEquals($review->comments()->first()->comment, "Buena review, no esta mal.");
        $this->assertEquals($comment->review->review, "Buena asignatura, me gusta.");
        $this->assertEquals($comment->user->name, "David");

        $userC->delete();
        $userR->delete();
        $review->delete();
        $comment->delete();
        $university->delete();
        $degree->delete();
        $subject->delete();
    }
}
