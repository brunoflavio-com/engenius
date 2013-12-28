using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameWebsite.Models
{
    public class User
    {
        public string Email { get; set; }
        public string Name { get; set; }
        public string Surname { get; set; }
        public DateTime Birthdate { get; set; }
        public string PhoneNumber { get; set; }
        public string LinkedinProfile { get; set; }
        public string FacebookProfile { get; set; }
        public HumorStatus HumorStatus { get; set; }
    }

    public class HumorStatus
    {
        public int ID { get; set; }
        public string Name { get; set; }
    }
}