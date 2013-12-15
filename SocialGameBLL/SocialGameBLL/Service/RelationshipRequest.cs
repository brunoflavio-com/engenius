using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Service
{
    public class RelationshipRequest
    {
        public User Requester { get; set; }
        public User Requested { get; set; }
    }
}