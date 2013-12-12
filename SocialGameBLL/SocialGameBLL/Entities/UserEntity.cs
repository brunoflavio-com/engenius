using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Entities
{
    public class UserEntity
    {
        [Key]
        public string Email { get; set; }
        public string Name { get; set; }
        public string Surname { get; set; }
        public Nullable<DateTime> Birthdate { get; set; }
        public string PhoneNumber { get; set; }
        public string LinkedInProfile { get; set; }
        public string FacebookProfile { get; set; }

        public int HumourStatusID { get; set; }
        public virtual HumourStatusEntity HumourStatus { get; set; }

        public virtual ICollection<RelationshipEntity> UserRelationships { get; set; }

        public virtual ICollection<RelationshipEntity> RelationshipsWithUser { get; set; }

        public virtual ICollection<RelationshipRequestEntity> RequestsSent { get; set; }

        public virtual ICollection<RelationshipRequestEntity> RequestsReceived { get; set; }

        public virtual ICollection<InterestEntity> Interests { get; set; }
    }
}