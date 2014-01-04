using SocialGameBLL.Service;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace SocialGameBLL
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    [ServiceContract]
    public interface ISocialGameBLLService
    {

        [OperationContract]
        string GetData(int value);

        [OperationContract]
        CompositeType GetDataUsingDataContract(CompositeType composite);

        // TODO: Add your service operations here
        [OperationContract]
        User RegisterUser(string Email, string Password);
        [OperationContract]
        [FaultContract(typeof(FaultException))]
        User LoginUser(string Email, string Password);
        [OperationContract]
        User GetUser(string Email);
        [OperationContract]
        User UpdateUser(User User);
        [OperationContract]
        HumourStatus GetHumourStatus(int Id);
        [OperationContract]
        ICollection<HumourStatus> GetAllHumourStatus();
        [OperationContract]
        ICollection<RelationshipTag> GetRelationshipTags();
        [OperationContract]
        Graph GetRelationships(User User, int Depth);
        [OperationContract]
        RelationshipRequest MakeRelationshipRequest(User Me, User Other, int RelationshipTagId, int Strength);
        [OperationContract]
        ICollection<User> GetShortestPath(User Me, User Goal, int Depth);
    }


    // Use a data contract as illustrated in the sample below to add composite types to service operations.
    [DataContract]
    public class CompositeType
    {
        bool boolValue = true;
        string stringValue = "Hello ";

        [DataMember]
        public bool BoolValue
        {
            get { return boolValue; }
            set { boolValue = value; }
        }

        [DataMember]
        public string StringValue
        {
            get { return stringValue; }
            set { stringValue = value; }
        }
    }
}
