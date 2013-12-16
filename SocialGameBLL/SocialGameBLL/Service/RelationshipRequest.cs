using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Service
{
    public class RelationshipRequest
    {
        public string RequesterEmail { get; set; }
        public string RequestedEmail { get; set; }
        public int RelationshipTagId { get; set; }
        public int Strength { get; set; }
    }
}