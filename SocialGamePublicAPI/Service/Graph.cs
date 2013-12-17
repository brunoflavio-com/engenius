using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGamePublicAPI.Service
{
    public class Graph
    {
        public ICollection<User> Users { get; set; }
        public ICollection<Relationship> Relationships { get; set; }
        public ICollection<Interest> Interests { get; set; }
        public ICollection<RelationshipTag> RelationshipTags { get; set; }
        public ICollection<HumourStatus> HumourStatus { get; set; }
    }
}