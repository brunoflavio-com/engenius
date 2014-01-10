using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using SocialGamePublicAPI.Service;

namespace SocialGamePublicAPI
{

     [ServiceContract(Namespace = "http://wvm008.dei.isep.ipp.pt/SocialGamePublicAPI")]
    public interface ISocialGameService
    {

        [OperationContract]
        [FaultContract(typeof(FaultException))]
        string Login(string Email, string Password);

        [OperationContract]
        [FaultContract(typeof(FaultException))]
        Service.Graph GetGraph(string Token, string Email, int graphDepth);

        [OperationContract]
        [FaultContract(typeof(FaultException))]
        void Logout(string Token);

        [OperationContract]
        [FaultContract(typeof(FaultException))]
        List<string> getRandomWordCategories(string Token, int number);

        [OperationContract]
        [FaultContract(typeof(FaultException))]
        string getRandomWordFromCategory(string Token, string category);

        [OperationContract]
        [FaultContract(typeof(FaultException))]
        string getMaze(string Token, int id);

        [OperationContract]
        [FaultContract(typeof(FaultException))]
        Service.UserGameInfo getUserGameInfo(string Token);

        [OperationContract]
        [FaultContract(typeof(FaultException))]
        void setUserLevel(string Token, int Level);

        [OperationContract]
        [FaultContract(typeof(FaultException))]
        void setUserPoints(string Token, float Points);
        
    }


   
}
