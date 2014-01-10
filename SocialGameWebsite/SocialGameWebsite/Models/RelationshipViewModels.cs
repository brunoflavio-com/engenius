using SocialGameWebsite.SocialGameBLLService;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace SocialGameWebsite.Models
{
    public class RelationshipViewModel
    {
        public RelationshipViewModel() { }
        internal RelationshipViewModel(Relationship BLLRelationship, IList<RelationshipTag> RelationshipTags = null, IList<HumourStatusViewModel> HumourStatus = null)
        {
            SocialGameBLLServiceClient Proxy = new SocialGameBLLServiceClient();

            User ServiceUserA = Proxy.GetUser(BLLRelationship.UserAEmail);
            User ServiceUserB = Proxy.GetUser(BLLRelationship.UserBEmail);            

            this.UserA = new UserViewModel(ServiceUserA, HumourStatus);
            this.UserB = new UserViewModel(ServiceUserB, HumourStatus);

            this.Strenght = BLLRelationship.Strength;
            this.RelationshipTag = GetRelationshipTagFromService(Proxy, BLLRelationship.RelationshipTagId);
        }

        [Required]
        public UserViewModel UserA { get; set; }

        [Required]
        public UserViewModel UserB { get; set; }

        [Required]
        public int Strenght { get; set; }

        [Required]
        public RelationshipTagViewModel RelationshipTag { get; set; }

        private RelationshipTagViewModel GetRelationshipTagFromService(SocialGameBLLServiceClient Proxy, int Id, IList<RelationshipTagViewModel> RelationshipTags = null)
        {
            
            if (RelationshipTags == null)
            {                
                SocialGameBLLService.RelationshipTag ServiceRT = Proxy.GetRelationshipTag(Id);
                return new RelationshipTagViewModel(ServiceRT);
            }
            else
            {
                RelationshipTagViewModel RTViewModel = RelationshipTags.First(rt => rt.ID == Id);
                if (RTViewModel != null)
                {
                    return RTViewModel;
                }
                else
                {
                    SocialGameBLLService.RelationshipTag ServiceRT = Proxy.GetRelationshipTag(Id);
                    return new RelationshipTagViewModel(ServiceRT);
                }
            }
        }
    }

    public class RelationshipTagViewModel
    {
        public RelationshipTagViewModel() {  }
        internal RelationshipTagViewModel(RelationshipTag BLLRelationshipTag)
        {
            this.ID = BLLRelationshipTag.Id;
            this.Name = BLLRelationshipTag.Name;
        }
        [Required]
        public int ID { get; set; }

        [Required]
        public String Name { get; set; }

        internal static IList<RelationshipTagViewModel> createList(ICollection<RelationshipTag> ServiceRelationshipTags)
        {
            IList<RelationshipTagViewModel> RelationshipTags = new List<RelationshipTagViewModel>();

            foreach (RelationshipTag R in ServiceRelationshipTags)
            {
                RelationshipTags.Add(new RelationshipTagViewModel(R));
            }

            return RelationshipTags;
        }
    }

    public class EditRelationshipViewModel
    {
        [Required]
        public string UserA { get; set; }

        [Required]
        public string UserB { get; set; }

        [Required]
        public int Strenght { get; set; }

        [Required]
        public int RelationshipTag { get; set; }
    }
}

