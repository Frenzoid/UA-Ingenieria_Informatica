<?php

namespace App;

use Illuminate\Contracts\Auth\MustVerifyEmail;
use Illuminate\Foundation\Auth\User as Authenticatable;
use Illuminate\Notifications\Notifiable;
use Session;

class User extends Authenticatable
{
    use Notifiable;
    public static $currentUserObject = NULL;

    /**
     * The attributes that are mass assignable.
     *
     * @var array
     */
    protected $fillable = [
        'name', 'email', 'password',
    ];

    /**
     * The attributes that should be hidden for arrays.
     *
     * @var array
     */
    protected $hidden = [
        'password', 'remember_token',
    ];

    /**
     * The attributes that should be cast to native types.
     *
     * @var array
     */
    protected $casts = [
        'email_verified_at' => 'datetime',
    ];


    /**
     * Returns all reviews made by the user.
     * 
     * @return array
     */
    public function reviews() {
        return $this->hasMany(Review::class);
    }

    /**
     * Returns all comments made by the user.
     * 
     * @return array
     */
    public function comments() {
        return $this->hasMany(Comment::class);
    }

    /**
     * Returns all suggestions made by the user.
     * 
     * @return array
     */
    public function suggestions() {
        return $this->hasMany(Suggestion::class);
    }

    /**
     * Returns all review votes made by the user.
     * 
     * @return array
     */
    public function votes() {
        return $this->hasMany(Vote::class);
    }

    /**
     * Returns all trust activity made by the user.
     * 
     * @return array
     */
    public function trusts() {
        return $this->hasMany(Trusts::class);
    }

    /**
     * Returns all materials posted by the user.
     * 
     * @return array
     */
    public function materials() {
        return $this->hasMany(Material::class);
    }

    // --------------- CUSTOM FUNCTIONS --------------------

    /**
     * Returns false if the user has no reviews of such subject, or true if else.
     * 
     * @param Subject $subject
     * @return boolean
     */
    public function hasReviewed($subject) {
        return !is_null($this->returnReviewOf($subject));
    }

    /**
     * Returns the review of a subject made by said user.
     * @param Subject $subject
     * @return Review
     */
    public function returnReviewOf($subject) {
        return $this->reviews()->where('subject_id', $subject->id)->first();
    }

     /**
     * Returns true if the user has already voted on the review, or false if else.
     * 
     * @param Review $review
     * @return boolean
     */
    public function hasVoted($review) {
        return !is_null($this->returnVoteOf($review));
    }

    /**
     * Returns the vote of a review made by said user.
     * @param Review $review
     * @return Subject
     */
    public function returnVoteOf($review) {
        return $this->votes()->where('review_id', $review->id)->first();
    }

     /**
     * Returns true if the user has already qualified said material, or false if else.
     * 
     * @param Material $material
     * @return boolean
     */
    public function hasQualified($material) {
        return $this->trusts()->where('material_id', $material->id)->first()->count() > 0;

    }
    
    // -------- SESSION AND PERMISSIONS MANAGEMENT ---------
    
    /**
    * Returns an instance of the class User, used as placeholder until logins and auths are done.
    *   
    * @return User
    */
    static public function currentUser(){
        if (User::isLoggedIn()) {
            // There are cases where currentUser is used in multiple instances, to avoid multiple queries per instance we can optiize it like this.
            if (is_null(User::$currentUserObject))
                User::$currentUserObject = User::findOrFail(Session::get('userid'));

            return User::$currentUserObject;
        }

        return false;
    }
    
    /**
     * Checks if the current user logged in is of role $role, returns true if it is, false if not.
     * 
     * @param Role $role
     * @return boolean
     */
    static public function isRoleOf($role) {
        /**
        * Current roles:
        * null: not logged in.
        * USER: logged in, but, user is an administrator.
        * ADMIN: logged in, user is an administrator.
        */
        return User::isLoggedIn() && User::currentUser()->role == strtoupper($role);
    }

    /**
     * Checks if the user is logged in, returns true if the user is logged in, false if else.
     * 
     * @param Role $role
     * @return boolean
     */
    static public function isLoggedIn() {
        if (Session::has('userid')){
            if (User::find(Session::get('userid')))
                return true;
            else {
                // Session is stuck, needs reflushing, this will happen only mid-debugging, due to closing / serving the app.
                Session::flush();
                Session::regenerate();
            }
        }

        return false;
    }

    /**
     * Log-ins the user.
     * 
     * @param Role $role
     * @return boolean
     */
    static public function logIn($user) {
        if (User::isLoggedIn()) return false;

        Session::regenerate();
        Session::put('userid', $user->id);

        return true;
    }

    /**
     * Log-outs the user.
     * 
     * @param Role $role
     * @return boolean
     */
    static public function logOut() {
        if (User::isLoggedIn()) {
            User::$currentUserObject = NULL;
            Session::flush();
            Session::regenerate();
            return true;
        } 

        return false;
    }


}
