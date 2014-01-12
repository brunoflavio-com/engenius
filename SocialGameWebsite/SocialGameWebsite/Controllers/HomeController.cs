using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using SocialGameWebsite.SocialGameBLLService;
using SocialGameWebsite.Models;
using SocialGameWebsite.Util;

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
        public ActionResult ViewProfile(string id)
        {
            string UserEmail;

            if (id == null) 
            {
               UserEmail = User.Identity.Name;
               ViewBag.myself = true;
            }
            else
            {
                UserEmail = Base64.Decode(id);
                ViewBag.myself = false;
            }

            SocialGameBLLService.User ServiceUser = Proxy.GetUser(UserEmail);
            IList<HumourStatusViewModel> ServiceHumourStatus = HumourStatusViewModel.createList( Proxy.GetAllHumourStatus() );
            UserViewModel UserViewModel = new UserViewModel(ServiceUser, ServiceHumourStatus);

            ICollection<UserViewModel> Friends = new List<UserViewModel>();
            foreach(User FriendServiceUser in Proxy.GetRelatedUsers(ServiceUser) )
            {
                Friends.Add( new UserViewModel(FriendServiceUser, ServiceHumourStatus) );
            }

            ViewBag.FriendsUserViewModel = Friends;
            
            return View(UserViewModel);
        }


        [Authorize]
        public ActionResult Interests(string Email)
        {
            string UserEmail = Base64.Decode(Email);
            bool isMyProfile = (User.Identity.Name == UserEmail);

            User ServiceUser = Proxy.GetUser(UserEmail);

            ICollection<Interest> UserInterests = Proxy.GetUserInterests(ServiceUser);
            ICollection<string> InterestNames = UserInterests.Select(i => i.Name).ToList();

            ViewBag.Interests = InterestNames;

            return PartialView(isMyProfile);
        }

        [HttpPost]
        [Authorize]
        [ValidateAntiForgeryToken]
        public ActionResult Interests(string id, string name)
        {
            User ServiceUser = Proxy.GetUser(User.Identity.Name);
            Interest Interest = Proxy.AddInterestToUser(ServiceUser, new Interest { Name = name }, id);
            var JsonResult = new { name = Interest.Name };
            return Json(JsonResult);
        }

        [HttpPost]
        [Authorize]
        [ValidateAntiForgeryToken]
        public ActionResult RemoveInterest(int id)
        {
            User ServiceUser = Proxy.GetUser(User.Identity.Name);
            Proxy.RemoveInterestFromUser(ServiceUser, new Interest { Id = id });
            return new EmptyResult();
        }

        [Authorize]
        public ActionResult EditProfile()
        {
            SocialGameBLLService.User ServiceUser = Proxy.GetUser(User.Identity.Name);
            IList<HumourStatusViewModel> ServiceHumourStatus = HumourStatusViewModel.createList(Proxy.GetAllHumourStatus());
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

        //
        // GET: /Home/HumourPartial

        [Authorize]
        public ActionResult HumourPartial()
        {
            SocialGameBLLService.User ServiceUser = Proxy.GetUser(User.Identity.Name);

            IList<HumourStatusViewModel> ServiceHumourStatus = HumourStatusViewModel.createList(Proxy.GetAllHumourStatus());
            UserViewModel UserViewModel = new UserViewModel(ServiceUser, ServiceHumourStatus);

            ViewBag.HumourStatusList = ServiceHumourStatus;
            ViewBag.CurrentHumourStatusID = UserViewModel.HumourStatus.ID;

            return PartialView();
        }

        //
        // GET: /Home/HumourPartial
        [HttpPost]
        [Authorize]
        public ActionResult HumourPartial(int mood)
        {
            SocialGameBLLService.User ServiceUser = Proxy.GetUser(User.Identity.Name);

            IList<HumourStatusViewModel> ServiceHumourStatus = HumourStatusViewModel.createList(Proxy.GetAllHumourStatus());
            UserViewModel UserViewModel = new UserViewModel(ServiceUser, ServiceHumourStatus);

            UserViewModel.HumourStatus = ServiceHumourStatus.Single(h => h.ID == mood);

            Proxy.UpdateUser(UserViewModel.GetServiceUser());

            ViewBag.HumourStatusList = ServiceHumourStatus;
            ViewBag.CurrentHumourStatusID = UserViewModel.HumourStatus.ID;
            return PartialView();
        }
    }
}
