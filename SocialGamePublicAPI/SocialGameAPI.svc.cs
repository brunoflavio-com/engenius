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
    [ServiceBehavior(Namespace = "http://wvm008.dei.isep.ipp.pt")]
    public class SocialGameService : ISocialGameService
    {
        private SessionContext db = new SessionContext();

        public string Login(string IEmail, string Password)
        {
            if (validateLogin(IEmail,Password))
            {
                string Token = Convert.ToBase64String(Guid.NewGuid().ToByteArray());
                db.Sessions.Add(new Session
                {
                    Token = Token,
                    Email = IEmail
                });
                db.SaveChangesAsync();
                
                return Token;
            }
            else
            {
                throw new FaultException("Wrong Username/Password");
            }

        }
        public void Logout(string Token) {
            Session Session = getSession(Token);

            db.Sessions.Remove(Session);
            
            db.SaveChangesAsync();
        }

        public UserContract GetGraph(string Token, string UserName, int graphDepth) {
            //TestData - TODO Integrate with BLL

            Session session = getSession("1");

            JavaScriptSerializer jser = new JavaScriptSerializer();
            UserContract User = jser.Deserialize<UserContract>(session.JsonGraph);
            return User;
        }

        private bool validateLogin(string Email, string Password)
        {
            
            //TODO Integrate with BLL
            if (Email == "xiko" && Password == "qwerty")
            {
                return true;
            }
            else {
                return false;
            }
        }

        private Session getSession(string Token)
        {
            Session Session = db.Sessions.Find(Token);

            if (Session == null )
            {
                throw new FaultException("Token not reconized");
            }

            Session.LastConnectionTime = System.DateTime.Now;
            return Session;
        }  
    }
    
}
