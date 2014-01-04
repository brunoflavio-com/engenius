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
            IList<HumourStatusViewModel> ServiceHumourStatus = GetHumourStatus();
            UserViewModel UserViewModel = new UserViewModel(ServiceUser, ServiceHumourStatus);
            return View(UserViewModel);
        }

        [Authorize]
        public ActionResult EditProfile()
        {
            SocialGameBLLService.User ServiceUser = Proxy.GetUser(User.Identity.Name);
            IList<HumourStatusViewModel> ServiceHumourStatus = GetHumourStatus();
            UserViewModel UserViewModel = new UserViewModel(ServiceUser, ServiceHumourStatus);
            return View(UserViewModel);
        }

        [HttpPost]
        [Authorize]
        public ActionResult EditProfile(UserViewModel model)
        {
            if (ModelState.IsValid)
            {
                UserViewModel UserViewModel = UpdateUserViewModel(model);
                User BLLUser = UserViewModel.GetServiceUser();
                Proxy.UpdateUser(BLLUser);
                return RedirectToAction("ViewProfile");
            }
            return View(model);
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

        /*Helper Methods*/

        private UserViewModel UpdateUserViewModel(UserViewModel UpdatedUserViewModel)
        {
            SocialGameBLLService.User ServiceUser = Proxy.GetUser(User.Identity.Name);
            UserViewModel UserViewModel = new UserViewModel(ServiceUser);
            UserViewModel.Email = UpdatedUserViewModel.Email;
            UserViewModel.Name = UpdatedUserViewModel.Name;
            UserViewModel.Surname = UpdatedUserViewModel.Surname;
            UserViewModel.Birthdate = UpdatedUserViewModel.Birthdate;
            UserViewModel.PhoneNumber = UpdatedUserViewModel.PhoneNumber;
            UserViewModel.LinkedinProfile = UpdatedUserViewModel.LinkedinProfile;
            UserViewModel.FacebookProfile = UpdatedUserViewModel.FacebookProfile;
            if (UpdatedUserViewModel.HumourStatus != null) UserViewModel.HumourStatus = UpdatedUserViewModel.HumourStatus;
            return UserViewModel;
        }

        private IList<HumourStatusViewModel> GetHumourStatus()
        {
            IList<HumourStatusViewModel> HumourStatus = new List<HumourStatusViewModel>();
            ICollection<HumourStatus> ServiceHumourStatus = Proxy.GetAllHumourStatus();

            foreach(HumourStatus H in ServiceHumourStatus)
            {
                HumourStatus.Add(new HumourStatusViewModel(H));
            }

            return HumourStatus;
        }
    }
}
