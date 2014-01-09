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

        public List<string> getRandomWordCategories(string Token, int number){

            
            Session Session = getSession(Token);
            SessionContext context = new SessionContext();
            List<WordCategory> categories = context.Categories.ToList<WordCategory>();
            if (number > categories.Count()) {
                throw new FaultException("Not enough categories");
            }
            Random random = new Random();
            List<string> tempCategories = new List<string>();
            List<int> numbers = new List<int>();
            for (int i = 0; i < number; i++)
            {
                int randomNumber = -1;
                    while(randomNumber==-1 || numbers.Contains(randomNumber))
                    {
                         randomNumber = random.Next(0, categories.Count());
                    }
                    numbers.Add(randomNumber);
                tempCategories.Add(categories.ElementAt(randomNumber).CategoryName);
            }
            return tempCategories;
        }

        public string getRandomWordFromCategory(string Token, string category)
        {
            Session Session = getSession(Token);
            SessionContext context = new SessionContext();
            WordCategory wordCategory = context.Categories.First(e => e.CategoryName == category);
            Random random = new Random();
            List<string> tempCategories = new List<string>();
            int randomNumber = random.Next(0, wordCategory.words.Count());
            return wordCategory.words.ElementAt(randomNumber).word;    
        }

        public string getMaze(string Token, int id)
        {
            Session Session = getSession(Token);
            SessionContext context = new SessionContext();
            Maze maze = context.mazes.First(e => e.id == id);
            return maze.mazeText;
        }

        public Service.UserGameInfo getUserGameInfo(string Token){
            Session Session = getSession(Token);
            Service.User User = getUser(Session);
            int userLevel = BLLClient.GetUserLevel(User.Email);
            float userPoints = BLLClient.GetUserPoints(User.Email);
            Service.UserGameInfo userGameInfo = new Service.UserGameInfo();
            userGameInfo.Level = userLevel;
            userGameInfo.Points = userPoints;
            return userGameInfo;
        }

        public void setUserLevel(string Token, int Level)
        {
            Session Session = getSession(Token);
            Service.User User = getUser(Session);
            BLLClient.SetUserLevel(User.Email, Level); 
        }
        
        public void setUserPoints(string Token, float Points)
        {
            Session Session = getSession(Token);
            Service.User User = getUser(Session);
            BLLClient.SetUserPoints(User.Email, Points);
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
        private Service.User getUser(Session session)
        {
            string jsonUser = session.JsonUser;  
            JavaScriptSerializer jsonSerializer =  new JavaScriptSerializer();
            Service.User user = jsonSerializer.Deserialize<Service.User>(jsonUser);
            return user;
        }

    }

}
