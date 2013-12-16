using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity.Infrastructure;
using System.Data.Entity;

namespace SocialGamePublicAPI.Model
{
    [Serializable]
    public class Connection
    {
        public int Id {get;set;}

        public int Strength { get; set; }

        
        public User User { get; set; }

        
        public ConnectionTag ConnectionTag { get; set; }
    }
}