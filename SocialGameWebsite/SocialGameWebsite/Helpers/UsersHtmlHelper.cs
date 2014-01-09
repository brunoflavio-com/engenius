using SocialGameWebsite.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using System.Web.Mvc.Html;
using System.Web.Mvc.Ajax;
using SocialGameWebsite.Util;

namespace SocialGameWebsite.Helpers
{
    public static class UsersHtmlHelper
    {        
        public static MvcHtmlString DisplayForUser(this HtmlHelper HtmlHelper, UserViewModel user)
        {            
            UrlHelper UrlHelper = new UrlHelper(HttpContext.Current.Request.RequestContext);
            AjaxHelper AjaxHelper = new AjaxHelper(HtmlHelper.ViewContext, HtmlHelper.ViewDataContainer);

            StringBuilder outputHTML = new StringBuilder();            

            outputHTML.Append("<div id=\"user_")
                      .Append(Base64.Encode(user.Email))
                      .Append("\" ")
                      .Append("onclick=\"if(event.target.tagName === 'A')return; location.href='")
                      .Append(UrlHelper.Action("ViewProfile", "Home", new { id = Base64.Encode(user.Email) }))
                      .Append("';\" ")
                      .Append("class=\"user ")
                      .Append("mood_")
                      .Append(user.HumourStatus.ID)
                      .Append("\">");

            outputHTML.Append("<div class=\"header\">")
                        .Append("<img alt=\"Product cover\" class=\"image\" src=\"")
                        //IF the user has profile picture: .Append(user.ImageURL)
                        .Append("/Images/user.png")
                        .Append("\" />")
                      .Append("</div>");

            outputHTML.Append("<div class=\"title\">").Append(user.Name + " " + user.Surname).Append("</div>");

            outputHTML.Append("<br><div class=\"mood\">Mood: ").Append(user.HumourStatus.Name).Append("</div>");
            
            outputHTML.Append("</div>");

            return MvcHtmlString.Create(outputHTML.ToString());
        }
    }
}