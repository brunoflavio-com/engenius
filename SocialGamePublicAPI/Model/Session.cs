using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity.Infrastructure;
using System.Data.Entity;

namespace SocialGamePublicAPI.Model
{
    public class SessionContext : DbContext
    {
       public SessionContext()
            : base("DefaultConnection") { }
        public DbSet<Session> Sessions { get; set; }
        public DbSet<WordCategory> Categories { get; set; }
        public DbSet<Maze> mazes { get; set; }
       
    }

    public class Session
    {

        public Session() {
            LastConnectionTime = System.DateTime.Now;
        }

        [Key]
        public string Token { get; set; }
        
        [Required]
        public string JsonUser { get; set; }

        [MaxLength]
        public string JsonGraph {get; set;}

        [Required]
        public DateTime LastConnectionTime { get; set; }
    }
}