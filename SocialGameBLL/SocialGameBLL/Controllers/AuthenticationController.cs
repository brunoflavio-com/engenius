using SocialGameBLL.Entities;
using SocialGameBLL.Security;
using SocialGameBLL.Service;
using SocialGameBLL.Util;
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

                return EntityServiceConverter.ConvertUserEntityToUser(UserEntity);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message);
            }
        }

        public User LoginUser(string Email, string Password)
        {
            try
            {
                UserEntity UserEntity = SecurityService.LoginUser(Email, Password);
                return EntityServiceConverter.ConvertUserEntityToUser(UserEntity);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message);
            }
        }
    }
}