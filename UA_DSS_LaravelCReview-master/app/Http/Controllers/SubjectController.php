<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Subject;
use App\Degree;

class SubjectController extends Controller
{
    /**
     * Return the data of a subject with its reviews and author (user) populated.
     */
    function getSubject($id) {
        $subject = Subject::with('reviews.user')->findOrFail($id);
        return view('review.subject')->with("subject", $subject);
    }

    /**
    * Deletes a subject.
    */
    function deleteSubject($id) {
        $subject = Subject::findOrFail($id);
        $degreeId = $subject->degree->id;
        $subject->delete();

        return redirect()->back();
    }

    /**
     * Creates a subject.
     */
    function newSubject($id){
        $degree = Degree::findOrFail($id);
        return view('academic.subjectadd')->with("degree", $degree);
    }

    /**
     * Processes the subject creation.
     */
    function newSubjectProcess(Request $req, $id){
        $degree = Degree::findOrFail($id);
        $req->validate(['name' => 'required',
                        'description' => 'required',
                        'year' => 'required|integer|between:1,' . $degree->years]);
        
        $subject = new Subject();
        $subject->name = $req->input('name');
        $subject->description = $req->input('description');
        $subject->year = $req->input('year');
        $subject->degree()->associate($degree);
        $subject->save();

        return redirect()->action(
            'DegreeController@getDegree', ['id' => $degree->id]
        );
    }

    function editSubject($id){
        $subject = Subject::findOrFail($id);
        return view('academic.subjectedit')->with("subject", $subject);
    }

    function editSubjectProcess(Request $req, $id){
        $subject = Subject::findOrFail($id);
        $req->validate(['name' => 'required',
                        'description' => 'required',
                        'year' => 'required']);
        
        $subject->name = $req->input('name');
        $subject->description = $req->input('description');
        $subject->year = $req->input('year');
        $subject->save();

        $degree = $subject->degree;

        return redirect()->action(
            'DegreeController@getDegree', ['id' => $degree->id]
        );
    }
}
