using SocialGameWebsite.SocialGameBLLService;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace SocialGameWebsite.Models
{
    public class UserViewModel
    {
        public UserViewModel() { }
        internal UserViewModel(User BLLUser, IList<HumourStatusViewModel> HumourStatus=null)
        {
            this.Email = BLLUser.Email;
            this.Name = BLLUser.Name;
            this.Surname = BLLUser.Surname;
            this.Birthdate = BLLUser.Birthdate;
            this.PhoneNumber = BLLUser.PhoneNumber;
            this.FacebookProfile = BLLUser.FacebookProfile;
            this.LinkedinProfile = BLLUser.LinkedInProfile;
            this.HumourStatus = GetHumourStatusFromService(BLLUser.HumourStatusId, HumourStatus);
        }
        [Required]
        [DataType(DataType.EmailAddress)]
        public string Email { get; set; }

        [Required]
        [Display(Name="First Name")]
        public string Name { get; set; }

        [Required]
        [Display(Name="Last Name")]
        public string Surname { get; set; }

        [Required]
        public DateTime Birthdate { get; set; }

        [Display(Name="Phone Number")]
        public string PhoneNumber { get; set; }

        [Display(Name="LinkedIn Profile")]
        public string LinkedinProfile { get; set; }

        [Display(Name="Facebook Profile")]
        public string FacebookProfile { get; set; }

        public HumourStatusViewModel HumourStatus { get; set; }

        internal User GetServiceUser()
        {
            User User = new User
            {
                Email = this.Email,
                Name = this.Name,
                Surname = this.Surname,
                Birthdate = this.Birthdate,
                PhoneNumber = this.PhoneNumber,
                FacebookProfile = this.FacebookProfile,
                LinkedInProfile = this.LinkedinProfile,
                HumourStatusId = this.HumourStatus.ID
            };
            return User;
        }

        private HumourStatusViewModel GetHumourStatusFromService(int Id, IList<HumourStatusViewModel> ServiceHumourStatus)
        {
            //LocalHostSocialGameBLL.SocialGameBLLServiceClient Proxy = new LocalHostSocialGameBLL.SocialGameBLLServiceClient();
            //LocalHostSocialGameBLL.HumourStatus ServiceHumourStatus = Proxy.GetHumourStatus(Id);

            if (ServiceHumourStatus == null)
            {
                SocialGameBLLService.SocialGameBLLServiceClient Proxy = new SocialGameBLLService.SocialGameBLLServiceClient();
                SocialGameBLLService.HumourStatus ServiceHS = Proxy.GetHumourStatus(Id);
                return new HumourStatusViewModel(ServiceHS);
            }
            else
            {
                HumourStatusViewModel HSViewModel = ServiceHumourStatus.First(hs => hs.ID == Id);
                if (HSViewModel != null)
                {
                    return HSViewModel;
                }
                else
                {
                    SocialGameBLLService.SocialGameBLLServiceClient Proxy = new SocialGameBLLService.SocialGameBLLServiceClient();
                    SocialGameBLLService.HumourStatus ServiceHS = Proxy.GetHumourStatus(Id);
                    return new HumourStatusViewModel(ServiceHS);
                }
            }
        }
    }

    public class HumourStatusViewModel
    {
        public int ID { get; set; }
        public string Name { get; set; }

        internal HumourStatusViewModel(HumourStatus ServiceHumourStatus)
        {
            this.ID = ServiceHumourStatus.Id;
            this.Name = ServiceHumourStatus.Name;
        }

        internal static IList<HumourStatusViewModel> createList(ICollection<HumourStatus> ServiceHumourStatus)
        {
            IList<HumourStatusViewModel> HumourStatus = new List<HumourStatusViewModel>();

            foreach (HumourStatus H in ServiceHumourStatus)
            {
                HumourStatus.Add(new HumourStatusViewModel(H));
            }

            return HumourStatus;
        }
    }

}