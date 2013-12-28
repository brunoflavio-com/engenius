using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using SocialGameWebsite.SocialGameBLLService;

namespace SocialGameWebsite.Controllers
{
    public class HomeController : Controller
    {
        SocialGameBLLServiceClient Proxy = new SocialGameBLLServiceClient();
        //LocalHostSocialGameBLL.SocialGameBLLServiceClient Proxy = new LocalHostSocialGameBLL.SocialGameBLLServiceClient();
        public ActionResult Index()
        {
            if (User.Identity.IsAuthenticated)
            {
                return RedirectToAction("ViewProfile");
            }
            return View();
        }

        [Authorize]
        public ActionResult ViewProfile()
        {
            return View();
        }

        public ActionResult About()
        {
            ViewBag.Message = "Your app description page.";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }
    }
}
