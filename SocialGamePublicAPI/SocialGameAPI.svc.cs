using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using SocialGamePublicAPI.Model;
using System.Web.Script.Serialization;

namespace SocialGamePublicAPI
{
    [ServiceBehavior(Namespace = "http://wvm008.dei.isep.ipp.pt/SocialGamePublicAPI")]
    public class SocialGameService : ISocialGameService
    {
        private SessionContext db = new SessionContext();

        private SocialGameBLLService.SocialGameBLLServiceClient BLLClient = new SocialGameBLLService.SocialGameBLLServiceClient();

        public string Login(string IEmail, string Password)
        {
            Service.User User;
            try
            {
                User = validateLogin(IEmail, Password);
            }
            catch (FaultException e)
            {
                return "";
            }
                string Token = Convert.ToBase64String(Guid.NewGuid().ToByteArray());
                string json = new JavaScriptSerializer().Serialize(User);
                db.Sessions.Add(new Session
                {
                    Token = Token,
                    JsonUser = json 
                });
                db.SaveChangesAsync();
                return Token;
        }
        
        public void Logout(string Token)
        {
            Session Session = getSession(Token);

            db.Sessions.Remove(Session);

            db.SaveChangesAsync();
        }

        public Service.Graph GetGraph(string Token, string Email, int graphDepth) {
            
            Session Session = getSession(Token);
            JavaScriptSerializer jsonSerializer =  new JavaScriptSerializer();
            SocialGameBLLService.User User = new SocialGameBLLService.User
            {
                Email = Email
            };
            SocialGameBLLService.Graph BLLGraph =  BLLClient.GetRelationships(User, graphDepth);
            return Service.ServiceConverter.convertGraph(BLLGraph);
        }

        private Service.User validateLogin(string Email, string Password)
        {
             
            SocialGameBLLService.User BLLUser =  BLLClient.LoginUser(Email, Password);
            return  Service.ServiceConverter.convertUser(BLLUser);
        }

        private Session getSession(string Token)
        {
            Session Session = db.Sessions.Find(Token);

            if (Session == null)
            {
                throw new FaultException("Token not reconized");
            }

            Session.LastConnectionTime = System.DateTime.Now;
            return Session;
        }
    }

}
