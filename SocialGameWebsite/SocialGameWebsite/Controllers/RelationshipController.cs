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
    [Authorize]
    public class RelationshipController : Controller
    {
        SocialGameBLLServiceClient Proxy = new SocialGameBLLServiceClient();

        // GET: /Relationship/Requests
        public ActionResult Requests()
        {
            RequestsViewModel RequestsViewModel = new RequestsViewModel();

            ICollection<RelationshipRequest> NewRequests = Proxy.GetPendingRequestsToUser(new User { Email = User.Identity.Name } );
            ICollection<RelationshipRequest> MyRequests = Proxy.GetUserPendingRequests(new User { Email = User.Identity.Name });

            IList<HumourStatusViewModel> ServiceHumourStatus = HumourStatusViewModel.createList(Proxy.GetAllHumourStatus());

            foreach (RelationshipRequest NewRequest in NewRequests)
            {
                UserViewModel user = new UserViewModel(Proxy.GetUser(NewRequest.RequesterEmail), ServiceHumourStatus);
                RequestsViewModel.UserNewRequests.Add(user);
            }

            foreach (RelationshipRequest MyRequest in MyRequests)
            {
                UserViewModel user = new UserViewModel(Proxy.GetUser(MyRequest.RequestedEmail), ServiceHumourStatus);
                RequestsViewModel.UserMyRequests.Add(user);
            }

            return View(RequestsViewModel);
        }

        
        public ActionResult CommonInterests(ICollection<int> InterestIDs)
        {
            if (InterestIDs == null) return new EmptyResult();

            User MeBLL = Proxy.GetUser(User.Identity.Name);

            ICollection<string> InterestNames = new List<String>();

            ICollection<Interest> Interests = new List<Interest>();
            foreach (int InterestID in InterestIDs)
            {
                Interest Interest = Proxy.GetInterest(InterestID);
                Interests.Add(Interest);
                InterestNames.Add(Interest.Name);
            }

            User[] FriendsWithCommonInterests = Proxy.GetFriendsWithCommonInterests(MeBLL, Interests.ToArray());

            IList<HumourStatusViewModel> ServiceHumourStatus = HumourStatusViewModel.createList(Proxy.GetAllHumourStatus());
            ICollection<UserViewModel> FriendsWithCommonInterestsViewModel = new List<UserViewModel>();
            foreach (User Friend in FriendsWithCommonInterests)
            {
                FriendsWithCommonInterestsViewModel.Add(new UserViewModel(Friend, ServiceHumourStatus));
            }

            ViewBag.InterestNames = InterestNames;
            return View(FriendsWithCommonInterestsViewModel);
        }

        //
        // GET: /Relationship/Router
        // Routes the request to the correct view.
        public ActionResult Router(EditRelationshipViewModel id)
        {
            id.UserA = User.Identity.Name;
            
            //Our own profile:
            if (id.UserA.Equals(id.UserB))
            {
                return new EmptyResult();
            }

            //We're waiting for user to accept request:
            if (Proxy.CheckPendingRequest(new User { Email = id.UserA }, new User { Email = id.UserB }))
            {
                return AssembleOutgoingRequest(id);
            }

            //Pending request to ourselves:
            if (Proxy.CheckPendingRequest(new User { Email = id.UserB }, new User { Email = id.UserA }))
            {
                return AssembleIncomingRequest(id);
            }

            //We're not friends (yet):
            if (!Proxy.CheckRelationship(new User { Email = id.UserA }, new User { Email = id.UserB }))
            {
                return AssembleCreate(id);
            }
            else
            //We're related:
            {
                Relationship Relationship = Proxy.GetRelationship(new User { Email = id.UserA }, new User { Email = id.UserB });
                return AssembleDetails(Relationship);
            }


            return new EmptyResult();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit(RelationshipViewModel RelationshipViewModel)
        {
            EditRelationshipViewModel id =
                    new EditRelationshipViewModel
                    {
                        UserA = RelationshipViewModel.UserA.Email,
                        UserB = RelationshipViewModel.UserB.Email,
                        Strenght = RelationshipViewModel.Strenght,
                        RelationshipTag = RelationshipViewModel.RelationshipTag.ID
                    };
            return AssembleCreate(id);
        }

        // POST: /Relationship/Create
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create(EditRelationshipViewModel EditRelationshipViewModel)
        {
            if (ModelState.IsValid)
            {
                SocialGameBLLService.User UserA = Proxy.GetUser(EditRelationshipViewModel.UserA);
                SocialGameBLLService.User UserB = Proxy.GetUser(EditRelationshipViewModel.UserB);
                int Strength = EditRelationshipViewModel.Strenght;
                int RelationshipTagID = EditRelationshipViewModel.RelationshipTag;

                Proxy.MakeRelationshipRequest(UserA, UserB, RelationshipTagID, Strength);
                
                return RedirectToAction("Router", EditRelationshipViewModel );
            }

            return new EmptyResult();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult EditAction(string UserA, string UserB)
        {
            EditRelationshipViewModel Relationship = new EditRelationshipViewModel();
            Relationship.UserA = Base64.Decode(UserA);
            Relationship.UserB = Base64.Decode(UserB);

            return AssembleCreate(Relationship);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Remove(string UserA, string UserB)
        {
            string UserAEmail = Base64.Decode(UserA);
            string UserBEmail = Base64.Decode(UserB);

            if (UserAEmail == User.Identity.Name || UserBEmail == User.Identity.Name) {
                Proxy.DeleteRelationship(new User { Email = UserAEmail }, new User { Email = UserBEmail });
            }

            return RedirectToAction("Router", new EditRelationshipViewModel { UserA = UserAEmail, UserB = UserBEmail });
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult CancelRequest(string UserA, string UserB)
        {
            string UserAEmail = Base64.Decode(UserA);
            string UserBEmail = Base64.Decode(UserB);

            if (UserAEmail == User.Identity.Name)
            {
                //Use the reject request method of the BLL to cancel the request.
                Proxy.RejectRelationshipRequest(new User { Email = UserBEmail }, new User { Email = UserAEmail });
            }
            return RedirectToAction("Router", new EditRelationshipViewModel { UserA = UserAEmail, UserB = UserBEmail });
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult AcceptRequest(string UserA, string UserB)
        {
            string UserAEmail = Base64.Decode(UserA);
            string UserBEmail = Base64.Decode(UserB);

            if (UserAEmail == User.Identity.Name)
            {
                Proxy.AcceptRelationshipRequest(new User { Email = UserAEmail }, new User { Email = UserBEmail });
            }
            return RedirectToAction("Router", new EditRelationshipViewModel { UserA = UserAEmail, UserB = UserBEmail });
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult RejectRequest(string UserA, string UserB)
        {
            string UserAEmail = Base64.Decode(UserA);
            string UserBEmail = Base64.Decode(UserB);

            if (UserAEmail == User.Identity.Name)
            {
                Proxy.RejectRelationshipRequest(new User { Email = UserAEmail }, new User { Email = UserBEmail });
            }
            return RedirectToAction("Router", new EditRelationshipViewModel { UserA = UserAEmail, UserB = UserBEmail });
        }

        [Authorize]
        public ActionResult Suggestions()
        {
            User MeBLL = Proxy.GetUser(User.Identity.Name);

            User[] PossibleFriends = Proxy.GetPossibleFriends(MeBLL);

            IList<HumourStatusViewModel> ServiceHumourStatus = HumourStatusViewModel.createList(Proxy.GetAllHumourStatus());
            ICollection<UserViewModel> PossibleFriendsViewModel = new List<UserViewModel>();
            foreach (User PossibleFriend in PossibleFriends)
            {
                PossibleFriendsViewModel.Add(new UserViewModel(PossibleFriend, ServiceHumourStatus));
            }

            return PartialView(PossibleFriendsViewModel);
        }
        


        private ActionResult AssembleCreate(EditRelationshipViewModel id)
        {
            //Ensure we will never make friendship requests as another user:
            id.UserA = User.Identity.Name;

            ViewBag.RelationshipTagViewModels = RelationshipTagViewModel.createList(Proxy.GetRelationshipTags());
            return PartialView("Create", id);
        }

        private ActionResult AssembleIncomingRequest(EditRelationshipViewModel id)
        {
            //Ensure we will never make friendship requests as another user:
            id.UserA = User.Identity.Name;

            ViewBag.RelationshipTagViewModels = RelationshipTagViewModel.createList(Proxy.GetRelationshipTags());
            return PartialView("AcceptRequest", id);
        }

        private ActionResult AssembleOutgoingRequest(EditRelationshipViewModel id)
        {
            //Ensure we will never make friendship requests as another user:
            id.UserA = User.Identity.Name;

            ViewBag.RelationshipTagViewModels = RelationshipTagViewModel.createList(Proxy.GetRelationshipTags());
            return PartialView("CancelRequest", id);
        }

        private ActionResult AssembleDetails(Relationship BLLRelationship)
        {
            RelationshipViewModel RelationshipViewModel = new RelationshipViewModel(BLLRelationship);
            return PartialView("Details", RelationshipViewModel);
        }
    }
}

