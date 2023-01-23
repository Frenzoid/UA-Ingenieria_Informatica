<?php

namespace Tests\Feature;

use Illuminate\Foundation\Testing\RefreshDatabase;
use Illuminate\Foundation\Testing\WithFaker;
use Tests\TestCase;

use App\Subject;
use App\User;
use App\Review;
use App\University;
use App\Degree;

class UserTest extends TestCase
{
    /**
     * Tests user relations.
     *
     * @return void
     */
    public function testUserRelations() {

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
        $subject->name = 'Administracion de Sistemas Operativos y Redes de Computadores';
        $subject->year = 3;
        $subject->description = "Instalamos cosillas y suspendemos igual porque FreeBSD siempre revienta antes de la correción";
        $subject->degree()->associate($degree);
        $subject->save();

        $user = new User();
        $user->name = "ghostman";
        $user->email = "ghostman1@gmail.com";
        $user->password = "adfgrgsrdfg";
        $user->save();

        $review = new Review();
        $review->satisfaction = 0;
        $review->review = "Instalar servicios goes brrrrrr";
        $review->user()->associate($user);
        $review->subject()->associate($subject);
        $review->save();

        $this->assertEquals($user->reviews()->first()->subject->name, "Administracion de Sistemas Operativos y Redes de Computadores");
        $this->assertEquals($user->hasReviewed($subject), true);


        $subject->delete();
        $review->delete();
        $user->delete();
        $degree->delete();
        $university->delete();
    }
}
