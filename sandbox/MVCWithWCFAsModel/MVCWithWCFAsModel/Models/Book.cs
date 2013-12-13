using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MVCWithWCFAsModel.Models
{
    public class Book
    {
        public int ID { get; set; }
        public string Name { get; set; }
        public float Price { get; set; }
    }
}