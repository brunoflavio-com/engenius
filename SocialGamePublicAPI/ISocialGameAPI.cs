using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace SocialGamePublicAPI
{

     [ServiceContract(Namespace = "http://wvm008.dei.isep.ipp.pt")]
    public interface ISocialGameService
    {

        [OperationContract]
        string Login(string Email, string Password);

        [OperationContract]
        UserContract GetGraph(string Token, string Email, int graphDepth);

        [OperationContract]
        void Logout(string Token);
    }


    [DataContract]
    public class UserContract
    {
        [DataMember]
        public string Email { get; set; }

        [DataMember]
        public List<ConnectionContract> Connections { get; set; }

        [DataMember]
        public List<UserTagContract> UserTags { get; set; }

        [DataMember]
        public HumorContract Humor { get; set; }


    }

    [DataContract]
    public class ConnectionContract
    {
        [DataMember]
        public int Id { get; set; }

        [DataMember]
        public int Strength { get; set; }

        [DataMember]
        public UserContract User { get; set; }

        [DataMember]
        public ConnectionTagContract ConnectionTag { get; set; }

    }

    [DataContract]
    public class ConnectionTagContract
    {
        [DataMember]
        public int Id { get; set; }

        [DataMember]
        public string ConnectionTagName { get; set; }
    }

    [DataContract]
    public class UserTagContract
    {
        [DataMember]
        public int Id { get; set; }

        [DataMember]
        public string UserTagName { get; set; }
    }

    [DataContract]
    public class HumorContract
    {
        [DataMember]
        public int Id { get; set; }

        [DataMember]
        public string HumorName { get; set; }
    }
}
