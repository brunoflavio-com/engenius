using SocialGameWebsite.SocialGameBLLService;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using SocialGameWebsite.Models;

namespace SocialGameWebsite.Controllers
{
    public class LeaderboardController : Controller
    {

        SocialGameBLLServiceClient Proxy = new SocialGameBLLServiceClient();
        //
        // GET: /Leaderboard/

        public ActionResult Index()
        {
            return View();
        }

        public ActionResult NormalModeTop10(int Page=1)
        {
            ICollection<UserScore> ServiceScores = Proxy.GetPaginatedUsersScores(10 , Page);
            NormalModePointsLeaderBoardViewModel Top10ViewModel = new NormalModePointsLeaderBoardViewModel();
        
            foreach(UserScore Score in ServiceScores)
            {
                Top10ViewModel.Scores.Add(new UserScoreViewModel
                    {
                        UserEmail = Score.UserEmail,
                        UserName = Score.UserName,
                        UserSurname = Score.UserSurname,
                        UserLevel = Score.UserLevel,
                        UserPoints = Score.UserPoints
                    });
            }

            return PartialView(Top10ViewModel);
        }

    }
}
