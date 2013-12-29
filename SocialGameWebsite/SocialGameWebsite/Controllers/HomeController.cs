using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using SocialGameWebsite.SocialGameBLLService;
using SocialGameWebsite.Models;

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
            SocialGameBLLService.User ServiceUser = Proxy.GetUser(User.Identity.Name);
            UserViewModel UserViewModel = new UserViewModel(ServiceUser);
            ViewBag.Text = "Name: " + UserViewModel.Name;
            return View();
        }

        public ActionResult Header()
        {
            if (User.Identity.IsAuthenticated)
            {
                ViewBag.Email = User.Identity.Name;
                return PartialView();
            }
            return PartialView();
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
