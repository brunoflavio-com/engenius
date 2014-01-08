using Newtonsoft.Json;
using SocialGameBLL.Entities;
using SocialGameBLL.Service;
using SocialGameBLL.Util;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Configuration;
using System.Linq;
using System.Net;
using System.Web;

namespace SocialGameBLL.Controllers
{
    public class UsersController
    {
        SocialGameBLLDbContext db = new SocialGameBLLDbContext();

        public User GetUser(string Email)
        {
            try
            {
                UserEntity UserEntity = db.Users.Find(Email);
                return EntityServiceConverter.ConvertUserEntityToUser(UserEntity);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public User UpdateUser(User User)
        {
            try
            {
                UserEntity UserEntity = db.Users.Find(User.Email);
                UpdateUserEntity(UserEntity, User);
                db.SaveChanges();
                return EntityServiceConverter.ConvertUserEntityToUser(UserEntity);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public ICollection<User> GetRelatedUsers(User User)
        {
            try
            {
                RelationshipsController RelationshipController = new RelationshipsController();
                Graph Graph = RelationshipController.GetRelationships(User, 1);
                ICollection<User> RelatedUsers = Graph.Users;
                foreach(User U in RelatedUsers)
                {
                    if (U.Email == User.Email)
                    {
                        RelatedUsers.Remove(U);
                        break;
                    }
                }
                return RelatedUsers;
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }

        }

        public int GetUserLevel(string Email)
        {
            try
            {
                UserEntity UserEntity = db.Users.Find(Email);
                SimpleModeScoreEntity Score = UserEntity.Score;
                return (Score == null || Score.Level == null) ? 0 : (int)Score.Level;
            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public int GetUserPoints(string Email)
        {
            try
            {
                UserEntity UserEntity = db.Users.Find(Email);
                SimpleModeScoreEntity Score = UserEntity.Score;
                return (Score == null || Score.Points == null) ? 0 : (int)Score.Points;
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public void SetUserLevel(string Email, int Level)
        {
            try
            {
                UserEntity UserEntity = db.Users.Find(Email);
                SimpleModeScoreEntity Score = UserEntity.Score;
                if (Score == null)
                {
                    Score = new SimpleModeScoreEntity
                    {
                        Level = Level,
                        Points = 0
                    };
                    UserEntity.Score = Score;
                }
                else
                {
                    Score.Level = Level;
                }
                db.SaveChanges();
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public void SetUserPoints(string Email, float Points)
        {
            try
            {
                UserEntity UserEntity = db.Users.Find(Email);
                SimpleModeScoreEntity Score = UserEntity.Score;
                if(Score == null)
                {
                    Score = new SimpleModeScoreEntity
                    {
                        Level = 0,
                        Points = Points
                    };
                    UserEntity.Score = Score;
                }
                else
                {
                    Score.Points = Points;
                }
                db.SaveChanges();
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public HumourStatus GetHumourStatus(int Id)
        {
            try
            {
                HumourStatusEntity HumourStatusEntity = db.HumourStatus.Find(Id);
                return EntityServiceConverter.ConvertToHumourStatusFromHumourStatusEntity(HumourStatusEntity);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public ICollection<HumourStatus> GetAllHumourStatus()
        {
            try
            {
                IList<HumourStatusEntity> HumourStatusEntities = db.HumourStatus.ToList();
                return EntityServiceConverter.ConvertToHumourStatusFromHumourStatusEntities(HumourStatusEntities);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public ICollection<User> GetFriendsWithCommonInterests(User Me, ICollection<Interest> Interests)
        {
            try
            {
                ICollection<int> InterestId = Interests.Select(i => i.Id).ToList();
                Graph graph = new RelationshipsController().GetRelationships(Me, 1);
                string Jsongraph = JsonConvert.SerializeObject(graph, Formatting.Indented);
                
                string AIService = ConfigurationManager.AppSettings["SocialGameAIURL"];
                CookieContainer CookieJar = new CookieContainer();

                string PostResponse = PrologRequest.MakeJsonPostRequest(PrologRequest.LOAD_USER_GRAPH, Jsongraph, CookieJar);

                string JsonInterest = JsonConvert.SerializeObject(InterestId);
                PostResponse = PrologRequest.MakeJsonPostRequest(PrologRequest.GET_FRIENDS_WITH_COMMON_INTERESTS, JsonInterest, CookieJar);
                
                ICollection<UserEntity> Entities = StringToUserEntity(PostResponse);
                ICollection<User> Users = new List<User>();

                foreach (UserEntity entity in Entities)
                {
                    Users.Add(EntityServiceConverter.ConvertUserEntityToUser(entity));
                }

                return Users;
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public ICollection<string> GetGraphStats(User Me)
        {
            try
            {

                Graph graph = new RelationshipsController().GetRelationships(Me, 2);
                string Jsongraph = JsonConvert.SerializeObject(graph, Formatting.Indented);

                string AIService = ConfigurationManager.AppSettings["SocialGameAIURL"];
                CookieContainer CookieJar = new CookieContainer();

                string PostResponse = PrologRequest.MakeJsonPostRequest(PrologRequest.LOAD_USER_GRAPH, Jsongraph, CookieJar);

                string JsonInterest = JsonConvert.SerializeObject(0);//To change
                PostResponse = PrologRequest.MakeJsonPostRequest(PrologRequest.GET_GRAPH_STATS, JsonInterest, CookieJar);

                //ICollection<UserEntity> Entities = StringToUserEntity(PostResponse);
                ICollection<string> Stats = new List<string>();

                //foreach (UserEntity entity in Entities)
                //{
                //    Users.Add(EntityServiceConverter.ConvertUserEntityToUser(entity));
                //}

                return Stats;
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public ICollection<User> GetPossibleFriends(User Me)
        {
            try
            {
                Graph graph = new RelationshipsController().GetRelationships(Me, 2);
                string Jsongraph = JsonConvert.SerializeObject(graph, Formatting.Indented);

                string AIService = ConfigurationManager.AppSettings["SocialGameAIURL"];
                CookieContainer CookieJar = new CookieContainer();

                string PostResponse = PrologRequest.MakeJsonPostRequest(PrologRequest.LOAD_USER_GRAPH, Jsongraph, CookieJar);

                string JsonInterest = JsonConvert.SerializeObject(0);//To change
                PostResponse = PrologRequest.MakeJsonPostRequest(PrologRequest.GET_POSSIBLE_FRIENDS, JsonInterest, CookieJar);

                ICollection<UserEntity> Entities = StringToUserEntity(PostResponse);
                ICollection<User> Users = new List<User>();

                foreach (UserEntity entity in Entities)
                {
                    Users.Add(EntityServiceConverter.ConvertUserEntityToUser(entity));
                }

                return Users;
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        /*Private helper methods*/
        private void UpdateUserEntity(UserEntity UserEntity, User User)
        {
            UserEntity.Name = User.Name;
            UserEntity.Surname = User.Surname;
            if (User.Birthdate != null)
            {
                UserEntity.Birthdate = (DateTime?)User.Birthdate;
            }
            UserEntity.HumourStatusID = User.HumourStatusId;
            UserEntity.PhoneNumber = User.PhoneNumber;
            UserEntity.FacebookProfile = User.FacebookProfile;
            UserEntity.LinkedInProfile = User.LinkedInProfile;
            UpdateInterests(UserEntity.Interests, User.InterestsIDs);
        }

        private void UpdateInterests(ICollection<InterestEntity> Interests, ICollection<int> InterestIDs)
        {
            if (InterestIDs != null)
            {
                foreach (int InterestID in InterestIDs)
                {
                    InterestEntity Interest = db.Interests.Find(InterestID);
                    if(!Interests.Contains(Interest))
                    {
                        Interests.Add(Interest);
                    }
                }
            }
        }

        private ICollection<UserEntity> StringToUserEntity(string JsonEmails)
        {
            ICollection<UserEntity> returnList = new List<UserEntity>();
            var array = JsonConvert.DeserializeObject<ICollection<string>>(JsonEmails);
            foreach (var email in array)
            {
                returnList.Add(db.Users.Find(email));
            }
            return returnList;
        }
    }
}