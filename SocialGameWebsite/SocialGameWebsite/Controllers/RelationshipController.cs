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

            if (true/*Proxy.isRelatedToUser(new User { Email = id.UserA }, new User { Email = id.UserB })*/) //We're not friends (yet):
            {
                return AssembleCreate(id);
            }
            else //We're related:
            {
                //Relationship Relationship = Proxy.GetRelationship(new User { Email = id.UserA }, new User { Email = id.UserB });
                //return AssembleDetails(Relationship);
            }

            return new EmptyResult();
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
                
                return RedirectToAction("Route");
            }

            return new EmptyResult();
        }

        private ActionResult AssembleCreate(EditRelationshipViewModel id)
        {
            //Ensure we will never make friendship requests as another user:
            id.UserA = User.Identity.Name;

            ViewBag.RelationshipTagViewModels = RelationshipTagViewModel.createList(Proxy.GetRelationshipTags());
            return PartialView("Create", id);
        }

        private ActionResult AssembleDetails(Relationship BLLRelationship)
        {
            RelationshipViewModel RelationshipViewModel = new RelationshipViewModel(BLLRelationship);
            return PartialView("Details", RelationshipViewModel);
        }
    }
}

