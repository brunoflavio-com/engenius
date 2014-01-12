using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace SocialGameBLL.Service
{
    [DataContract]
    public class UserScore
    {
        [DataMember]
        public string UserEmail { get; set; }
        [DataMember]
        public string UserName { get; set; }
        [DataMember]
        public string UserSurname{ get; set; }
        [DataMember]
        public int UserLevel { get; set; }
        [DataMember]
        public float UserPoints{ get; set; }
    }
}