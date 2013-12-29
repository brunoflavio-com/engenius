using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameWebsite.Models
{
    public class User
    {
        //public User(LocalHostSocialGameBLL.User BLLUser)
        public User(SocialGameBLLService.User BLLUser)
        {
            this.Email = BLLUser.Email;
            this.Name = BLLUser.Name;
            this.Surname = BLLUser.Surname;
            this.Birthdate = BLLUser.Birthdate;
            this.PhoneNumber = BLLUser.PhoneNumber;
            this.FacebookProfile = BLLUser.FacebookProfile;
            this.LinkedinProfile = BLLUser.LinkedInProfile;
            this.HumourStatus = GetHumourStatusFromService(BLLUser.HumourStatusId);
        }

        public string Email { get; set; }
        public string Name { get; set; }
        public string Surname { get; set; }
        public DateTime Birthdate { get; set; }
        public string PhoneNumber { get; set; }
        public string LinkedinProfile { get; set; }
        public string FacebookProfile { get; set; }
        public HumourStatus HumourStatus { get; set; }

        private HumourStatus GetHumourStatusFromService(int Id)
        {
            //LocalHostSocialGameBLL.SocialGameBLLServiceClient Proxy = new LocalHostSocialGameBLL.SocialGameBLLServiceClient();
            //LocalHostSocialGameBLL.HumourStatus ServiceHumourStatus = Proxy.GetHumourStatus(Id);
            SocialGameBLLService.SocialGameBLLServiceClient Proxy = new LocalHostSocialGameBLL.SocialGameBLLServiceClient();
            SocialGameBLLService.HumourStatus ServiceHumourStatus = Proxy.GetHumourStatus(Id);
            return new HumourStatus
            {
                ID = ServiceHumourStatus.Id,
                Name = ServiceHumourStatus.Name
            };
        }
    }

    public class HumourStatus
    {
        public int ID { get; set; }
        public string Name { get; set; }
    }
}