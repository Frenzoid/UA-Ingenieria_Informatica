<?php

namespace App\Http\Middleware;

use Closure;
use App\User;

class AdminPermissions
{
    /**
     * Handle an incoming request.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \Closure  $next
     * @return mixed
     */
    public function handle($request, Closure $next)
    {

        if(User::isRoleOf('admin')){

            return $next($request);

        } else {

            return abort(403, 'This content is only accesible by our admins, please go back.');

        }

    }
}
