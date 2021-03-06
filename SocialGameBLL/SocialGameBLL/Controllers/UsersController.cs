﻿using Newtonsoft.Json;
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
using SocialGameBLL.AdvancedModeScores;

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

        public int GetTotalNumberOfUsers()
        {
            try
            {
                return db.Users.Count();
            }catch(Exception e)
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
                    if (entity.Email != Me.Email)
                        Users.Add(EntityServiceConverter.ConvertUserEntityToUser(entity));
                }

                return Users;
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public NetworkStatistics GetGraphStats(User Me)
        {
            try
            {

                Graph graph = new RelationshipsController().GetRelationships(Me, 2);
                if (graph.Relationships.Count == 0)
                {
                    var JsonStats = new
                    {
                        TotalFriends = 1,
                        AverageStrength = 0
                    };
                    string JsonStatsString = JsonConvert.SerializeObject(JsonStats, Formatting.Indented);
                    NetworkStatistics Stats = StringToNetworkStatistics(JsonStatsString);

                    return Stats;
                }
                else
                {
                    string Jsongraph = JsonConvert.SerializeObject(graph, Formatting.Indented);

                    string AIService = ConfigurationManager.AppSettings["SocialGameAIURL"];
                    CookieContainer CookieJar = new CookieContainer();

                    string PostResponse = PrologRequest.MakeJsonPostRequest(PrologRequest.LOAD_USER_GRAPH, Jsongraph, CookieJar);

                    PostResponse = PrologRequest.MakeJsonGetResquest(PrologRequest.GET_GRAPH_STATS, null, CookieJar);

                    NetworkStatistics Stats = StringToNetworkStatistics(PostResponse);

                    return Stats;
                }
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public NetworkStatistics GetGraphStats()
        {
            try
            {
                NetworkStatistics NetworkStatistics = new NetworkStatistics
                {
                    UserCount = db.Users.Count(),
                    RelationshipStrenghtAverage = db.Relationships.Select(r => r.Strength).Average()
                };

                return NetworkStatistics;
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

                OrderedDictionary param = new OrderedDictionary();
                param["useremail"]=Me.Email;
                PostResponse = PrologRequest.MakeJsonGetResquest(PrologRequest.GET_POSSIBLE_FRIENDS, param, CookieJar);

                ICollection<UserEntity> Entities = StringToUserEntity(PostResponse);

                if (Entities.Count == 0)
                {
                    Entities = db.Users.OrderByDescending(u => u.Interests.Count).Take(5).ToList();
                }

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

        public Interest AddInterestToUser(User Me, Interest Interest, string  FreebaseId)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);

                InterestEntity InterestEntity;
                try
                {
                    InterestEntity = db.Interests.Single(i => i.FreebaseId == FreebaseId);
                }catch(Exception e)
                {
                    InterestEntity = new InterestEntity 
                    { 
                        FreebaseId = FreebaseId,
                        Name = Interest.Name
                    };
                    db.Interests.Add(InterestEntity);
                }

                MyEntity.Interests.Add(InterestEntity);
                db.SaveChanges();
                return EntityServiceConverter.ConvertInterestEntityToInterest(InterestEntity);
            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public void RemoverInterestFromUser(User Me, Interest Interest)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);
                InterestEntity InterestEntity = db.Interests.Find(Interest.Id);

                MyEntity.Interests.Remove(InterestEntity);
                db.SaveChanges();
            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public Interest GetInterest(int InterestID)
        {
            InterestEntity InterestEntity;
            try
            {
                InterestEntity = db.Interests.Single(i => i.ID == InterestID);
                return EntityServiceConverter.ConvertInterestEntityToInterest(InterestEntity);
            } catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public ICollection<Interest> GetUserInterests(User Me)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);
                ICollection<InterestEntity> InterestEntities = MyEntity.Interests.ToList();
                return EntityServiceConverter.ConvertToInterestFromInterestEntities(InterestEntities);
            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public IDictionary<string, int> GetInterestsTagCloud(User Me = null)
        {
            try
            {
                ICollection<User> Users = AssembleUserList(Me);

                //Count how many times each interest shows up:
                Dictionary<int, int> InterestCount = new Dictionary<int,int>();
                foreach (User user in Users) {
                    foreach (int interestID in user.InterestsIDs)
                    {
                        int count;
                        if (InterestCount.TryGetValue(interestID, out count))
                        {
                            InterestCount[interestID] = count + 1;
                        }
                        else
                        {
                            InterestCount[interestID] = 1;
                        }
                    }
                }

                //Get the interests from the id:
                Dictionary<string, int> InterestsCloud = new Dictionary<string, int>();
                foreach (KeyValuePair<int, int> interestCountEntry in InterestCount)
                {
                    InterestEntity InterestEntity = db.Interests.Find(interestCountEntry.Key);
                    InterestsCloud.Add(InterestEntity.Name, interestCountEntry.Value);
                }

                return InterestsCloud;
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public ICollection<UserScore> GetPaginatedUsersScores(int ElementsPerPage, int PageNumber)
        {
            ICollection<SimpleModeScoreEntity> OrderedScores = db.Scores.OrderByDescending(s => s.Points).ToList();
            ICollection<UserScore> RequestedScores = new List<UserScore>();

            int firstPosition = (PageNumber - 1) * ElementsPerPage;
            for (int i = firstPosition; i < firstPosition + ElementsPerPage; i++ )
            {
                if (i < OrderedScores.Count)
                {
                    SimpleModeScoreEntity SimpleScore = OrderedScores.ElementAt(i);
                    UserEntity UserEntity = db.Users.Find(SimpleScore.UserEmail);
                    RequestedScores.Add(new UserScore
                    {
                        Position = i + 1,
                        UserEmail = SimpleScore.UserEmail,
                        UserLevel = (SimpleScore.Level == null) ? 0 : (int)SimpleScore.Level,
                        UserPoints = (SimpleScore.Points == null) ? 0.0f : (float)SimpleScore.Points,
                        UserName = UserEntity.Name,
                        UserSurname = UserEntity.Surname
                    });
                }
            }
            return RequestedScores;
        }

        public ICollection<UserNetworkSizeScore> GetPaginatedUsersNetworkSizeScores(int ElementsPerPage, int PageNumber)
        {
            AdvancedModeScoresSingleton AdvancedScores = AdvancedModeScoresSingleton.GetInstance();
            IList<NetworkSizeScore> OrderedSizeScores = AdvancedScores.GetSizeScores().OrderByDescending(s => s.NetworkSize).ToList();
            ICollection<UserNetworkSizeScore> RequestedScores = new List<UserNetworkSizeScore>();

            int firstPosition = (PageNumber - 1) * ElementsPerPage;
            for (int i = firstPosition; i < firstPosition + ElementsPerPage; i++)
            {
                if (i < OrderedSizeScores.Count)
                {
                    NetworkSizeScore SizeScore = OrderedSizeScores.ElementAt(i);
                    UserEntity UserEntity = db.Users.Find(SizeScore.UserEmail);
                    RequestedScores.Add(new UserNetworkSizeScore
                    {
                        Position = i + 1,
                        UserEmail = SizeScore.UserEmail,
                        UserNetworkSize = SizeScore.NetworkSize,
                        UserName = UserEntity.Name,
                        UserSurname = UserEntity.Surname
                    });
                }
            }
            return RequestedScores;
        }

        public ICollection<UserNetworkStrengthScore> GetPaginatedUsersNetworkStrengthScores(int ElementsPerPage, int PageNumber)
        {
            AdvancedModeScoresSingleton AdvancedScores = AdvancedModeScoresSingleton.GetInstance();
            IList<NetworkStrengthScore> OrderedStrengthScores = AdvancedScores.GetStrengthScores().OrderByDescending(s => s.AvarageStregth).ToList();
            ICollection<UserNetworkStrengthScore> RequestedScores = new List<UserNetworkStrengthScore>();

            int firstPosition = (PageNumber - 1) * ElementsPerPage;
            for (int i = firstPosition; i < firstPosition + ElementsPerPage; i++)
            {
                if (i < OrderedStrengthScores.Count)
                {
                    NetworkStrengthScore StrengthScore = OrderedStrengthScores.ElementAt(i);
                    UserEntity UserEntity = db.Users.Find(StrengthScore.UserEmail);
                    RequestedScores.Add(new UserNetworkStrengthScore
                    {
                        Position = i + 1,
                        UserEmail = StrengthScore.UserEmail,
                        UserNetworkStrength = StrengthScore.AvarageStregth,
                        UserName = UserEntity.Name,
                        UserSurname = UserEntity.Surname
                    });
                }
            }
            return RequestedScores;
        }
       
        public UserNetworkSizeScore GetUserNetworkSizeScore(User Me)
        {
            UserEntity MyEntity = db.Users.Find(Me.Email);
            AdvancedModeScoresSingleton AdvancedScores = AdvancedModeScoresSingleton.GetInstance();
            IList<NetworkSizeScore> OrderedSizeScores = AdvancedScores.GetSizeScores().OrderByDescending(s => s.NetworkSize).ToList();

            try
            {
                NetworkSizeScore SizeScore = OrderedSizeScores.First(s => s.UserEmail == MyEntity.Email);
                int i = OrderedSizeScores.IndexOf(SizeScore);
                return new UserNetworkSizeScore
                {
                    Position = i + 1,
                    UserEmail = SizeScore.UserEmail,
                    UserNetworkSize = SizeScore.NetworkSize,
                    UserName = MyEntity.Name,
                    UserSurname = MyEntity.Surname
                };
            }catch(Exception e)
            {
                return null;
            }
        }

        public UserNetworkStrengthScore GetUserNetworkStrengthScore(User Me)
        {
            UserEntity MyEntity = db.Users.Find(Me.Email);
            AdvancedModeScoresSingleton AdvancedScores = AdvancedModeScoresSingleton.GetInstance();
            IList<NetworkStrengthScore> OrderedSizeScores = AdvancedScores.GetStrengthScores().OrderByDescending(s => s.AvarageStregth).ToList();

            try
            {
                NetworkStrengthScore StrengthScore = OrderedSizeScores.First(s => s.UserEmail == MyEntity.Email);
                int i = OrderedSizeScores.IndexOf(StrengthScore);
                return new UserNetworkStrengthScore
                {
                    Position = i + 1,
                    UserEmail = StrengthScore.UserEmail,
                    UserNetworkStrength = StrengthScore.AvarageStregth,
                    UserName = MyEntity.Name,
                    UserSurname = MyEntity.Surname
                };
            }
            catch (Exception e)
            {
                return null;
            }
        }

        public UserScore GetUserScore(User Me)
        {
            UserEntity MyEntity = db.Users.Find(Me.Email);
            IList<SimpleModeScoreEntity> OrderedScores = db.Scores.OrderByDescending(s => s.Points).ToList();

            try
            {
                SimpleModeScoreEntity Score = OrderedScores.First(s => s.UserEmail == MyEntity.Email);
                int i = OrderedScores.IndexOf(Score);
                return new UserScore
                {
                    Position = i + 1,
                    UserEmail = Score.UserEmail,
                    UserLevel = (Score.Level == null) ? 0 : (int)Score.Level,
                    UserPoints = (Score.Points == null) ? 0.0f : (float)Score.Points,
                    UserName = MyEntity.Name,
                    UserSurname = MyEntity.Surname
                };
            }catch(Exception e)
            {
                return null;
            }
        }



        /*Private helper methods*/
        private ICollection<User> AssembleUserList(User CentralUser = null)
        {
            ICollection<User> Users;
            if (CentralUser == null)
            {   //Global Network Interests cloud:
                Users = new List<User>();

                ICollection<UserEntity> UserEntities = db.Users.ToList();
                foreach (UserEntity userEntity in UserEntities)
                {
                    Users.Add(EntityServiceConverter.ConvertUserEntityToUser(userEntity));
                }
            }
            else
            {   //User Network Interests cloud:
                RelationshipsController RelationshipController = new RelationshipsController();
                Graph Graph = RelationshipController.GetRelationships(CentralUser, 2);
                Users = Graph.Users;
            }

            return Users;
        }

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

        private NetworkStatistics StringToNetworkStatistics(string JsonStatistics)
        {
            dynamic prologStats = JsonConvert.DeserializeObject<dynamic>(JsonStatistics);

            NetworkStatistics Stats = new NetworkStatistics();
            Stats.UserCount = prologStats["TotalFriends"];
            Stats.RelationshipStrenghtAverage = prologStats["AverageStrength"];

            return Stats;
        }
    }
}