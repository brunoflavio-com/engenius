using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using SocialGameWebsite.SocialGameBLLService;
using WebMatrix.WebData;

namespace SocialGameWebsite.Authorization
{
    public class SocialGameWebSecurity
    {
        public static void Register(string Username, string Password, string Name, string Surname, DateTime Birthdate)
        {
            SocialGameBLLServiceClient Proxy = new SocialGameBLLServiceClient();
            User User = Proxy.RegisterUser(Username, Password);
            User.Name = Name;
            User.Surname = Surname;
            User.Birthdate = Birthdate;
            User = Proxy.UpdateUser(User);
            WebSecurity.CreateUserAndAccount(User.Email, Password);
            WebSecurity.Login(User.Email, Password);
        }

        public static bool Login(string Username, string Password, bool PersistCookie = false)
        {
            SocialGameBLLServiceClient Proxy = new SocialGameBLLServiceClient();
            try
            {
                User User = Proxy.LoginUser(Username, Password);
                if (!WebSecurity.Login(User.Email, Password, persistCookie: PersistCookie))
                {
                    WebSecurity.CreateUserAndAccount(User.Email, Password);
                    if (!WebSecurity.Login(User.Email, Password, persistCookie: PersistCookie))
                    {
                        return false;
                    }
                }
                return true;
            }
            catch (Exception e)
            {
                return false;
            }
        }
    }
}