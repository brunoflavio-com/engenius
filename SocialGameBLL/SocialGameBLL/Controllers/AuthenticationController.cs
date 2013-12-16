using SocialGameBLL.Entities;
using SocialGameBLL.Security;
using SocialGameBLL.Service;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Controllers
{
    public class AuthenticationController
    {
        public User RegisterUser(string Email, string Password)
        {
            SocialGameBLLDbContext db = new SocialGameBLLDbContext();

            try
            {
                UserEntity UserEntity = SecurityService.RegisterUser(Email, Password);

                return ConvertUserEntityToUser(UserEntity);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message);
            }
        }

        public User LoginUser(string Email, string Password)
        {
            try
            {
                UserEntity UserEntity = SecurityService.LoginUser(Email, Password);
                return ConvertUserEntityToUser(UserEntity);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message);
            }
        }

        private User ConvertUserEntityToUser(UserEntity UserEntity)
        {
            return new User
            {
                Email = UserEntity.Email,
                Name = UserEntity.Name,
                Surname = UserEntity.Surname,
                Birthdate = (UserEntity.Birthdate != null) ? (DateTime)UserEntity.Birthdate : DateTime.MinValue,
                HumourStatusId = UserEntity.HumourStatusID,
                InterestsIDs = GetInterestsIdsFromInterests(UserEntity.Interests),
                FacebookProfile = UserEntity.FacebookProfile,
                LinkedInProfile = UserEntity.LinkedInProfile,
                PhoneNumber = UserEntity.PhoneNumber
            };
        }

        private ICollection<int> GetInterestsIdsFromInterests(ICollection<InterestEntity> Interests)
        {
            ICollection<int> InterestsIDs = new List<int>();
            if (Interests != null)
            {
                foreach (InterestEntity Interest in Interests)
                {
                    InterestsIDs.Add(Interest.ID);
                }
            }
            return InterestsIDs;
        }
    }
}