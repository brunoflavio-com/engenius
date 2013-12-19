using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace SocialGameWebSite.Authorization
{
    public interface IUser : IPrincipal
    {
        bool IsAuthenticated { get;}
        string UserName { get;}
    }
}
