using SocialGameBLL.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Controllers
{
    public class DownloadsController
    {
        SocialGameBLLDbContext db = new SocialGameBLLDbContext();

        public void LogDownload(string UserEmail, string Ip)
        {
            DownloadLogEntity DownloadEntity = new DownloadLogEntity
            {
                UserEmail = UserEmail,
                DownloadIp = Ip
            };

            db.Downloads.Add(DownloadEntity);
            db.SaveChanges();
        }

        public int GetTotalNumberOfDownloads()
        {
            return db.Downloads.ToList().Count;
        }
    }
}