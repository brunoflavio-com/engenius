using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Collections.Concurrent;
using WcfCustomAuthSession.Model;
using System.Security.Cryptography;

namespace WcfCustomAuthSession
{
    [ServiceBehavior(Namespace = "http://wvm008.dei.isep.ipp.pt/graphService")]
    public class Service1 : IService1
    {
        private SessionContext db = new SessionContext();

        public string Login(string Email, string Password)
        {
            if (validateLogin(Email,Password))
            {
                string Token = Convert.ToBase64String(Guid.NewGuid().ToByteArray());
                db.Sessions.Add(new Session
                {
                    Token = Token,
                    Email = Email
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

        public User GetGraph(string Token, string UserName, int graphDepth) {
            Session session = getSession(Token);
            //TestData
            ConnectionTag cTag = new ConnectionTag
            {
                ConnectionTagName = "Familia"
            };

            UserTag UTag = new UserTag
            {
                UserTagName = "Pudim"
            };

            User Eli  = new User
            {
                Username = "Eli"

            };

            User Dinis = new User
            {
                Username = "Dinis"

            };

            List<Connection> connections = new List<Connection>();
            connections.Add(new Connection
            {
                strength = 100,
                User = Dinis,
                ConnectionTag=cTag
            });
            
            connections.Add(new Connection
            {
                strength = 200,
                User = Eli,
                ConnectionTag = cTag
            });

            List<UserTag> UserTags = new List<UserTag>();
            UserTags.Add(new UserTag
            {
                UserTagName = "Pudim"
            });
            UserTags.Add(new UserTag
            {
                UserTagName = "C++"
            });


            User User = new User { 
            Username = "xiko",
            Connections = connections,
            UserTags = UserTags
            };

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
