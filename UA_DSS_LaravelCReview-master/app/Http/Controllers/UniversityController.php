<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\University;

class UniversityController extends Controller
{
    /**
     * Returns all universities with degrees pre-populated.
     */
    function getAllUniversities() {
        return view('academic.universities')->with("universities", University::with('degrees')->simplePaginate(5));
    }

    /**
     * Returns the data of one university with degrees pre-populated.
     */
    function getUniversity($id) {
        $university = University::with('degrees')->findOrFail($id);
        return view('academic.degrees')->with("university", $university);
    }

    /**
     * Deletes a university.
     */
    function deleteUniversity($id) {
        $university = University::findOrFail($id);
        $university->delete();
        return redirect('/universities');
    }

    /**
     * Returns the form to add a new university.
     */
    function newUniversity() {
        return view('academic.universityadd');
    }

    /**
     * Processes to form to add a new university.
     */
    function newUniversityProcess(Request $req) {
        $req->validate(['name' => 'required',
                        'city' => 'required',
                        'country' => 'required']);

        $university = new University();
        $university->name = $req->input('name');
        $university->city = $req->input('city');
        $university->country = $req->input('country');
        $university->save();

        return redirect('/universities');
    }

    /**
     * Returns the university edit form.
     */
    function editUniversity($id) {
        $university = University::findOrFail($id);
        return view('academic.universityedit')->with('university', $university);
    }

    /**
     * Processes to form to add a new university.
     */
    function editUniversityProcess(Request $req, $id) {
        $university = University::findOrFail($id);

        $req->validate(['name' => 'required',
                        'city' => 'required',
                        'country' => 'required']);

        $university->name = $req->input('name');
        $university->city = $req->input('city');
        $university->country = $req->input('country');
        $university->save();

        return redirect('/universities');
    }
}
