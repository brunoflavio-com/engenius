using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(SocialGameWebSite.Startup))]
namespace SocialGameWebSite
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
