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


        [Authorize]
        // Get: /Network/MyNetwork
        public ActionResult MyNetwork()
        {
            return View();
        }


        public ActionResult InterestsGlobalTagCloud()
        {
            TagCloudViewModel ViewModel = new TagCloudViewModel();

            ViewModel.Title = "Global interests cloud:";
            ViewModel.Data = Proxy.GetInterestsTagCloud(null);
            
            return PartialView("TagCloud", ViewModel);
        }

        [Authorize]
        public ActionResult InterestsUserTagCloud()
        {
            TagCloudViewModel ViewModel = new TagCloudViewModel();

            ViewModel.Title = "User interests cloud:";
            ViewModel.Data = Proxy.GetInterestsTagCloud(new User { Email = User.Identity.Name });
    
            return PartialView("TagCloud", ViewModel);
        }

        public ActionResult RelationshipsGlobalTagCloud()
        {
            TagCloudViewModel ViewModel = new TagCloudViewModel();

            ViewModel.Title = "Global relationships cloud:";
            ViewModel.Data = Proxy.GetRelationshipsTagCloud(null);

            return PartialView("TagCloud", ViewModel);
        }
        
        [Authorize]
        public ActionResult RelationshipsUserTagCloud()
        {
            TagCloudViewModel ViewModel = new TagCloudViewModel();

            ViewModel.Title = "User relationships cloud:";
            ViewModel.Data = Proxy.GetRelationshipsTagCloud(new User { Email = User.Identity.Name });
            
            return PartialView("TagCloud", ViewModel);
        }

        public ActionResult NetworkGlobalStatistics()
        {
            StatisticsViewModel ViewModel = new StatisticsViewModel();

            NetworkStatistics NetworkStatistics = Proxy.GetGraphStats(null);
            
            ViewModel.Title = "Global network statistics:";
            ViewModel.UserCount = NetworkStatistics.UserCount;
            ViewModel.RelationshipStrenghtAverage = NetworkStatistics.RelationshipStrenghtAverage;
            
            return PartialView("Statistics", ViewModel);
        }

        public ActionResult NetworkUserStatistics()
        {
            StatisticsViewModel ViewModel = new StatisticsViewModel();

            NetworkStatistics NetworkStatistics = Proxy.GetGraphStats(new User { Email = User.Identity.Name });
            
            ViewModel.Title = "User network statistics:";
            ViewModel.UserCount = NetworkStatistics.UserCount;
            ViewModel.RelationshipStrenghtAverage = NetworkStatistics.RelationshipStrenghtAverage;

            return PartialView("Statistics", ViewModel);
        }
    }
}
