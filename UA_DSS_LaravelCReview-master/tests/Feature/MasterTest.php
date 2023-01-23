<?php

namespace Tests\Feature;

use Illuminate\Foundation\Testing\RefreshDatabase;
use Illuminate\Foundation\Testing\WithFaker;
use Tests\TestCase;

use App\Comment;
use App\Degree;
use App\Review;
use App\Subject;
use App\Suggestion;
use App\University;
use App\User;
use App\Vote;

class MasterTest extends TestCase
{
    /**
     * A basic feature test example.
     *
     * @return void
     */
    public function testMasterRelations()
    {
        $university = new University();
        $university->name = "UA";
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

        $user = new User();
        $user->name = "ghostman";
        $user->email = "ghostman2@gmail.com";
        $user->password = "adfgrgsrdfg";
        $user->save();

        $review = new Review();
        $review->satisfaction = 0;
        $review->review = "Buena asignatura, me gusta.";
        $review->subject()->associate($subject);
        $review->user()->associate($user);
        $review->save();

        $comment = new Comment();
        $comment->comment = "Buena review.";
        $comment->review()->associate($review);
        $comment->user()->associate($user);
        $comment->save();

        $vote = new Vote();
        $vote->likes = true;
        $vote->user()->associate($user);
        $vote->review()->associate($review);
        $vote->save();

        $suggestion = new Suggestion();
        $suggestion->suggestion = "Ordenar universidades por calificacion.";
        $suggestion->user()->associate($user);
        $suggestion->save();

        //Comprobamos la relacion entre universidad y asignatura.
        $this->assertEquals($university->degrees()->first()->subjects()->first()->name, "DSS");
        //Comprobamos la relacion entre la asignatura y la universidad.
        $this->assertEquals($subject->degree->university->name, "UA");

        //Comprobamos si la review es correcta.
        $this->assertEquals($subject->reviews()->first()->review, "Buena asignatura, me gusta.");
        //Comprobamos si este usuario ha hecho la review.
        $this->assertEquals($subject->hasBeenReviewedBy($user), true);

        //Comprobamos la relacion entre review y subject.
        $this->assertEquals($review->subject->name, 'DSS');
        //Comprobamos la relacion entre review y user.
        $this->assertEquals($review->user->name, 'ghostman');
        
        //Comprobamos relacion bidireccional entre user y suggestion.
        $this->assertEquals($user->suggestions()->first()->suggestion, "Ordenar universidades por calificacion.");
        $this->assertEquals($suggestion->user->name, "ghostman");

        //Comprobamos relacion entre user y comment.
        $this->assertEquals($user->comments()->first()->comment, "Buena review.");
        $this->assertEquals($comment->review->review, "Buena asignatura, me gusta.");
        $this->assertEquals($comment->user->name, "ghostman");

        //Comprobamos relacion entre user, vote y review.
        $this->assertEquals($user->votes()->first()->likes, true);
        $this->assertEquals($review->votes()->first()->likes, true);
        $this->assertEquals($vote->user->name, "ghostman");
        $this->assertEquals($vote->review->review, "Buena asignatura, me gusta.");


        $subject->delete();
        $review->delete();
        $user->delete();
        $degree->delete();
        $university->delete();
        $comment->delete();
        $suggestion->delete();
        $vote->delete();
    }
}
