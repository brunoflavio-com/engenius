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

        SocialGameBLLServiceClient Proxy = new SocialGameBLLServiceClient();


        //
        // GET: /Network/

        public ActionResult Index()
        {
            return RedirectToAction("GlobalNetwork");
        }

        public ActionResult GlobalNetwork()
        {
            return View();
        }


        // Get: /Network/MyNetwork
        public ActionResult MyNetwork()
        {
            return View();
        }


        public ActionResult InterestsTagCloud(bool global = false)
        {
            TagCloudViewModel ViewModel = new TagCloudViewModel();

            if (global)
            {
                ViewModel.Title = "Global interests cloud:";
                ViewModel.Data = Proxy.GetInterestsTagCloud(null);
            }
            else
            {
                ViewModel.Title = "User interests cloud:";
                ViewModel.Data = Proxy.GetInterestsTagCloud(new User { Email = User.Identity.Name });
            }
            

            return PartialView("TagCloud", ViewModel);
        }

        public ActionResult RelationshipsTagCloud(bool global = false)
        {
            TagCloudViewModel ViewModel = new TagCloudViewModel();

            if (global)
            {
                ViewModel.Title = "Global relationships cloud:";
                ViewModel.Data = Proxy.GetRelationshipsTagCloud(null);
            }
            else
            {
                ViewModel.Title = "User relationships cloud:";
                ViewModel.Data = Proxy.GetRelationshipsTagCloud(new User { Email = User.Identity.Name });
            }


            return PartialView("TagCloud", ViewModel);
        }
    }
}
