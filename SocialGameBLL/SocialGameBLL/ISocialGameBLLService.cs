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
        int GetTotalNumberOfUsers();
        [OperationContract]
        User UpdateUser(User User);
        [OperationContract]
        HumourStatus GetHumourStatus(int Id);
        [OperationContract]
        ICollection<HumourStatus> GetAllHumourStatus();
        [OperationContract]
        ICollection<RelationshipTag> GetRelationshipTags();
        [OperationContract]
        RelationshipTag GetRelationshipTag(int Id);
        [OperationContract]
        ICollection<User> GetRelatedUsers(User User);
        [OperationContract]
        Relationship GetRelationship(User Me, User Other);
        [OperationContract]
        bool CheckRelationship(User Me, User Other);
        [OperationContract]
        void DeleteRelationship(User Me, User Other);
        [OperationContract]
        Graph GetRelationships(User User, int Depth);
        [OperationContract]
        RelationshipRequest MakeRelationshipRequest(User Me, User Other, int RelationshipTagId, int Strength);
        [OperationContract]
        void AcceptRelationshipRequest(User Me, User Other);
        [OperationContract]
        void RejectRelationshipRequest(User Me, User Other);
        [OperationContract]
        ICollection<RelationshipRequest> GetUserPendingRequests(User Me);
        [OperationContract]
        ICollection<RelationshipRequest> GetPendingRequestsToUser(User Me);
        [OperationContract]
        RelationshipRequest GetPendingRequest(User Me, User Other);
        [OperationContract]
        bool CheckPendingRequest(User Me, User Other);
        [OperationContract]
        ICollection<User> GetShortestPath(User Me, User Goal, int Depth);
        [OperationContract]
        int GetUserLevel(string Email);
        [OperationContract]
        float GetUserPoints(string Email);
        [OperationContract]
        void SetUserLevel(string Email, int Level);
        [OperationContract]
        void SetUserPoints(string Email, float Points);
        [OperationContract]
        ICollection<User> GetFriendsWithCommonInterests(User Me, ICollection<Interest> Interests);

        [OperationContract]
        ICollection<string> GetGraphStats(User Me);

        [OperationContract]
        ICollection<User> GetPossibleFriends(User Me);

        [OperationContract]
        Interest AddInterestToUser(User Me, Interest Interest, string Freebase);

        [OperationContract]
        void RemoveInterestFromUser(User Me, Interest Interest);

        [OperationContract]
        Interest GetInterest(int InterestID);

        [OperationContract]
        ICollection<Interest> GetUserInterests(User Me);

        [OperationContract]
        IDictionary<string, int> GetInterestsTagCloud(User Me);

        [OperationContract]
        IDictionary<string, int> GetRelationshipsTagCloud(User Me);
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
