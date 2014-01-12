using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameWebsite.Models
{
  
    public class TagCloudViewModel
    {
        public string Title { get; set;}
        
        public Dictionary<string, int> Data {get;set;}

        public TagCloudViewModel()
        {
            Data = new Dictionary<string,int>();
        }

    }
}