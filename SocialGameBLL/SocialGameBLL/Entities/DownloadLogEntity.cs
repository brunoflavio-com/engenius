using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Entities
{
    public class DownloadLogEntity
    {
        public int ID { get; set; }
        public string UserEmail { get; set; }
        public string DownloadIp { get; set; }
    }
}