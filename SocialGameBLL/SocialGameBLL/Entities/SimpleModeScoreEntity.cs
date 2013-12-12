using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Entities
{
    public class SimpleModeScoreEntity
    {
        [Key]
        public int UserID { get; set; }
        public virtual UserEntity User { get; set; }
        public float? Points { get; set; }
        public int? Level { get; set; }
    }
}