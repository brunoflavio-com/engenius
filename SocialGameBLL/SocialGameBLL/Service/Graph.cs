using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Service
{
    public class Graph
    {
        public ICollection<User> Users { get; set; }
        public ICollection<Relationship> Relationships { get; set; }
    }
}