using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Microsoft.AspNet.Identity;
using System.Threading.Tasks;

namespace SocialGameWebSite.Authorization.AuthorizationUsers
{
    public class SocialGameUserManager<IUser> : UserManager<IUser> where IUser : SocialGameWebSite.Authorization.AuthorizationUsers.SocialGameUser
    {

        public SocialGameUserManager(IUserStore<IUser> UserStore) : base(UserStore) { }

        public async override Task<IdentityResult> CreateAsync(IUser user, string password)
        {
            return await Task.Factory.StartNew<IdentityResult>(() =>
            {
                try
                {
                    SocialGameBLLService.ISocialGameBLLService Proxy = new SocialGameBLLService.SocialGameBLLServiceClient();
                    Proxy.RegisterUser(user.UserName, password);
                    return IdentityResult.Success;
                }
                catch (Exception e)
                {
                    return IdentityResult.Failed(new string[] { e.Message });
                }
            });
        }

    }
}