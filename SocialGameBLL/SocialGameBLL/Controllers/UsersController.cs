using SocialGameBLL.Entities;
using SocialGameBLL.Service;
using SocialGameBLL.Util;
using System;
using System.Collections.Generic;
using System.Linq;
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
    }
}