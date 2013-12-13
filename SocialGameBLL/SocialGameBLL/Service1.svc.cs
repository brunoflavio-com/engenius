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
    public class Service1 : IService1
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
            SocialGameBLLDbContext db = new SocialGameBLLDbContext();
            UserEntity UserEntity = new UserEntity
            {
                Email = Email,
                HumourStatusID = 1
            };

            db.Users.Add(UserEntity);
            db.SaveChanges();

            SecurityService.RegisterUser(UserEntity, Password);
            
            return new User
            {
                Email = UserEntity.Email
            };
        }

        public User LoginUser(string Email, string Password)
        {
            SocialGameBLLDbContext db = new SocialGameBLLDbContext();
            User User = new User();

            if (SecurityService.LoginUser(Email, Password))
            {
                UserEntity UserEntity = db.Users.Find(Email);
                User.Email = UserEntity.Email;
            }
            return User;
        }
    }
}
