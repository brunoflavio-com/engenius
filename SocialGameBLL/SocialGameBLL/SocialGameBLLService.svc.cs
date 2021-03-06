﻿using SocialGameBLL.Controllers;
using SocialGameBLL.Entities;
using SocialGameBLL.Security;
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
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class SocialGameBLLService : ISocialGameBLLService
    {
        public string GetData(int value)
        {
            return string.Format("You entered: {0}", value);
        }

        public CompositeType GetDataUsingDataContract(CompositeType composite)
        {
            if (composite == null)
            {
                throw new ArgumentNullException("composite");
            }
            if (composite.BoolValue)
            {
                composite.StringValue += "Suffix";
            }
            return composite;
        }

        public User RegisterUser(string Email, string Password)
        {
            try
            {
                AuthenticationController Controller = new AuthenticationController();
                return Controller.RegisterUser(Email, Password);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public User LoginUser(string Email, string Password)
        {
            try{
                AuthenticationController Controller = new AuthenticationController();
                return Controller.LoginUser(Email, Password);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public int GetTotalNumberOfUsers()
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetTotalNumberOfUsers();
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<RelationshipTag> GetRelationshipTags()
        {
            RelationshipsController Controller = new RelationshipsController();
            return Controller.GetRelationshipTags();
        }

        public RelationshipTag GetRelationshipTag(int Id)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                return Controller.GetRelationshipTag(Id);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public Graph GetRelationships(User User, int Depth)
        {
            RelationshipsController Controller = new RelationshipsController();
            return Controller.GetRelationships(User, Depth);
        }

        public ICollection<User> GetRelatedUsers(User User)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetRelatedUsers(User);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public Relationship GetRelationship(User Me, User Other)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                return Controller.GetRelationship(Me, Other);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public bool CheckRelationship(User Me, User Other)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                Relationship Relationship = Controller.GetRelationship(Me, Other);
                return (Relationship == null) ? false : true;
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public void DeleteRelationship(User Me, User Other)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                Controller.DeleteRelationship(Me, Other);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public User GetUser(string Email)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetUser(Email);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public User UpdateUser(User User)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.UpdateUser(User);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public HumourStatus GetHumourStatus(int Id)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetHumourStatus(Id);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<HumourStatus> GetAllHumourStatus()
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetAllHumourStatus();
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public RelationshipRequest MakeRelationshipRequest(User Me, User Other, int RelationshipTagId, int Strength)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                return Controller.MakeRelationshipRequest(Me, Other, RelationshipTagId, Strength);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public void AcceptRelationshipRequest(User Me, User Other)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                Controller.AcceptRelationshipRequest(Me, Other);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public void RejectRelationshipRequest(User Me, User Other)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                Controller.RejectRelationshipRequest(Me, Other);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<RelationshipRequest> GetUserPendingRequests(User Me)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                return Controller.GetUserPendingRequests(Me);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<RelationshipRequest> GetPendingRequestsToUser(User Me)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                return Controller.GetPendingRequestsToUser(Me);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public RelationshipRequest GetPendingRequest(User Me, User Other)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                return Controller.GetPendingRequest(Me, Other);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public bool CheckPendingRequest(User Me, User Other)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                RelationshipRequest RelationshipRequest = Controller.GetPendingRequest(Me, Other);
                return (RelationshipRequest == null) ? false : true;
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<User> GetShortestPath(User Me, User Goal, int Depth)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                return Controller.GetShortestPath(Me, Goal, Depth);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public int GetUserLevel(string Email)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetUserLevel(Email);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<User> GetFriendsWithCommonInterests(User Me, ICollection<Interest> Interests)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetFriendsWithCommonInterests(Me,Interests);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public NetworkStatistics GetGraphStats(User Me = null)
        {
            try
            {
                UsersController Controller = new UsersController();
                //Global Stats
                if (Me == null)
                {
                    return Controller.GetGraphStats();
                }
                //User Stats
                else 
                { 
                    return Controller.GetGraphStats(Me); 
                }
                
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<User> GetPossibleFriends(User Me)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetPossibleFriends(Me);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public float GetUserPoints(string Email)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetUserPoints(Email);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public void SetUserLevel(string Email, int Level)
        {
            try
            {
                UsersController Controller = new UsersController();
                Controller.SetUserLevel(Email, Level);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public void SetUserPoints(string Email, float Points)
        {
            try
            {
                UsersController Controller = new UsersController();
                Controller.SetUserPoints(Email, Points);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public Interest AddInterestToUser(User User, Interest Intrerest, string FreebaseId)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.AddInterestToUser(User, Intrerest, FreebaseId);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public void RemoveInterestFromUser(User Me, Interest Interest)
        {
            try
            {
                UsersController Controller = new UsersController();
                Controller.RemoverInterestFromUser(Me, Interest);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public Interest GetInterest(int InterestID)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetInterest(InterestID);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<Interest> GetUserInterests(User Me)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetUserInterests(Me);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public IDictionary<string, int> GetInterestsTagCloud(User User)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetInterestsTagCloud(User);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public IDictionary<string, int> GetRelationshipsTagCloud(User User)
        {
            try
            {
                RelationshipsController Controller = new RelationshipsController();
                return Controller.GetRelationshipsTagCloud(User);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<UserScore> GetPaginatedUsersScores(int ElementsPerPage, int PageNumber)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetPaginatedUsersScores(ElementsPerPage, PageNumber);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<UserNetworkSizeScore> GetPaginatedUsersNetworkSizeScores(int ElementsPerPage, int PageNumber)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetPaginatedUsersNetworkSizeScores(ElementsPerPage, PageNumber);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public ICollection<UserNetworkStrengthScore> GetPaginatedUsersNetworkStrengthScores(int ElementsPerPage, int PageNumber)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetPaginatedUsersNetworkStrengthScores(ElementsPerPage, PageNumber);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public UserNetworkSizeScore GetUserNetworkSizeScore(User Me)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetUserNetworkSizeScore(Me);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public UserNetworkStrengthScore GetUserNetworkStrengthScore(User Me)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetUserNetworkStrengthScore(Me);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public UserScore GetUserScore(User Me)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetUserScore(Me);
            }catch(Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public void LogDownload(string UserEmail, string Ip)
        {
            try
            {
                DownloadsController Controller = new DownloadsController();
                Controller.LogDownload(UserEmail, Ip);
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }

        public int GetTotalNumberOfDownloads()
        {
            try
            {
                DownloadsController Controller = new DownloadsController();
                return Controller.GetTotalNumberOfDownloads();
            }
            catch (Exception e)
            {
                throw new FaultException(e.Message);
            }
        }
    }
}
