using SocialGameBLL.Controllers;
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

        public ICollection<string> GetGraphStats(User Me)
        {
            try
            {
                UsersController Controller = new UsersController();
                return Controller.GetGraphStats(Me);
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
    }
}
