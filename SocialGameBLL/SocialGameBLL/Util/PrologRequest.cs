using System;
using System.Collections.Generic;
using System.Configuration;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Web;
using System.Collections.Specialized;

namespace SocialGameBLL.Util
{
    public static class PrologRequest
    {
        public const string LOAD_USER_GRAPH = "LoadUserGraph";
        public const string GET_SHORTEST_PATH = "GetShortestPath";
        public const string GET_STRONGEST_PATH = "GetStrongestPath";

        public static string MakeJsonPostRequest(string ServerMethod, string Json, CookieContainer CookieJar)
        {
            if (CookieJar == null)
            {
                CookieJar = new CookieContainer();
            }

            /*Get Url*/
            string ServerUrl = ConfigurationManager.AppSettings["SocialGameAIUrl"];
            ServerUrl += ConfigurationManager.AppSettings[ServerMethod];

            /*Convert String to Bytes*/
            byte[] ByteArray = Encoding.UTF8.GetBytes(Json);

            /*Make Request*/
            HttpWebRequest Request = (HttpWebRequest)HttpWebRequest.Create(ServerUrl);
            Request.CookieContainer = CookieJar;
            Request.Method = "POST";
            Request.ContentType = "application/json";
            Request.ContentLength = ByteArray.Length;
            Stream RequestStream = Request.GetRequestStream();
            RequestStream.Write(ByteArray, 0, ByteArray.Length);
            RequestStream.Close();

            /*Get Response*/
            WebResponse Response = Request.GetResponse();
            Stream ResponseStream = Response.GetResponseStream();

            /*Convert Response to String*/
            StreamReader StreamReader = new StreamReader(ResponseStream);
            string ResponseText = StreamReader.ReadToEnd();
            StreamReader.Close();
            ResponseStream.Close();
            Response.Close();

            return ResponseText;
        }

        public static string MakeJsonGetResquest(string ServerMethod, OrderedDictionary Params, CookieContainer CookieJar)
        {
            if (CookieJar == null)
            {
                CookieJar = new CookieContainer();
            }

            /*Get Url*/
            string ServerUrl = ConfigurationManager.AppSettings["SocialGameAIUrl"];
            ServerUrl += ConfigurationManager.AppSettings[ServerMethod];

            /*Prepare Query String*/
            string RequestQuery = (Params.Count > 0) ? "?" : "";
            int Counter = 0;
            foreach(var Key in Params.Keys)
            {
                Counter++;
                if (!(Key is string) || !(Params[Key] is string))
                {
                    throw new ArgumentException("Params must be a OrderedDictionary of <string, string>");
                }
                RequestQuery += Key + "=" + Params[Key];
                RequestQuery += (Counter == Params.Count) ? "" : "&";
            }
            
            /*Make Request*/
            HttpWebRequest Request = (HttpWebRequest)HttpWebRequest.Create(ServerUrl+RequestQuery);
            Request.Method = "GET";
            Request.CookieContainer = CookieJar;

            /*Get Response*/
            WebResponse Response = Request.GetResponse();
            Stream ResponseStream = Response.GetResponseStream();

            /*Convert Response to string*/
            StreamReader StreamReader = new StreamReader(ResponseStream);
            string ResponseText = StreamReader.ReadToEnd();
            StreamReader.Close();
            ResponseStream.Close();
            Response.Close();

            return ResponseText;
        }
    }
}