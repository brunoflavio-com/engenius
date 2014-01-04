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
    }


   
}
