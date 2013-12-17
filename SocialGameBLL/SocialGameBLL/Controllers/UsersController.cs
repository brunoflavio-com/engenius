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

        public User UpdateUser(User User)
        {
            try
            {
                UserEntity UserEntity = db.Users.Find(User.Email);
                UpdateUserEntity(UserEntity, User);
                db.SaveChanges();
                return EntitieServiceConvert.ConvertUserEntityToUser(UserEntity);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message);
            }
        }

        private void UpdateUserEntity(UserEntity UserEntity, User User)
        {
            UserEntity.Name = User.Name;
            UserEntity.Surname = User.Surname;
            if (User.Birthdate != null)
            {
                UserEntity.Birthdate = (DateTime?)UserEntity.Birthdate;
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