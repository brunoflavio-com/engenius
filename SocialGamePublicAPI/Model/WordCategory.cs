using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity.Infrastructure;
using System.Data.Entity;

namespace SocialGamePublicAPI.Model
{
    public class WordCategory
    {
        [Key]
        public int id { get; set; }
        
        [Required]
        public string CategoryName { get; set; }

        public List<Word> words { get; set; }

        public WordCategory()
        {
            words = new List<Word>();
        }
    }
}