using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Entities
{
    public class RelationshipEntity
    {
        [Column(Order = 0), Key]
        public string UserEmail { get; set; }
        [Column(Order = 1), Key]
        public string FriendEmail { get; set; }

        public int RelationTagID { get; set; }

        public int Strength { get; set; }

        public virtual UserEntity User { get; set; }
        public virtual UserEntity Friend { get; set; }
        public virtual RelationTagEntity RelationTag { get; set; }

        public override bool Equals(object obj)
        {
            if (obj is RelationshipEntity)
            {
                RelationshipEntity Other = (RelationshipEntity)obj;
                return (this.UserEmail == Other.UserEmail && this.FriendEmail == Other.FriendEmail
                        || this.FriendEmail == Other.UserEmail && this.UserEmail == Other.FriendEmail);
            }
            return false;
        }
    }
}