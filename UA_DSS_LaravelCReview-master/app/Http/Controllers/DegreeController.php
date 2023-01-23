<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Degree;
use App\University;

class DegreeController extends Controller
{
    /**
     * Return data of specific degree with subjects pre-populated.
     */
    function getDegree($id) {
        $degree = Degree::with('subjects')->findOrFail($id);
        return view('academic.subjects')->with("degree", $degree);
    }

    /**
    * Deletes a degree.
    */
    function deleteDegree($id) {
        $degree = Degree::findOrFail($id);
        $degree->delete();
        
        return redirect()->back();
    }

    /**
     * Creates a degree.
     */
    function newDegree($id){
        $university = University::findOrFail($id);
        return view('academic.degreeadd')->with("university", $university);
    }

    /**
     * Processes the degree creation.
     */
    function newDegreeProcess(Request $req, $id){
        $university = University::findOrFail($id);
        $req->validate(['name' => 'required',
                        'description' => 'required',
                        'years' => 'required']);
        
        $degree = new Degree();
        $degree->name = $req->input('name');
        $degree->description = $req->input('description');
        $degree->years = $req->input('years');
        $degree->university()->associate($university);
        $degree->save();

        return redirect()->action(
            'UniversityController@getUniversity', ['id' => $university->id]
        );
    }

    function editDegree($id){
        $degree = Degree::findOrFail($id);
        return view('academic.degreeedit')->with("degree", $degree); 
    }

    function editDegreeProcess(Request $req, $id){
        $degree = Degree::findOrFail($id);

        $req->validate(['name' => 'required',
                        'description' => 'required',
                        'years' => 'required']);

        $degree->name = $req->input('name');
        $degree->description = $req->input('description');
        $degree->years = $req->input('years');
        $degree->save();

        $university = $degree->university;

        return redirect()->action(
            'UniversityController@getUniversity', ['id' => $university->id]
        );
    }
}
