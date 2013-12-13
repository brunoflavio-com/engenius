using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Entities
{
    public class SimpleModeScoreEntity
    {
        [Required]
        [Key]
        [ForeignKey("User")]
        public string UserEmail { get; set; }
        public virtual UserEntity User { get; set; }
        public float? Points { get; set; }
        public int? Level { get; set; }
    }
}