<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Suggestion;
use App\User;

class SuggestionController extends Controller
{
    /**
     * returns the form to create a new suggestion
     */
    function newSuggestion(){
        return view('suggestion.create');
    }

    /**
     * Processes the new suggestion form
     */
    function newSuggestionProcess(Request $req){
        $req->validate(['suggestion' => 'required']);

        $suggestion = new Suggestion();
        $suggestion->suggestion = $req->input('suggestion');
        $suggestion->user()->associate(User::currentUser());
        $suggestion->save();

        return redirect()->action(
            'UserController@getProfile', ['id' => User::currentUser()->id]
        );  
    }

    /**
     * Returns all suggestions
     */
    function getSuggestions(){
        return view('suggestion.suggestions')->with('suggestions', Suggestion::orderBy('checked', 'asc')->simplePaginate(3));
    }

    /**
     * Deletes a suggestion
     */
    function deleteSuggestion($id){
        $suggestion = Suggestion::findOrFail($id);        
        $suggestion->delete();

        return redirect()->back();
    }

    /**
     * Checks a suggestion
     */
    function checkSuggestion($id) {
        $suggestion = Suggestion::findOrFail($id);

        if (!User::currentUser()->isRoleOf('ADMIN'))
            return abort(403, 'Access denied');

        $suggestion->checked = true;
        $suggestion->save();
        return redirect()->back();
    }
    
}
