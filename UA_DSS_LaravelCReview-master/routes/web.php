<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

// |---------- Nav Routes
Route::get('/', function () {
    return redirect('/about');
});

Route::get('/top-reviews', 'ReviewController@getTopReviews');
Route::get('/latest-reviews', 'ReviewController@getLatestReviews');

Route::get('/about', 'AboutController@getAbout');

Route::get('/login', 'UserController@logIn');
Route::post('/login', 'UserController@logInProcess');
Route::get('/logout', 'UserController@logOut');
Route::get('/users', 'UserController@getUsers');
Route::post('/users/search', 'UserController@searchUsers');

Route::get('/admin', 'UserController@adminPannel')->middleware('admin');


// |--------- Accessors
// |-- University.
Route::get('/universities', 'UniversityController@getAllUniversities');
Route::get('/university/new', 'UniversityController@newUniversity')->middleware('admin');
Route::get('/university/{id}', 'UniversityController@getUniversity');
Route::delete('/university/{id}', 'UniversityController@deleteUniversity')->middleware('admin');
Route::post('/university/new', 'UniversityController@newUniversityProcess')->middleware('admin');
Route::get('/university/edit/{id}', 'UniversityController@editUniversity')->middleware('admin');
Route::put('/university/edit/{id}', 'UniversityController@editUniversityProcess')->middleware('admin');

// |-- Suggestions.
Route::get('/suggestions', 'SuggestionController@getSuggestions')->middleware('admin');
Route::get('/suggestion/new/', 'SuggestionController@newSuggestion');
Route::post('/suggestion/new/', 'SuggestionController@newSuggestionProcess');
Route::delete('/suggestion/{id}', 'SuggestionController@deleteSuggestion')->middleware('admin');
Route::put('/suggestion/{id}', 'SuggestionController@checkSuggestion')->middleware('admin');


// |-- Degree.
Route::delete('/degree/{id}', 'DegreeController@deleteDegree')->middleware('admin');
Route::get('/degree/{id}/', 'DegreeController@getDegree');
Route::get('/degree/new/{id}', 'DegreeController@newDegree')->middleware('admin');
Route::post('/degree/new/{id}', 'DegreeController@newDegreeProcess')->middleware('admin');
Route::get('/degree/edit/{id}', 'DegreeController@editDegree')->middleware('admin');
Route::put('/degree/edit/{id}', 'DegreeController@editDegreeProcess')->middleware('admin');

// |-- Subject.
Route::delete('/subject/{id}', 'SubjectController@deleteSubject')->middleware('admin');
Route::get('/subject/{id}/', 'SubjectController@getSubject');
Route::get('/subject/new/{id}', 'SubjectController@newSubject')->middleware('admin');
Route::post('/subject/new/{id}', 'SubjectController@newSubjectProcess')->middleware('admin');
Route::get('/subject/edit/{id}', 'SubjectController@editSubject')->middleware('admin');
Route::put('/subject/edit/{id}', 'SubjectController@editSubjectProcess')->middleware('admin');

// |-- Review.
Route::get('/review/{id}/', 'ReviewController@getReview');
Route::get('/review/new/{id}', 'ReviewController@newReview');
Route::post('/review/new/{id}', 'ReviewController@newReviewProcess');
Route::delete('/review/{id}', 'ReviewController@deleteReview');


// |-- Vote.
Route::get('/vote/upvote/{id}', 'VoteController@upVote');
Route::get('/vote/downvote/{id}', 'VoteController@downVote');

// |-- Comment.
Route::delete('/comment/{id}', 'CommentController@deleteComment');
Route::post('/comment/new/{id}', 'CommentController@newComment');
Route::get('/comment/edit/{id}', 'CommentController@editComment');
Route::put('/comment/edit/{id}', 'CommentController@editCommentProcess');


// |-- User.
Route::get('/profile/{id}', 'UserController@getProfile');
Route::get('/register', 'UserController@register');
Route::post('/register', 'UserController@registerProcess');
Route::get('/profile/edit/{id}', 'UserController@editProfile');
Route::put('/profile/edit/{id}', 'UserController@editProfileProcess');
Route::delete('/profile/{id}', 'UserController@deleteProfile');

