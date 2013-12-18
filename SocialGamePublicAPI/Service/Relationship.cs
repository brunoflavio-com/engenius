using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGamePublicAPI.Service
{
    public class Relationship
    {
        public string UserAEmail { get; set; }
        public string UserBEmail { get; set; }
        public int RelationshipTagId { get; set; }
        public int Strength { get; set; }
    }
}