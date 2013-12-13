using SocialGameBLL.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Web;

namespace SocialGameBLL.Security
{
    public static class SecurityService
    {

        public static UserEntity RegisterUser(string Email, string Password)
        {
            byte[] PasswordBytes = GetBytesFromString(Password);
            byte[] SaltBytes = new byte[128];
            SocialGameBLLDbContext db = new SocialGameBLLDbContext();

            UserEntity UserEntity = db.Users.Find(Email);

            if (UserEntity != null)
            {
                throw new Exception("Already Exists a user with the same email address");
            }

            UserEntity = new UserEntity
            {
                Email = Email,
                HumourStatusID = 1
            };

            db.Users.Add(UserEntity);

            RNGCryptoServiceProvider CryptoProvider = new RNGCryptoServiceProvider();
            CryptoProvider.GetBytes(SaltBytes);

            byte[] PasswordHash = GenerateHash(PasswordBytes, SaltBytes);

            UserSecurity UserSecurity = new UserSecurity
            {
                UserEmail = UserEntity.Email,
                Password = PasswordHash,
                Salt = SaltBytes
            };

            db.Passwords.Add(UserSecurity);
            db.SaveChanges();
            return UserEntity;
        }

        public static UserEntity LoginUser(string UserEmail, string Challenge)
        {
            SocialGameBLLDbContext db = new SocialGameBLLDbContext();
            UserSecurity PasswordForEmail = db.Passwords.Find(UserEmail);

            if (PasswordForEmail == null)
            {
                throw new Exception("No user with email " + UserEmail);
            }

            byte[] ChallengeBytes = GetBytesFromString(Challenge);

            byte[] PasswordHash = PasswordForEmail.Password;
            byte[] Salt = PasswordForEmail.Salt;

            byte[] ChallengeHash = GenerateHash(ChallengeBytes, Salt);

            if (ChallengeHash.SequenceEqual(PasswordHash))
            {
                return db.Users.Find(UserEmail);
            }
            else
            {
                throw new Exception("Wrong Password");
            }

        }

        private static byte[] GetBytesFromString(string String)
        {
            byte[] bytes = new byte[String.Length * sizeof(char)];
            System.Buffer.BlockCopy(String.ToCharArray(), 0, bytes, 0, bytes.Length);
            return bytes;
        }

        private static byte[] ConcatenateByteArrays(byte[] Arr1, byte[] Arr2)
        {
            byte[] Combination = new byte[Arr1.Length + Arr2.Length];
            System.Buffer.BlockCopy(Arr1, 0, Combination, 0, Arr1.Length);
            System.Buffer.BlockCopy(Arr2, 0, Combination, Arr1.Length, Arr2.Length);
            return Combination;
        }

        private static byte[] GenerateHash(byte[] Password, byte[] Salt)
        {
            byte[] Combination = ConcatenateByteArrays(Password, Salt);

            HashAlgorithm Algorithm = new SHA512Managed();

            return Algorithm.ComputeHash(Combination);
        }

    }
}