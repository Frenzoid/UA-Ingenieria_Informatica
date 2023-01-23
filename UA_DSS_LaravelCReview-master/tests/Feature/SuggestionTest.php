<?php

namespace Tests\Feature;

use Illuminate\Foundation\Testing\RefreshDatabase;
use Illuminate\Foundation\Testing\WithFaker;
use Tests\TestCase;

use App\User;
use App\Suggestion;

class SuggestionTest extends TestCase
{
    /**
     * A basic feature test example.
     *
     * @return void
     */
    public function testSuggestionRelations()
    {
        $user = new User();
        $user->name = "David";
        $user->email = "davidmgaspe@gmail.com";
        $user->password = "holaquetal";
        $user->role = "tester";
        $user->save();

        $suggestion = new Suggestion();
        $suggestion->suggestion = "Estaria bien que las universidades pudiesen ordenarse de mejor a peor.";
        $suggestion->user()->associate($user);
        $suggestion->save();

        $this->assertEquals($user->suggestions()->first()->suggestion, "Estaria bien que las universidades pudiesen ordenarse de mejor a peor.");
        $this->assertEquals($suggestion->user->name, "David");

        $user->delete();
        $suggestion->delete();
    }
}
