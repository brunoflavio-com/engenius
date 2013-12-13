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

        public static void RegisterUser(UserEntity User, string Password)
        {
            byte[] PasswordBytes = GetBytesFromString(Password);
            byte[] SaltBytes = new byte[128];
            SocialGameBLLDbContext db = new SocialGameBLLDbContext();

            RNGCryptoServiceProvider CryptoProvider = new RNGCryptoServiceProvider();
            CryptoProvider.GetBytes(SaltBytes);

            byte[] PasswordHash = GenerateHash(PasswordBytes, SaltBytes);

            UserSecurity UserSecurity = new UserSecurity
            {
                UserEmail = User.Email,
                Password = PasswordHash,
                Salt = SaltBytes
            };

            db.Passwords.Add(UserSecurity);
            db.SaveChanges();
        }

        public static bool LoginUser(string UserEmail, string Challenge)
        {
            SocialGameBLLDbContext db = new SocialGameBLLDbContext();
            UserSecurity PasswordForEmail = db.Passwords.Find(UserEmail);
            byte[] ChallengeBytes = GetBytesFromString(Challenge);

            byte[] PasswordHash = PasswordForEmail.Password;
            byte[] Salt = PasswordForEmail.Salt;

            byte[] ChallengeHash = GenerateHash(ChallengeBytes, Salt);

            return ChallengeHash.SequenceEqual(PasswordHash);

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