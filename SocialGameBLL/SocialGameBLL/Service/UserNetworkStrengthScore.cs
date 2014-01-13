using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace SocialGameBLL.Service
{
    [DataContract]
    public class UserNetworkStrengthScore
    {
        [DataMember]
        public int Position { get; set; }
        [DataMember]
        public string UserEmail { get; set; }
        [DataMember]
        public double UserNetworkStrength { get; set; }
        [DataMember]
        public string UserName { get; set; }
        [DataMember]
        public string UserSurname { get; set; }
    }
}