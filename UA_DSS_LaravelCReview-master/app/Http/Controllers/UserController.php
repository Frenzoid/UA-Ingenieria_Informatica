<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\User;
use Illuminate\Support\Facades\Hash;

class UserController extends Controller
{

    /**
     * List all users
     */
     function getUsers(){
        return view('user.users')->with('users', User::simplePaginate(10));
     }

    /**
     * Search users
     */
    function searchUsers(Request $req){
        return view('user.users')->with('users', User::where('name', 'LIKE', "%{$req->input('search')}%")
                                                   ->orWhere('email', 'LIKE', "%{$req->input('search')}%")
                                                   ->simplePaginate(10));
     }

    /**
     * Returns the log in form.
     */
    function logIn(){
        return view('user.login');
    }

    /**
     * Processes the login form.
     */
    function logInProcess(Request $req){
        $req->validate(['email' => 'required',
                        'password' => 'required']);

        $user = User::where('email', $req->input('email'))->first();
        if (empty($user) || !Hash::check($req->input('password'), $user->password))
            return view('user.login')->with('customError', 'Incorrect credentials or user not found!');

        User::logIn($user);
        return redirect()->action(
            'UserController@getProfile', ['id' => $user->id]
        );
    }

    /**
     * Logs out the current user.
     */
    function logOut(){
        User::logOut();
        return redirect('/');
    }

    /**
     * Returns the user register form.
     */
    function register(){
        return view('user.register');
    }

    /**
     * Processes the user register form.
     */
    function registerProcess(Request $req){
            $req->validate(['name' => 'required',
                            'email' => 'required',
                            'password' => 'required',
                            'password2' => 'required']);

            // Check if passwords match.
            if ($req->input('password') != $req->input('password2')) return view('user.register')->with('customError', 'Passwords missmatch!');

            // Check if the email is already in use.
            if (User::where('email', $req->input('email'))->count() > 0) return view('user.register')->with('customError', 'Email already in use!');

            $user = new User();
            $user->email = $req->input('email');
            $user->password = Hash::make($req->input('password'));
            $user->name = $req->input('name');
            $user->save();

            User::logIn($user);

            return redirect()->action(
                'UserController@getProfile', ['id' => $user->id]
            );
    }

    /**
     * Returns a user profile.
     */
    function getProfile($id){
        return view('user.profile')->with('user', User::with('reviews', 'suggestions', 'comments')->findOrFail($id));
    }

    /**
     * Returns the profile edit form.
     */
    function editProfile($id){
        $user = User::findOrFail($id);

        if (!(User::currentUser()->id == $id) && !User::currentUser()->isRoleOf('ADMIN'))
            return abort(403, 'Access denied');

        return view('user.edit')->with('user', $user);
    }

    /**
     * Returns the profile edit form.
     */
    function editProfileProcess(Request $req, $id) {
        $user = User::with('reviews', 'suggestions', 'comments')->findOrFail($id);

        if (!(User::currentUser()->id == $id) && !User::currentUser()->isRoleOf('ADMIN'))
            return abort(403, 'Access denied');

        $req->validate(['name' => 'required']);

        // Check if new passwords match, if password is going to be edited.
        if ($req->filled('newPassword') && $req->input('newPassword') != $req->input('newPassword2')) return view('user.edit')->with('customError', 'New passwords missmatch!')->with('user', $user);

        // Check if the old password is the same if its an user.
        if (User::currentUser()->isRoleOf('USER') && !Hash::check($req->input('oldPassword'), $user->password)) return view('user.edit')->with('customError', 'Old password is not correct!')->with('user', $user);

        $user->name = $req->input('name');
        if ($req->filled('newPassword')) $user->password = Hash::make($req->input('newPassword'));
        $user->save();

        return view('user.profile')->with('user', $user);
    }

    /**
     * Deletes an user given their id.
     */
    function deleteProfile($id) {

        $user = User::findOrFail($id);

        if (!(User::currentUser()->id == $id) && !User::currentUser()->isRoleOf('ADMIN'))
            return abort(403, 'Access denied');

        if (User::currentUser()->id == $id)
             User::logOut();
             
        $user->delete();
        return redirect('/');
    }

    /**
     * Renders the admin pannel.
     */

     function adminPannel(){
         return view("admin.pannel");
     }
}
