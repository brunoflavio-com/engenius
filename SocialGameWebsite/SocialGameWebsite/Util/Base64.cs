using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameWebsite.Util
{
    public static class Base64
    {
        public static string Decode(string Base64String)
        {
            byte[] DataBytes = Convert.FromBase64String(Base64String);
            string DataString = System.Text.Encoding.UTF8.GetString(DataBytes);

            return DataString;
        }

        public static string Encode(string DataString)
        {
            byte[] DataBytes = System.Text.Encoding.UTF8.GetBytes(DataString);
            string Base64String = Convert.ToBase64String(DataBytes);

            return Base64String;
        }
    }
}