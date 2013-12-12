using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Entities
{
    public class UserSecurity
    {
        [Key]
        public string UserEmail { get; set; }

        public byte[] Password { get; set; }

        public byte[] Salt { get; set; }

        public virtual UserEntity User { get; set; }
    }
}