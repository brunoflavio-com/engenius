using SocialGameBLL.Entities;
using SocialGameBLL.Security;
using SocialGameBLL.Service;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Controllers
{
    public class AuthenticationController
    {
        public User RegisterUser(string Email, string Password)
        {
            SocialGameBLLDbContext db = new SocialGameBLLDbContext();

            try
            {
                UserEntity UserEntity = SecurityService.RegisterUser(Email, Password);

                return new User
                {
                    Email = UserEntity.Email
                };
            }
            catch (Exception e)
            {
                throw new Exception(e.Message);
            }
        }

        public User LoginUser(string Email, string Password)
        {
            User User = new User();

            try
            {
                UserEntity UserEntity = SecurityService.LoginUser(Email, Password);
                User.Email = UserEntity.Email;
            }
            catch (Exception e)
            {
                throw new Exception(e.Message);
            }
            return User;
        }
    }
}