using SocialGameWebsite.Models;
using SocialGameWebsite.SocialGameBLLService;
using SocialGameWebsite.Util;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace SocialGameWebsite.Controllers
{
    public class NetworkController : Controller
    {
        //
        // GET: /Network/

        public ActionResult Index()
        {
            return View();
        }


        // Get: /Network/MyNetwork
        public ActionResult MyNetwork()
        {
            return View();
        }

    }
}
