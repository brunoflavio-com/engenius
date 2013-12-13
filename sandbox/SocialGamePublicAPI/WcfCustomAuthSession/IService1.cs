using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace WcfCustomAuthSession
{

    [ServiceContract(Namespace = "http://wvm008.dei.isep.ipp.pt/graphService")]
    public interface IService1
    {
        
        [OperationContract]
        string Login(string Email, string Password);
        
        [OperationContract]
        User GetGraph(string Token,string Email,int graphDepth);

        [OperationContract]
        void Logout(string Token);
    }

    [DataContract]
    public class User
    {   
        [DataMember]
        public string Username { get; set; }

        [DataMember]
        public List<Connection> Connections{ get; set; }

        [DataMember]
        public List<UserTag> UserTags{ get; set; }
    }

    [DataContract]
    public class Connection
    {
        [DataMember]
        public int strength { get; set; }
        
        [DataMember]
        public User User { get; set; }

        [DataMember]
        public ConnectionTag ConnectionTag{ get; set;}

    }

    [DataContract]
    public class ConnectionTag
    {
        [DataMember]
        public string ConnectionTagName { get; set; }
    }
    
    [DataContract]
    public class UserTag
    {
        [DataMember]
        public string UserTagName { get; set; }
    }
}
