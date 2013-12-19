using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameWebSite.Authorization
{
    public class User : IUser
    {

        public bool IsAuthenticated
        {
            get { throw new NotImplementedException(); }
        }

        public string UserName
        {
            get { throw new NotImplementedException(); }
        }

        public System.Security.Principal.IIdentity Identity
        {
            get { throw new NotImplementedException(); }
        }

        public bool IsInRole(string role)
        {
            throw new NotImplementedException();
        }
    }
}