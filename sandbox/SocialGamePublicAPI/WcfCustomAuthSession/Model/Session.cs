using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity.Infrastructure;
using System.Data.Entity;
using System.Collections.Generic;

namespace WcfCustomAuthSession.Model
{
    public class SessionContext : DbContext
    {
        public DbSet<Session> Sessions { get; set; }
    }

    public class Session
    {

        public Session() {
            LastConnectionTime = System.DateTime.Now;
        }

        [Key]
        public string Token { get; set; }
        
        public string Email { get; set; }

        [Required]
        public DateTime LastConnectionTime { get; set; }
    }
}