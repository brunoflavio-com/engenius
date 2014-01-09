﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity.Infrastructure;
using System.Data.Entity;

namespace SocialGamePublicAPI.Model
{
    public class Word
    {
        [Key]
        public int id { get; set; }
        
        [Required]
        public string word { get; set; }
    }
}