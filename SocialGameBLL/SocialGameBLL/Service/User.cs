using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace SocialGameBLL.Service
{
    [DataContract]
    public class User
    {
        [DataMember]
        public string Email { get; set; }
        [DataMember]
        public string Name { get; set; }
        [DataMember]
        public string Surname { get; set; }
        [DataMember]
        public DateTime Birthdate { get; set; }
        [DataMember]
        public int HumourStatusId { get; set; }
        [DataMember]
        public ICollection<int> InterestsIDs { get; set; }
        [DataMember]
        public string PhoneNumber { get; set; }
        [DataMember]
        public string LinkedInProfile { get; set; }
        [DataMember]
        public string FacebookProfile { get; set; }
    }
}