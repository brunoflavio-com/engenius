using SocialGameWebsite.SocialGameBLLService;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace SocialGameWebsite.Controllers
{
    public class DownloadController : Controller
    {
        private static string FILE_PATH_KEY = "OpenGLClientExePath";
        //
        // GET: /Download/
        SocialGameBLLServiceClient Proxy = new SocialGameBLLServiceClient();

        public ActionResult Index()
        {
            string UserEmail = null;
            string ClientIp = Request.ServerVariables["REMOTE_ADDR"];

            if (User.Identity.IsAuthenticated)
            {
                UserEmail = User.Identity.Name;
            }

            Proxy.LogDownload(UserEmail, ClientIp);

            string FilePath =  ConfigurationManager.AppSettings[FILE_PATH_KEY];
            return File(FilePath, "application/octet-stream", "SocialGameApplication.exe");
        }

    }
}
